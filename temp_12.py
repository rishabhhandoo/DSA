# Paste this entire cell into Jupyter and run.
import re
from collections import defaultdict
from functools import lru_cache
import sys

def parse_input(filename="input.txt"):
    with open(filename, "r") as f:
        lines = [ln.rstrip("\n") for ln in f]

    # Parse shapes: lines starting with "<idx>:" then shape rows until next index or blank line
    shapes = {}
    i = 0
    while i < len(lines):
        ln = lines[i].strip()
        if ln == "":
            i += 1
            continue
        m = re.match(r"^(\d+):\s*$", ln)
        if not m:
            break
        idx = int(m.group(1))
        i += 1
        shape_lines = []
        while i < len(lines):
            if lines[i].strip() == "":
                i += 1
                break
            if re.match(r"^\d+:\s*$", lines[i].strip()):
                break
            if re.match(r"^\d+x\d+:\s*", lines[i].strip()):  # start of regions
                break
            shape_lines.append(lines[i])
            i += 1
        shapes[idx] = shape_lines

    # Parse regions: remaining non-empty lines like "WxH: c0 c1 c2 ..."
    regions = []
    while i < len(lines):
        ln = lines[i].strip()
        i += 1
        if not ln:
            continue
        m = re.match(r"^(\d+)x(\d+):\s*(.*)$", ln)
        if not m:
            continue
        w = int(m.group(1))
        h = int(m.group(2))
        counts = [int(x) for x in m.group(3).split()]
        regions.append((w, h, counts))
    return shapes, regions

# Convert shape visual to set of (x,y) coordinates (x = col, y = row), normalized to min 0
def shape_to_coords(shape_lines):
    coords = []
    for y, row in enumerate(shape_lines):
        for x, ch in enumerate(row):
            if ch == "#":
                coords.append((x, y))
    if not coords:
        return frozenset()
    minx = min(x for x, y in coords)
    miny = min(y for x, y in coords)
    norm = frozenset(((x - minx, y - miny) for x, y in coords))
    return norm

def rotate90(coords):
    # rotate 90 degrees: (x,y) -> (y, -x) then normalize
    pts = [(y, -x) for x, y in coords]
    minx = min(x for x, y in pts)
    miny = min(y for x, y in pts)
    return frozenset(((x - minx, y - miny) for x, y in pts))

def flip_horizontal(coords):
    # reflect horizontally: (x,y) -> (-x, y)
    pts = [(-x, y) for x, y in coords]
    minx = min(x for x, y in pts)
    miny = min(y for x, y in pts)
    return frozenset(((x - minx, y - miny) for x, y in pts))

def generate_orientations(coords):
    # generate all unique rotations/flips
    s = set()
    cur = coords
    for r in range(4):
        if cur not in s:
            s.add(cur)
        f = flip_horizontal(cur)
        if f not in s:
            s.add(f)
        cur = rotate90(cur)
    return list(s)

def get_bbox(coords):
    xs = [x for x, y in coords]
    ys = [y for x, y in coords]
    return max(xs)+1, max(ys)+1  # width, height

def can_place(grid_w, grid_h, occ, shape_coords, ox, oy):
    for x, y in shape_coords:
        gx, gy = ox + x, oy + y
        if gx < 0 or gy < 0 or gx >= grid_w or gy >= grid_h:
            return False
        if (gx, gy) in occ:
            return False
    return True

def place(occ, shape_coords, ox, oy):
    for x, y in shape_coords:
        occ.add((ox + x, oy + y))

def unplace(occ, shape_coords, ox, oy):
    for x, y in shape_coords:
        occ.remove((ox + x, oy + y))

def try_pack_one_region(grid_w, grid_h, piece_orients):
    """
    piece_orients: list of (area, [list of orientation sets for that piece]) for each piece instance
    We assume piece_orients is a list of instances (i.e., if same shape appears k times, it will appear k times in list)
    """
    # Sort pieces by area descending (and by number of orientations ascending to break ties)
    piece_indices = list(range(len(piece_orients)))
    piece_indices.sort(key=lambda i: (-piece_orients[i][0], len(piece_orients[i][1])))

    occ = set()

    # Precompute bounding dims for each orientation to limit placement loops
    orient_dims = {}
    for i in piece_indices:
        _, orients = piece_orients[i]
        od = []
        for o in orients:
            w, h = get_bbox(o)
            od.append((o, w, h))
        orient_dims[i] = od

    # backtracking
    sys.setrecursionlimit(10000)
    @lru_cache(maxsize=None)
    def occ_key_from_set(s):
        # not used; keep for potential memoization in future
        return tuple(sorted(s))

    def backtrack(k):
        if k == len(piece_indices):
            return True
        i = piece_indices[k]
        area, orients = piece_orients[i]
        # For small grids, simple heuristics suffice: try each orientation and placement
        for o, w_o, h_o in orient_dims[i]:
            # try all top-left placements that keep piece inside grid
            for ox in range(0, grid_w - w_o + 1):
                for oy in range(0, grid_h - h_o + 1):
                    if can_place(grid_w, grid_h, occ, o, ox, oy):
                        place(occ, o, ox, oy)
                        if backtrack(k + 1):
                            return True
                        unplace(occ, o, ox, oy)
        return False

    return backtrack(0)


def solve_all(shapes_raw, regions):
    # prepare shapes: index -> all orientations (sets of coords)
    shapes_coords = {}
    for idx, lines in shapes_raw.items():
        coords = shape_to_coords(lines)
        shapes_coords[idx] = generate_orientations(coords)

    success_count = 0
    results = []

    for region_idx, (w, h, counts) in enumerate(regions):
        # Build list of piece instances to place
        piece_instances = []
        valid = True
        for shape_idx, cnt in enumerate(counts):
            if cnt <= 0:
                continue
            if shape_idx not in shapes_coords:
                # shape not present in shapes section -> cannot place
                valid = False
                break
            orients = shapes_coords[shape_idx]
            # compute area of shape (same for all orientations)
            if len(orients) == 0:
                area = 0
            else:
                area = len(next(iter(orients)))
            for _ in range(cnt):
                piece_instances.append((area, orients))
        if not valid:
            results.append(False)
            continue

        # quick area-prune: total area must be <= grid area
        total_area = sum(area for area, _ in piece_instances)
        if total_area > w * h:
            results.append(False)
            continue

        # Attempt packing (try both orientations of width/height since input width x length [they mean width x height]
        # We'll treat w as width (x) and h as height (y).
        ok = try_pack_one_region(w, h, piece_instances)
        results.append(bool(ok))
        if ok:
            success_count += 1

    return success_count, results

if __name__ == "__main__":
    shapes, regions = parse_input("input.txt")
    success_count, results = solve_all(shapes, regions)
    print(f"Regions that can fit all presents: {success_count} of {len(regions)}")
    for idx, res in enumerate(results):
        print(f" Region {idx+1}: {'Fits' if res else 'Does NOT fit'}")
