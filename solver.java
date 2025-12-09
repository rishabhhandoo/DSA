import java.io.*;
import java.util.*;

public class Solver {

    static class Interval {
        int l, r;
        Interval(int l, int r){
            this.l = l;
            this.r = r;
        }
    }

    public static void main(String[] args) throws Exception {

        // ---------- READ input.txt ----------
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line;
        ArrayList<int[]> verts = new ArrayList<>();

        while((line = br.readLine()) != null){
            line = line.trim();
            if(line.isEmpty()) continue;
            String[] p = line.split(",");
            int x = Integer.parseInt(p[0]);
            int y = Integer.parseInt(p[1]);
            verts.add(new int[]{x,y});
        }

        int n = verts.size();
        if(n < 2){
            System.out.println(0);
            return;
        }

        // ---------- Build edges ----------
        int[][] v = new int[n][2];
        for(int i=0;i<n;i++){
            v[i] = verts.get(i);
        }

        // bounding box
        int minx = Integer.MAX_VALUE, maxx = Integer.MIN_VALUE;
        int miny = Integer.MAX_VALUE, maxy = Integer.MIN_VALUE;
        for(int i=0;i<n;i++){
            minx = Math.min(minx, v[i][0]);
            maxx = Math.max(maxx, v[i][0]);
            miny = Math.min(miny, v[i][1]);
            maxy = Math.max(maxy, v[i][1]);
        }

        int H = maxy - miny + 1;

        @SuppressWarnings("unchecked")
        ArrayList<Interval>[] allowed = new ArrayList[H];
        for(int i=0;i<H;i++) allowed[i] = new ArrayList<>();

        // ---------- Scanline Polygon Fill (fast) ----------
        for(int yy = miny; yy <= maxy; yy++){
            ArrayList<Double> xs = new ArrayList<>(32);

            for(int i=0;i<n;i++){
                int x1 = v[i][0], y1 = v[i][1];
                int x2 = v[(i+1)%n][0], y2 = v[(i+1)%n][1];

                // horizontal edge -> add the whole interval
                if(y1 == yy && y2 == yy){
                    int a = Math.min(x1,x2);
                    int b = Math.max(x1,x2);
                    allowed[yy-miny].add(new Interval(a,b));
                }
                else if((y1 > yy) != (y2 > yy)){ 
                    // compute intersection
                    double xi = x1 + (double)(yy - y1) * (x2 - x1) / (double)(y2 - y1);
                    xs.add(xi);
                }
            }

            Collections.sort(xs);

            // interior intervals from pairs
            for(int k=0; k+1 < xs.size(); k+=2){
                int a = (int)Math.ceil(xs.get(k));
                int b = (int)Math.floor(xs.get(k+1));
                if(a <= b){
                    allowed[yy-miny].add(new Interval(a,b));
                }
            }

            // merge intervals
            ArrayList<Interval> row = allowed[yy-miny];
            if(row.isEmpty()) continue;

            row.sort((A,B)->A.l - B.l);

            ArrayList<Interval> merged = new ArrayList<>();
            int L = row.get(0).l, R = row.get(0).r;

            for(int i=1;i<row.size();i++){
                Interval cur = row.get(i);
                if(cur.l <= R + 1){
                    R = Math.max(R, cur.r);
                } else {
                    merged.add(new Interval(L,R));
                    L = cur.l; R = cur.r;
                }
            }
            merged.add(new Interval(L,R));
            allowed[yy-miny] = merged;
        }

        // ---------- Rectangle Checking ----------
        HashMap<Long, int[]> redMap = new HashMap<>();
        for(int[] p : v){
            long key = (((long)p[0])<<32) ^ (long)(p[1] & 0xffffffffL);
            redMap.put(key, p);
        }

        // Cache: prefix per (lx,rx)
        HashMap<String, int[]> prefixCache = new HashMap<>();

        int maxArea = 0;

        for(int i=0;i<n;i++){
            int x1 = v[i][0], y1 = v[i][1];

            for(int j=i+1;j<n;j++){
                int x2 = v[j][0], y2 = v[j][1];

                if(x1 == x2 || y1 == y2) continue;

                int lx = Math.min(x1,x2);
                int rx = Math.max(x1,x2);
                int by = Math.min(y1,y2);
                int ty = Math.max(y1,y2);

                int area = (rx - lx + 1) * (ty - by + 1);
                if(area <= maxArea) continue;

                String key = lx + "," + rx;

                int[] P;
                if(prefixCache.containsKey(key)){
                    P = prefixCache.get(key);
                } else {
                    P = new int[H+1];
                    for(int yi=0; yi<H; yi++){
                        ArrayList<Interval> row = allowed[yi];
                        boolean ok = false;
                        for(Interval in : row){
                            if(in.l <= lx && in.r >= rx){
                                ok = true;
                                break;
                            }
                        }
                        P[yi+1] = P[yi] + (ok ? 1 : 0);
                    }
                    prefixCache.put(key, P);
                }

                int r1 = by - miny;
                int r2 = ty - miny;
                int full = r2 - r1 + 1;

                if(P[r2+1] - P[r1] == full){
                    maxArea = area;
                }
            }
        }

        System.out.println(maxArea);
    }
}
