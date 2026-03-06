#ifndef GRAPH_EXPERT_HPP
#define GRAPH_EXPERT_HPP

#include <string>

class GraphExpert {
public:

    /* --- 1. BASIC TRAVERSALS --- */

    static std::string getBFS() {
        return "// Time: O(V+E) | Space: O(V)\n"
               "vector<int> bfs(int n, vector<vector<int>>& adj, int src) {\n"
               "    vector<int> dist(n + 1, -1); queue<int> q;\n"
               "    dist[src] = 0; q.push(src);\n"
               "    while(!q.empty()) {\n"
               "        int u = q.front(); q.pop();\n"
               "        for(int v : adj[u]) if(dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); }\n"
               "    } return dist;\n}\n\n";
    }

    static std::string getDFS() {
        return "// Standard Recursive DFS\n"
               "void dfs(int u, vector<vector<int>>& adj, vector<bool>& vis) {\n"
               "    vis[u] = true;\n"
               "    for(int v : adj[u]) if(!vis[v]) dfs(v, adj, vis);\n"
               "}\n\n";
    }

    /* --- 2. CYCLE DETECTION & COLORING --- */

    static std::string getCycleDetection() {
        return "// Undirected Cycle Detection using BFS\n"
               "bool hasCycleUndirected(int n, vector<vector<int>>& adj) {\n"
               "    vector<bool> vis(n + 1, false);\n"
               "    for(int i=1; i<=n; i++) {\n"
               "        if(!vis[i]) {\n"
               "            queue<pair<int,int>> q; q.push({i, -1}); vis[i] = true;\n"
               "            while(!q.empty()) {\n"
               "                auto [u, p] = q.front(); q.pop();\n"
               "                for(int v : adj[u]) {\n"
               "                    if(!vis[v]) { vis[v] = true; q.push({v, u}); }\n"
               "                    else if(v != p) return true;\n"
               "                }\n"
               "            }\n"
               "        }\n"
               "    } return false;\n}\n\n";
    }

    static std::string getBipartite() {
        return "// Bipartite Check (2-Coloring) using BFS\n"
               "bool isBipartite(int n, vector<vector<int>>& adj) {\n"
               "    vector<int> color(n + 1, -1);\n"
               "    for(int i=1; i<=n; i++) {\n"
               "        if(color[i] == -1) {\n"
               "            queue<int> q; q.push(i); color[i] = 0;\n"
               "            while(!q.empty()) {\n"
               "                int u = q.front(); q.pop();\n"
               "                for(int v : adj[u]) {\n"
               "                    if(color[v] == -1) { color[v] = 1 - color[u]; q.push(v); }\n"
               "                    else if(color[v] == color[u]) return false;\n"
               "                }\n"
               "            }\n"
               "        }\n"
               "    } return true;\n}\n\n";
    }

    /* --- 3. TOPOLOGICAL SORTING --- */

    static std::string getTopoSort() {
        return "// Kahn's Algorithm for Topological Sort (DAG only)\n"
               "vector<int> topoSort(int n, vector<vector<int>>& adj) {\n"
               "    vector<int> inDegree(n + 1, 0), order;\n"
               "    for(int u=1; u<=n; u++) for(int v : adj[u]) inDegree[v]++;\n"
               "    queue<int> q; for(int i=1; i<=n; i++) if(inDegree[i] == 0) q.push(i);\n"
               "    while(!q.empty()) {\n"
               "        int u = q.front(); q.pop(); order.push_back(u);\n"
               "        for(int v : adj[u]) if(--inDegree[v] == 0) q.push(v);\n"
               "    }\n"
               "    return (order.size() == n) ? order : vector<int>();\n}\n\n";
    }

    /* --- 4. SHORTEST PATHS --- */

    static std::string getDijkstra() {
        return "// Dijkstra O(E log V) - Weighted Shortest Path\n"
               "vector<ll> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int src) {\n"
               "    vector<ll> dist(n + 1, 1e18); dist[src] = 0;\n"
               "    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;\n"
               "    pq.push({0, src});\n"
               "    while(!pq.empty()) {\n"
               "        auto [d, u] = pq.top(); pq.pop();\n"
               "        if(d > dist[u]) continue;\n"
               "        for(auto& edge : adj[u]) {\n"
               "            if(dist[edge.first] > d + edge.second) {\n"
               "                dist[edge.first] = d + edge.second;\n"
               "                pq.push({dist[edge.first], edge.first});\n"
               "            }\n"
               "        }\n"
               "    } return dist;\n}\n\n";
    }

    static std::string getFloydWarshall() {
        return "// All-Pairs Shortest Path O(V^3)\n"
               "void floydWarshall(int n, vector<vector<ll>>& dist) {\n"
               "    for(int k=1; k<=n; k++)\n"
               "        for(int i=1; i<=n; i++)\n"
               "            for(int j=1; j<=n; j++)\n"
               "                if(dist[i][k] != 1e18 && dist[k][j] != 1e18)\n"
               "                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);\n}\n\n";
    }

    /* --- 5. CONNECTIVITY & MST --- */

    static std::string getDSU() {
        return "struct DSU {\n"
               "    vector<int> p, sz; DSU(int n) { p.resize(n+1); sz.assign(n+1, 1); iota(p.begin(), p.end(), 0); }\n"
               "    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }\n"
               "    bool unite(int a, int b) {\n"
               "        a = find(a); b = find(b); if(a == b) return false;\n"
               "        if(sz[a] < sz[b]) swap(a, b); p[b] = a; sz[a] += sz[b]; return true;\n"
               "    }\n};\n\n";
    }

    static std::string getKruskal() {
        return "// MST: Kruskal's O(E log E)\n"
               "struct Edge { int u, v, w; bool operator<(const Edge& other) const { return w < other.w; } };\n"
               "ll kruskal(int n, vector<Edge>& edges) {\n"
               "    sort(edges.begin(), edges.end()); DSU dsu(n); ll mst_wt = 0;\n"
               "    for(auto& e : edges) if(dsu.unite(e.u, e.v)) mst_wt += e.w;\n"
               "    return mst_wt;\n}\n\n";
    }

    /* --- 6. SPECIALIZED VARIATIONS --- */

    static std::string getWordLadder() {
        return "// BFS Variation: Shortest transformation path between words\n"
               "int wordLadder(string begin, string end, unordered_set<string>& dict) {\n"
               "    if(dict.find(end) == dict.end()) return 0;\n"
               "    queue<pair<string, int>> q; q.push({begin, 1});\n"
               "    while(!q.empty()) {\n"
               "        string curr = q.front().first; int steps = q.front().second; q.pop();\n"
               "        if(curr == end) return steps;\n"
               "        for(int i=0; i<curr.size(); i++) {\n"
               "            char orig = curr[i];\n"
               "            for(char c='a'; c<='z'; c++) {\n"
               "                curr[i] = c;\n"
               "                if(dict.count(curr)) { dict.erase(curr); q.push({curr, steps+1}); }\n"
               "            }\n"
               "            curr[i] = orig;\n"
               "        }\n"
               "    } return 0;\n}\n\n";
    }
};

#endif