#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Interval { int l, r; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<int,int>> verts;
    int x, y;

    // ---- READ INPUT.TXT ----
    while (cin >> x) {
        char c;
        cin >> c >> y;
        verts.push_back({x,y});
    }

    int n = verts.size();
    vector<pair<pair<int,int>, pair<int,int>>> edges;

    // build edges
    for(int i=0;i<n;i++){
        auto [x1,y1] = verts[i];
        auto [x2,y2] = verts[(i+1)%n];
        edges.push_back({{x1,y1},{x2,y2}});
        if(x1!=x2 && y1!=y2){
            cerr << "Non axis-aligned edge!\n";
            return 1;
        }
    }

    // bounding box
    int minx=1e9, maxx=-1e9, miny=1e9, maxy=-1e9;
    for(auto& p: verts){
        minx=min(minx,p.first);
        maxx=max(maxx,p.first);
        miny=min(miny,p.second);
        maxy=max(maxy,p.second);
    }

    int H = maxy - miny + 1;
    vector<vector<Interval>> allowed(H);

    // ---------- BUILD ALLOWED INTERVALS FAST ----------
    // For each row (y), compute polygon intersections
    for(int yy = miny; yy <= maxy; yy++){
        vector<double> xs;
        xs.reserve(32);

        for(auto &e: edges){
            auto [p1,p2] = e;
            auto [x1,y1] = p1;
            auto [x2,y2] = p2;

            if((y1 > yy) != (y2 > yy)){    // proper intersection
                double xi = x1 + (double)(yy - y1) * (x2 - x1) / (double)(y2 - y1);
                xs.push_back(xi);
            }
            else if(y1==yy && y2==yy){
                // horizontal edge → fill entire span as interior/edge
                int a=min(x1,x2), b=max(x1,x2);
                allowed[yy-miny].push_back({a,b});
            }
        }

        sort(xs.begin(), xs.end());
        vector<Interval> merged;

        // pair intersections for interior
        for(int k=0;k+1<xs.size();k+=2){
            int a = (int)ceil(xs[k]);
            int b = (int)floor(xs[k+1]);
            if(a<=b) merged.push_back({a,b});
        }

        // merge with edge intervals
        // NOTE: horizontal edge intervals were already inserted above
        // Now merge merged + allowed[yy-miny]
        vector<Interval> &row = allowed[yy-miny];
        for(auto &iv : merged) row.push_back(iv);

        // unify row intervals
        if(row.empty()) continue;
        sort(row.begin(), row.end(), [](auto &A, auto &B){ return A.l<B.l; });
        vector<Interval> unified;
        int L=row[0].l, R=row[0].r;
        for(int i=1;i<row.size();i++){
            if(row[i].l <= R+1) R=max(R,row[i].r);
            else{
                unified.push_back({L,R});
                L=row[i].l; R=row[i].r;
            }
        }
        unified.push_back({L,R});
        row = unified;
    }

    // RED SET
    unordered_set<long long> red_hash;
    for(auto&p:verts){
        long long key= ((long long)p.first<<32) ^ (unsigned long long)p.second;
        red_hash.insert(key);
    }

    // rectangle checking:
    // cache prefix for each span
    map<pair<int,int>, vector<int>> prefix_cache;

    auto covers = [&](vector<Interval>& v, int lx, int rx){
        int lo=0, hi=v.size();
        while(lo<hi){
            int mid=(lo+hi)/2;
            if(v[mid].l <= lx) lo=mid+1;
            else hi=mid;
        }
        int idx=lo-1;
        if(idx>=0 && v[idx].l<=lx && v[idx].r>=rx) return true;
        return false;
    };

    int max_area = 0;

    for(int i=0;i<n;i++){
        auto [x1,y1] = verts[i];
        for(int j=i+1;j<n;j++){
            auto [x2,y2] = verts[j];

            if(x1==x2 || y1==y2) continue;

            int lx=min(x1,x2), rx=max(x1,x2);
            int by=min(y1,y2), ty=max(y1,y2);

            int area = (rx-lx+1)*(ty-by+1);
            if(area <= max_area) continue;

            auto key = make_pair(lx,rx);

            if(prefix_cache.count(key)==0){
                vector<int> P(H+1,0);
                for(int yi=0; yi<H; yi++){
                    P[yi+1] = P[yi] + (covers(allowed[yi], lx, rx) ? 1 : 0);
                }
                prefix_cache[key] = P;
            }

            auto &P = prefix_cache[key];
            int r1 = by - miny;
            int r2 = ty - miny;
            int full = r2 - r1 + 1;

            if(P[r2+1] - P[r1] == full){
                max_area = area;
            }
        }
    }

    cout << max_area << "\n";
    return 0;
}
