class Solution {
public:
   vector<int>parent;
   vector<int>rank;
  struct DSU {
    int n;
    vector<int> p, sz;
    DSU(int n=0): n(n), p(n), sz(n,1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){ return p[x]==x ? x : p[x]=find(p[x]); }
    void unite(int a, int b){
        a = find(a); b = find(b);
        if(a==b) return;
        if(sz[a] < sz[b]) swap(a,b);
        p[b] = a;
        sz[a] += sz[b];
    }
};
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
    DSU dsu(n);

    // Build adjacency list or edge list with max value for sorting
    struct Edge { int u,v,maxv; };
    vector<Edge> E;
    E.reserve(edges.size());
    for(auto &e: edges){
        int u = e[0], v = e[1];
        E.push_back({u, v, max(vals[u], vals[v])});
    }
    sort(E.begin(), E.end(), [](const Edge &a, const Edge &b){
        return a.maxv < b.maxv;
    });

    // Order nodes by value (value, node)
    vector<pair<int,int>> nodes;
    nodes.reserve(n);
    for(int i=0;i<n;++i) nodes.emplace_back(vals[i], i);
    sort(nodes.begin(), nodes.end());

    long long ans = 0;
    int ei = 0; // pointer over sorted edges

    // Process values in increasing order (group by equal values)
    for(int i=0; i<n; ){
        int j = i;
        int curVal = nodes[i].first;
        // first unite all edges with maxv <= curVal
        while(ei < (int)E.size() && E[ei].maxv <= curVal){
            dsu.unite(E[ei].u, E[ei].v);
            ++ei;
        }

        // collect all nodes with value == curVal and count per DSU root
        unordered_map<int,int> cnt;
        while(j < n && nodes[j].first == curVal){
            int node = nodes[j].second;
            int root = dsu.find(node);
            ++cnt[root];
            ++j;
        }

        // For each component with k nodes of value curVal, add k*(k+1)/2
        for(auto &p : cnt){
            long long k = p.second;
            ans += k * (k + 1) / 2;
        }

        i = j;
    }

    return ans;
    }
};