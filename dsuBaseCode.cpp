class DSU {
    public:
    vector<int> parent, rank,size;
    DSU(int n) {
        parent.resize(n+1);
        size.resize(n+1,1);
        rank.resize(n+1, 0);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }
    int findpar(int node) {
       if(node == parent[node])  return node;
       return parent[node] = findpar(parent[node]);
    }
    void unionRank(int u, int v) {
        int paru = findpar(u), parv = findpar(v);
        if(paru == parv)    return;
        else if(rank[paru]< rank[parv])
        {
            parent[paru]=parv;
        }else if(rank[parv]< rank[paru])
        {
            parent[parv]=paru;
        }else 
        {
            parent[parv] = paru;
            rank[paru]++;
        }
    }
    void unionSize(int u,int v)
    {
        int paru = findpar(u),parv = findpar(v);
        if(paru == parv)    return;
        if(size[paru] < size[parv])
        {
            size[parv]+=size[paru];
            parent[paru]= parv;
        }else{
            size[parv]+=size[paru];
            parent[paru] = parv;
        }
    }
};