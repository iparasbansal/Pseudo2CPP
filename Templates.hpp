#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <string>

class Templates {
public:
    static std::string header() {
        return "#include <bits/stdc++.h>\n"
               "using namespace std;\n"
               "typedef long long ll;\n"
               "#define MOD 1000000007\n\n";
    }

    /* =========================================
       1. GRAPHS EXPERT
       ========================================= */

    static std::string dijkstra() {
        return "vector<ll> dijkstra(int n, vector<vector<pair<int,int>>>& g, int src) {\n"
               "    vector<ll> dist(n, LLONG_MAX); dist[src] = 0;\n"
               "    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;\n"
               "    pq.push({0, src});\n"
               "    while(!pq.empty()) {\n"
               "        auto [d, u] = pq.top(); pq.pop();\n"
               "        if(d > dist[u]) continue;\n"
               "        for(auto& [v, w] : g[u]) {\n"
               "            if(dist[v] > d + w) { dist[v] = d + w; pq.push({dist[v], v}); }\n"
               "        }\n"
               "    } return dist;\n}\n\n";
    }

    static std::string bfs() {
        return "vector<int> bfs(int n, vector<vector<int>>& g, int src) {\n"
               "    vector<int> dist(n, -1); queue<int> q;\n"
               "    dist[src] = 0; q.push(src);\n"
               "    while(!q.empty()) {\n"
               "        int u = q.front(); q.pop();\n"
               "        for(int v : g[u]) if(dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); }\n"
               "    } return dist;\n}\n\n";
    }

    static std::string dfs() {
        return "void dfs(int u, vector<vector<int>>& g, vector<bool>& vis) {\n"
               "    vis[u] = true;\n"
               "    for(int v : g[u]) if(!vis[v]) dfs(v, g, vis);\n"
               "}\n\n";
    }

    static std::string topoSort() {
        return "vector<int> topoSort(int n, vector<vector<int>>& g) {\n"
               "    vector<int> in_degree(n, 0), order; queue<int> q;\n"
               "    for(int u=0; u<n; u++) for(int v : g[u]) in_degree[v]++;\n"
               "    for(int i=0; i<n; i++) if(in_degree[i] == 0) q.push(i);\n"
               "    while(!q.empty()) {\n"
               "        int u = q.front(); q.pop(); order.push_back(u);\n"
               "        for(int v : g[u]) if(--in_degree[v] == 0) q.push(v);\n"
               "    } return order.size() == n ? order : vector<int>();\n}\n\n";
    }

    static std::string kruskal() {
        return "struct DSU {\n"
               "    vector<int> parent; DSU(int n) { parent.resize(n); iota(parent.begin(), parent.end(), 0); }\n"
               "    int find(int i) { if (parent[i] == i) return i; return parent[i] = find(parent[i]); }\n"
               "    void unite(int i, int j) { int r_i = find(i), r_j = find(j); if (r_i != r_j) parent[r_i] = r_j; }\n"
               "};\n"
               "int kruskal(int n, vector<vector<int>>& edges) {\n"
               "    sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; });\n"
               "    DSU dsu(n); int mst_weight = 0;\n"
               "    for (auto& e : edges) if (dsu.find(e[0]) != dsu.find(e[1])) { dsu.unite(e[0], e[1]); mst_weight += e[2]; }\n"
               "    return mst_weight;\n}\n\n";
    }

    static std::string bellmanFord() {
        return "vector<ll> bellmanFord(int n, vector<vector<int>>& edges, int src) {\n"
               "    vector<ll> dist(n, 1e18); dist[src] = 0;\n"
               "    for(int i=0; i<n-1; i++) {\n"
               "        for(auto& e : edges) if(dist[e[0]] != 1e18) dist[e[1]] = min(dist[e[1]], dist[e[0]] + e[2]);\n"
               "    } return dist;\n}\n\n";
    }

    static std::string floydWarshall() {
        return "void floydWarshall(vector<vector<ll>>& dist, int n) {\n"
               "    for(int k=0; k<n; k++) \n"
               "        for(int i=0; i<n; i++) \n"
               "            for(int j=0; j<n; j++) \n"
               "                if(dist[i][k] != 1e18 && dist[k][j] != 1e18) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);\n"
               "}\n\n";
    }

    static std::string tarjanSCC() {
        return "void tarjan(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& inStack, vector<vector<int>>& adj) {\n"
               "    static int time = 0; disc[u] = low[u] = ++time; st.push(u); inStack[u] = true;\n"
               "    for (int v : adj[u]) {\n"
               "        if (disc[v] == -1) { tarjan(v, disc, low, st, inStack, adj); low[u] = min(low[u], low[v]); }\n"
               "        else if (inStack[v]) low[u] = min(low[u], disc[v]);\n"
               "    }\n"
               "    if (low[u] == disc[u]) { while (true) { int v = st.top(); st.pop(); inStack[v] = false; if (u == v) break; } }\n"
               "}\n\n";
    }

    /* =========================================
       2. TREES EXPERT
       ========================================= */

    static std::string lcaBinaryLifting() {
        return "struct LCA {\n"
               "    int LOG; vector<int> depth; vector<vector<int>> up;\n"
               "    LCA(int n, vector<vector<int>>& g, int root=0) {\n"
               "        LOG = log2(n) + 1; depth.assign(n, 0); up.assign(n, vector<int>(LOG));\n"
               "        dfs(root, root, g);\n"
               "    }\n"
               "    void dfs(int u, int p, vector<vector<int>>& g) {\n"
               "        up[u][0] = p;\n"
               "        for(int i=1; i<LOG; i++) up[u][i] = up[up[u][i-1]][i-1];\n"
               "        for(int v : g[u]) if(v != p) { depth[v] = depth[u] + 1; dfs(v, u, g); }\n"
               "    }\n"
               "    int get(int u, int v) {\n"
               "        if(depth[u] < depth[v]) swap(u, v);\n"
               "        for(int i=LOG-1; i>=0; i--) if(depth[u]-(1<<i) >= depth[v]) u = up[u][i];\n"
               "        if(u == v) return u;\n"
               "        for(int i=LOG-1; i>=0; i--) if(up[u][i] != up[v][i]) { u = up[u][i]; v = up[v][i]; }\n"
               "        return up[u][0];\n"
               "    }\n};\n\n";
    }

    static std::string treeDiameter() {
        return "int diameter(vector<vector<int>>& adj, int u, int p, int& res) {\n"
               "    int m1 = 0, m2 = 0;\n"
               "    for(int v : adj[u]) {\n"
               "        if(v == p) continue;\n"
               "        int h = diameter(adj, v, u, res);\n"
               "        if(h > m1) { m2 = m1; m1 = h; } else if(h > m2) m2 = h;\n"
               "    }\n"
               "    res = max(res, m1 + m2);\n"
               "    return 1 + m1;\n"
               "}\n\n";
    }

    static std::string burnTree() {
        return "int burnTree(unordered_map<int, vector<int>>& graph, int target) {\n"
               "    queue<int> q; unordered_set<int> vis; q.push(target); vis.insert(target);\n"
               "    int time = 0;\n"
               "    while(!q.empty()) {\n"
               "        int sz = q.size(); bool burned = false;\n"
               "        for(int i=0; i<sz; i++) {\n"
               "            int node = q.front(); q.pop();\n"
               "            for(int nbr : graph[node]) if(vis.find(nbr) == vis.end()) { vis.insert(nbr); q.push(nbr); burned = true; }\n"
               "        } if(burned) time++;\n"
               "    } return time;\n"
               "}\n\n";
    }

    static std::string morrisTraversal() {
        return "void morrisInorder(Node* root) {\n"
               "    Node* curr = root;\n"
               "    while(curr) {\n"
               "        if(!curr->left) { cout << curr->val << \" \"; curr = curr->right; }\n"
               "        else {\n"
               "            Node* pre = curr->left;\n"
               "            while(pre->right && pre->right != curr) pre = pre->right;\n"
               "            if(!pre->right) { pre->right = curr; curr = curr->left; }\n"
               "            else { pre->right = NULL; cout << curr->val << \" \"; curr = curr->right; }\n"
               "        }\n"
               "    }\n"
               "}\n\n";
    }

    static std::string bstValidate() {
        return "bool isValidBST(Node* root, long minV, long maxV) {\n"
               "    if(!root) return true;\n"
               "    if(root->val <= minV || root->val >= maxV) return false;\n"
               "    return isValidBST(root->left, minV, root->val) && isValidBST(root->right, root->val, maxV);\n"
               "}\n\n";
    }

    /* =========================================
       3. DYNAMIC PROGRAMMING EXPERT
       ========================================= */

    static std::string knapsack01() {
        return "int knapsack(int W, vector<int>& wt, vector<int>& val, int n) {\n"
               "    vector<int> dp(W + 1, 0);\n"
               "    for(int i=0; i<n; i++) for(int w=W; w>=wt[i]; w--) dp[w] = max(dp[w], val[i] + dp[w-wt[i]]);\n"
               "    return dp[W];\n}\n\n";
    }

    static std::string dpLCS() {
        return "int lcs(string& s1, string& s2) {\n"
               "    int n = s1.size(), m = s2.size(); vector<int> prev(m + 1, 0), curr(m + 1, 0);\n"
               "    for (int i = 1; i <= n; i++) {\n"
               "        for (int j = 1; j <= m; j++) {\n"
               "            if (s1[i - 1] == s2[j - 1]) curr[j] = 1 + prev[j - 1];\n"
               "            else curr[j] = max(prev[j], curr[j - 1]);\n"
               "        } prev = curr;\n"
               "    } return prev[m];\n}\n\n";
    }

    static std::string dpLIS() {
        return "int lis(vector<int>& a) {\n"
               "    vector<int> dp;\n"
               "    for(int x : a) {\n"
               "        auto it = lower_bound(dp.begin(), dp.end(), x);\n"
               "        if(it == dp.end()) dp.push_back(x); else *it = x;\n"
               "    } return dp.size();\n}\n\n";
    }

    static std::string gridPathDP() {
        return "int minPathSum(vector<vector<int>>& grid) {\n"
               "    int n = grid.size(), m = grid[0].size(); vector<int> dp(m, 1e9); dp[0] = grid[0][0];\n"
               "    for(int j=1; j<m; j++) dp[j] = dp[j-1] + grid[0][j];\n"
               "    for(int i=1; i<n; i++) {\n"
               "        dp[0] += grid[i][0];\n"
               "        for(int j=1; j<m; j++) dp[j] = grid[i][j] + min(dp[j], dp[j-1]);\n"
               "    } return dp[m-1];\n}\n\n";
    }

    static std::string stockDP() {
        return "int stockWithCooldown(vector<int>& prices) {\n"
               "    int sold = 0, hold = -1e9, rest = 0;\n"
               "    for (int p : prices) {\n"
               "        int prev_sold = sold;\n"
               "        sold = hold + p; hold = max(hold, rest - p); rest = max(rest, prev_sold);\n"
               "    } return max(sold, rest);\n}\n\n";
    }

    static std::string partitionMCM() {
        return "int mcm(vector<int>& p) {\n"
               "    int n = p.size(); vector<vector<int>> dp(n, vector<int>(n, 0));\n"
               "    for(int len=2; len<n; len++) {\n"
               "        for(int i=1; i<n-len+1; i++) {\n"
               "            int j = i+len-1; dp[i][j] = 1e9;\n"
               "            for(int k=i; k<j; k++) dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j]);\n"
               "        }\n"
               "    } return dp[1][n-1];\n}\n\n";
    }

    static std::string treeDP() {
        return "pair<int, int> maxIndependentSet(Node* root) {\n"
               "    if(!root) return {0, 0};\n"
               "    auto left = maxIndependentSet(root->left), right = maxIndependentSet(root->right);\n"
               "    int inc = root->val + left.second + right.second;\n"
               "    int exc = max(left.first, left.second) + max(right.first, right.second);\n"
               "    return {inc, exc};\n}\n\n";
    }

    static std::string bitmaskDP() {
        return "int tsp(int mask, int pos, int n, vector<vector<int>>& dist, vector<vector<int>>& dp) {\n"
               "    if(mask == (1<<n)-1) return dist[pos][0];\n"
               "    if(dp[mask][pos] != -1) return dp[mask][pos];\n"
               "    int ans = 1e9;\n"
               "    for(int city=0; city<n; city++) if((mask & (1<<city)) == 0)\n"
               "        ans = min(ans, dist[pos][city] + tsp(mask | (1<<city), city, n, dist, dp));\n"
               "    return dp[mask][pos] = ans;\n}\n\n";
    }

    static std::string digitDP() {
        return "ll dp[20][2][2][200]; // pos, tight, leading_zeros, sum\n"
               "ll solveDigit(string& s, int pos, bool tight, bool leading_zeros, int sum) {\n"
               "    if(pos == s.size()) return sum;\n"
               "    if(dp[pos][tight][leading_zeros][sum] != -1) return dp[pos][tight][leading_zeros][sum];\n"
               "    ll ans = 0; int limit = tight ? s[pos]-'0' : 9;\n"
               "    for(int i=0; i<=limit; i++) ans += solveDigit(s, pos+1, tight && (i == limit), leading_zeros && (i == 0), sum + i);\n"
               "    return dp[pos][tight][leading_zeros][sum] = ans;\n}\n\n";
    }

    static std::string matrixExp() {
        return "struct Matrix {\n"
               "    ll mat[2][2]; Matrix() { memset(mat, 0, sizeof(mat)); }\n"
               "    static Matrix identity() { Matrix res; res.mat[0][0] = res.mat[1][1] = 1; return res; }\n"
               "    Matrix operator*(const Matrix& o) const {\n"
               "        Matrix res; for(int i=0; i<2; i++) for(int j=0; j<2; j++) for(int k=0; k<2; k++)\n"
               "            res.mat[i][j] = (res.mat[i][j] + mat[i][k] * o.mat[k][j]) % MOD;\n"
               "        return res;\n"
               "    }\n};\n"
               "Matrix power(Matrix a, ll b) {\n"
               "    Matrix res = Matrix::identity();\n"
               "    while(b > 0) { if(b & 1) res = res * a; a = a * a; b >>= 1; }\n"
               "    return res;\n}\n\n";
    }

    /* =========================================
       4. STACKS & QUEUES EXPERT
       ========================================= */

    static std::string validParentheses() {
        return "bool isValid(string s) {\n"
               "    stack<char> st;\n"
               "    for(char c : s) {\n"
               "        if(c=='(' || c=='{' || c=='[') st.push(c);\n"
               "        else {\n"
               "            if(st.empty()) return false;\n"
               "            if((c==')' && st.top()=='(') || (c=='}' && st.top()=='{') || (c==']' && st.top()=='[')) st.pop();\n"
               "            else return false;\n"
               "        }\n"
               "    } return st.empty();\n}\n\n";
    }

    static std::string nextGreater() {
        return "vector<int> nextGreater(vector<int>& a) {\n"
               "    int n = a.size(); vector<int> res(n, -1); stack<int> st;\n"
               "    for(int i = 2*n - 1; i >= 0; i--) {\n"
               "        while(!st.empty() && st.top() <= a[i%n]) st.pop();\n"
               "        if(i < n && !st.empty()) res[i] = st.top();\n"
               "        st.push(a[i%n]);\n"
               "    } return res;\n}\n\n";
    }

    static std::string histogramArea() {
        return "int largestRectangleArea(vector<int>& h) {\n"
               "    int n = h.size(), maxA = 0; stack<int> st;\n"
               "    for(int i=0; i<=n; i++) {\n"
               "        while(!st.empty() && (i==n || h[st.top()] >= h[i])) {\n"
               "            int height = h[st.top()]; st.pop();\n"
               "            int width = st.empty() ? i : i - st.top() - 1;\n"
               "            maxA = max(maxA, height * width);\n"
               "        } st.push(i);\n"
               "    } return maxA;\n}\n\n";
    }

    static std::string slidingWindowMax() {
        return "vector<int> maxSlidingWindow(vector<int>& nums, int k) {\n"
               "    deque<int> dq; vector<int> res;\n"
               "    for(int i=0; i<nums.size(); i++) {\n"
               "        if(!dq.empty() && dq.front() == i-k) dq.pop_front();\n"
               "        while(!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();\n"
               "        dq.push_back(i); if(i >= k-1) res.push_back(nums[dq.front()]);\n"
               "    } return res;\n}\n\n";
    }

    static std::string lruCache() {
        return "class LRUCache {\n"
               "    int cap; list<pair<int,int>> l; unordered_map<int, list<pair<int,int>>::iterator> m;\n"
               "public:\n"
               "    LRUCache(int c) : cap(c) {}\n"
               "    int get(int k) {\n"
               "        if(m.find(k) == m.end()) return -1;\n"
               "        l.splice(l.begin(), l, m[k]); return m[k]->second;\n"
               "    }\n"
               "    void put(int k, int v) {\n"
               "        if(m.count(k)) { m[k]->second = v; l.splice(l.begin(), l, m[k]); return; }\n"
               "        if(l.size() == cap) { m.erase(l.back().first); l.pop_back(); }\n"
               "        l.push_front({k, v}); m[k] = l.begin();\n"
               "    }\n};\n\n";
    }

    static std::string removeKDigits() {
        return "string removeKdigits(string num, int k) {\n"
               "    string res = \"\";\n"
               "    for(char c : num) {\n"
               "        while(res.size() && res.back() > c && k) { res.pop_back(); k--; }\n"
               "        if(res.size() || c != '0') res.push_back(c);\n"
               "    }\n"
               "    while(res.size() && k--) res.pop_back();\n"
               "    return res.empty() ? \"0\" : res;\n}\n\n";
    }

    /* =========================================
       5. LINEAR & TWO POINTERS EXPERT
       ========================================= */

    static std::string threeSum() {
        return "vector<vector<int>> threeSum(vector<int>& nums) {\n"
               "    sort(nums.begin(), nums.end()); vector<vector<int>> res;\n"
               "    for(int i=0; i<nums.size(); i++) {\n"
               "        if(i>0 && nums[i] == nums[i-1]) continue;\n"
               "        int l = i+1, r = nums.size()-1;\n"
               "        while(l < r) {\n"
               "            int sum = nums[i] + nums[l] + nums[r];\n"
               "            if(sum == 0) {\n"
               "                res.push_back({nums[i], nums[l], nums[r]});\n"
               "                while(l<r && nums[l] == nums[l+1]) l++;\n"
               "                while(l<r && nums[r] == nums[r-1]) r--;\n"
               "                l++; r--;\n"
               "            } else if(sum < 0) l++; else r--;\n"
               "        }\n"
               "    } return res;\n}\n\n";
    }

    static std::string trappingRainWater() {
        return "int trap(vector<int>& h) {\n"
               "    int l = 0, r = h.size()-1, lMax = 0, rMax = 0, res = 0;\n"
               "    while(l <= r) {\n"
               "        if(h[l] <= h[r]) {\n"
               "            if(h[l] >= lMax) lMax = h[l]; else res += lMax - h[l]; l++;\n"
               "        } else {\n"
               "            if(h[r] >= rMax) rMax = h[r]; else res += rMax - h[r]; r--;\n"
               "        }\n"
               "    } return res;\n}\n\n";
    }

    static std::string containerWithMostWater() {
        return "int maxArea(vector<int>& height) {\n"
               "    int l = 0, r = height.size() - 1, mx = 0;\n"
               "    while(l < r) {\n"
               "        mx = max(mx, min(height[l], height[r]) * (r - l));\n"
               "        if(height[l] < height[r]) l++; else r--;\n"
               "    } return mx;\n}\n\n";
    }

    static std::string slidingWindowVariable() {
        return "int minSubArrayLen(int target, vector<int>& nums) {\n"
               "    int l = 0, sum = 0, minLen = 1e9;\n"
               "    for(int r=0; r<nums.size(); r++) {\n"
               "        sum += nums[r];\n"
               "        while(sum >= target) { minLen = min(minLen, r-l+1); sum -= nums[l++]; }\n"
               "    } return minLen == 1e9 ? 0 : minLen;\n}\n\n";
    }

    /* =========================================
       6. LINKED LIST EXPERT
       ========================================= */

    static std::string reverseLL() {
        return "ListNode* reverseList(ListNode* head) {\n"
               "    ListNode *prev = NULL, *curr = head;\n"
               "    while(curr) { ListNode* next = curr->next; curr->next = prev; prev = curr; curr = next; }\n"
               "    return prev;\n}\n\n";
    }

    static std::string reverseKGroup() {
        return "ListNode* reverseKGroup(ListNode* head, int k) {\n"
               "    ListNode* curr = head; for(int i=0; i<k; i++) { if(!curr) return head; curr = curr->next; }\n"
               "    ListNode *prev = NULL, *nxt = NULL; curr = head;\n"
               "    for(int i=0; i<k; i++) { nxt = curr->next; curr->next = prev; prev = curr; curr = nxt; }\n"
               "    head->next = reverseKGroup(curr, k); return prev;\n}\n\n";
    }

    static std::string detectCycle() {
        return "ListNode* detectCycle(ListNode* head) {\n"
               "    ListNode *slow = head, *fast = head;\n"
               "    while(fast && fast->next) {\n"
               "        slow = slow->next; fast = fast->next->next;\n"
               "        if(slow == fast) {\n"
               "            slow = head; while(slow != fast) { slow = slow->next; fast = fast->next; }\n"
               "            return slow;\n"
               "        }\n"
               "    } return NULL;\n}\n\n";
    }

    static std::string flattenLL() {
        return "ListNode* merge(ListNode* a, ListNode* b) {\n"
               "    if(!a) return b; if(!b) return a;\n"
               "    ListNode* res; if(a->val < b->val) { res = a; res->bottom = merge(a->bottom, b); }\n"
               "    else { res = b; res->bottom = merge(a, b->bottom); }\n"
               "    return res;\n}\n"
               "ListNode* flatten(ListNode* root) {\n"
               "    if(!root || !root->next) return root;\n"
               "    return merge(root, flatten(root->next));\n}\n\n";
    }

    static std::string mergeSortLL() {
        return "ListNode* sortList(ListNode* head) {\n"
               "    if(!head || !head->next) return head;\n"
               "    ListNode *slow = head, *fast = head->next;\n"
               "    while(fast && fast->next) { slow = slow->next; fast = fast->next->next; }\n"
               "    ListNode* mid = slow->next; slow->next = NULL;\n"
               "    return merge(sortList(head), sortList(mid)); // assuming standard merge logic\n}\n\n";
    }

    /* =========================================
       7. HEAPS & HASHING EXPERT
       ========================================= */

    static std::string kthLargest() {
        return "int findKthLargest(vector<int>& nums, int k) {\n"
               "    priority_queue<int, vector<int>, greater<int>> pq;\n"
               "    for(int x : nums) { pq.push(x); if(pq.size() > k) pq.pop(); }\n"
               "    return pq.top();\n}\n\n";
    }

    static std::string medianInStream() {
        return "class MedianFinder {\n"
               "    priority_queue<int> maxH;\n"
               "    priority_queue<int, vector<int>, greater<int>> minH;\n"
               "public:\n"
               "    void addNum(int num) {\n"
               "        maxH.push(num); minH.push(maxH.top()); maxH.pop();\n"
               "        if(minH.size() > maxH.size()) { maxH.push(minH.top()); minH.pop(); }\n"
               "    }\n"
               "    double findMedian() {\n"
               "        return maxH.size() > minH.size() ? maxH.top() : (maxH.top() + minH.top()) / 2.0;\n"
               "    }\n};\n\n";
    }

    static std::string mergeKLists() {
        return "struct cmp { bool operator()(ListNode* a, ListNode* b) { return a->val > b->val; } };\n"
               "ListNode* mergeKLists(vector<ListNode*>& lists) {\n"
               "    priority_queue<ListNode*, vector<ListNode*>, cmp> pq;\n"
               "    for(auto l : lists) if(l) pq.push(l);\n"
               "    ListNode* dummy = new ListNode(0), *curr = dummy;\n"
               "    while(!pq.empty()) {\n"
               "        ListNode* top = pq.top(); pq.pop(); curr->next = top; curr = curr->next;\n"
               "        if(top->next) pq.push(top->next);\n"
               "    } return dummy->next;\n}\n\n";
    }

    static std::string subarraySumK() {
        return "int subarraySum(vector<int>& nums, int k) {\n"
               "    unordered_map<int, int> mp; mp[0] = 1;\n"
               "    int sum = 0, count = 0;\n"
               "    for(int x : nums) { sum += x; if(mp.count(sum - k)) count += mp[sum - k]; mp[sum]++; }\n"
               "    return count;\n}\n\n";
    }

    static std::string longestConsecutive() {
        return "int longestConsecutive(vector<int>& nums) {\n"
               "    unordered_set<int> s(nums.begin(), nums.end()); int mx = 0;\n"
               "    for(int x : nums) if(!s.count(x - 1)) {\n"
               "        int curr = x, len = 1; while(s.count(curr + 1)) { curr++; len++; } mx = max(mx, len);\n"
               "    } return mx;\n}\n\n";
    }

    /* =========================================
       8. STRINGS EXPERT
       ========================================= */

    static std::string kmp() {
        return "vector<int> kmp(string txt, string pat) {\n"
               "    int n = txt.size(), m = pat.size(); vector<int> lps(m, 0), res;\n"
               "    for(int i=1, j=0; i<m; i++) {\n"
               "        while(j > 0 && pat[i] != pat[j]) j = lps[j-1];\n"
               "        if(pat[i] == pat[j]) j++; lps[i] = j;\n"
               "    }\n"
               "    for(int i=0, j=0; i<n; i++) {\n"
               "        while(j > 0 && txt[i] != pat[j]) j = lps[j-1];\n"
               "        if(txt[i] == pat[j]) j++;\n"
               "        if(j == m) { res.push_back(i - m + 1); j = lps[j-1]; }\n"
               "    } return res;\n}\n\n";
    }

    static std::string zAlgo() {
        return "vector<int> z_function(string s) {\n"
               "    int n = s.size(); vector<int> z(n, 0);\n"
               "    for(int i=1, l=0, r=0; i<n; i++) {\n"
               "        if(i <= r) z[i] = min(r - i + 1, z[i - l]);\n"
               "        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;\n"
               "        if(i + z[i] - 1 > r) { l = i; r = i + z[i] - 1; }\n"
               "    } return z;\n}\n\n";
    }

    static std::string trie() {
        return "struct TrieNode {\n"
               "    TrieNode* child[26]; bool isEnd;\n"
               "    TrieNode() { isEnd = false; for(int i=0; i<26; i++) child[i] = NULL; }\n"
               "};\n"
               "class Trie {\n"
               "    TrieNode* root = new TrieNode();\n"
               "public:\n"
               "    void insert(string s) {\n"
               "        TrieNode* curr = root; for(char c : s) { if(!curr->child[c-'a']) curr->child[c-'a'] = new TrieNode(); curr = curr->child[c-'a']; }\n"
               "        curr->isEnd = true;\n"
               "    }\n"
               "    bool search(string s) {\n"
               "        TrieNode* curr = root; for(char c : s) { if(!curr->child[c-'a']) return false; curr = curr->child[c-'a']; }\n"
               "        return curr->isEnd;\n"
               "    }\n};\n\n";
    }

    static std::string manacher() {
        return "string manacher(string s) {\n"
               "    string t = \"#\"; for(char c : s) t += c, t += \"#\";\n"
               "    int n = t.size(); vector<int> p(n, 0);\n"
               "    int c = 0, r = 0, mx = 0, center = 0;\n"
               "    for(int i=0; i<n; i++) {\n"
               "        if(i < r) p[i] = min(r-i, p[2*c-i]);\n"
               "        while(i+1+p[i]<n && i-1-p[i]>=0 && t[i+1+p[i]] == t[i-1-p[i]]) p[i]++;\n"
               "        if(i+p[i] > r) c = i, r = i+p[i];\n"
               "        if(p[i] > mx) mx = p[i], center = i;\n"
               "    } return s.substr((center-mx)/2, mx);\n}\n\n";
    }

    static std::string rabinKarp() {
        return "void rabinKarp(string txt, string pat) {\n"
               "    int n = txt.size(), m = pat.size(); ll p = 31, pow_m = 1, h_pat = 0, h_txt = 0;\n"
               "    for(int i=0; i<m-1; i++) pow_m = (pow_m * p) % MOD;\n"
               "    for(int i=0; i<m; i++) { h_pat = (h_pat * p + pat[i]) % MOD; h_txt = (h_txt * p + txt[i]) % MOD; }\n"
               "    for(int i=0; i <= n-m; i++) {\n"
               "        if(h_pat == h_txt) cout << \"Match at \" << i << endl;\n"
               "        if(i < n-m) { h_txt = (p * (h_txt - txt[i] * pow_m) + txt[i+m]) % MOD; if(h_txt < 0) h_txt += MOD; }\n"
               "    }\n}\n\n";
    }

    /* =========================================
       9. SEARCH & MATH EXPERT
       ========================================= */

    static std::string bsOnAnswer() {
        return "ll solveBS(vector<int>& a) {\n"
               "    ll low = 0, high = 1e18, ans = 0;\n"
               "    while(low <= high) {\n"
               "        ll mid = low + (high-low)/2;\n"
               "        if(check(mid, a)) { ans = mid; low = mid + 1; } // or high = mid - 1 based on monotonic condition\n"
               "        else high = mid - 1;\n"
               "    } return ans;\n}\n\n";
    }

    static std::string sieve() {
        return "vector<int> sieve(int n) {\n"
               "    vector<int> is_prime(n+1, 1), primes;\n"
               "    is_prime[0] = is_prime[1] = 0;\n"
               "    for(int p=2; p*p<=n; p++) if(is_prime[p]) for(int i=p*p; i<=n; i+=p) is_prime[i] = 0;\n"
               "    for(int p=2; p<=n; p++) if(is_prime[p]) primes.push_back(p);\n"
               "    return primes;\n}\n\n";
    }

    static std::string modExp() {
        return "ll power(ll a, ll b) {\n"
               "    ll res = 1; a %= MOD; \n"
               "    while (b > 0) { if (b & 1) res = res * a % MOD; a = a * a % MOD; b >>= 1; }\n"
               "    return res;\n}\n\n"
               "ll modInverse(ll n) { return power(n, MOD - 2); }\n\n";
    }

    static std::string nCr() {
        return "ll nCr(int n, int r, vector<ll>& fact) {\n"
               "    if (r < 0 || r > n) return 0;\n"
               "    ll num = fact[n];\n"
               "    ll den = (modInverse(fact[r]) * modInverse(fact[n - r])) % MOD;\n"
               "    return (num * den) % MOD;\n}\n\n";
    }

    static std::string bitManip() {
        return "bool isPowerOfTwo(ll n) { return n > 0 && (n & (n - 1)) == 0; }\n"
               "int countSetBits(ll n) { return __builtin_popcountll(n); }\n"
               "int findUniqueInPairs(vector<int>& a) { int res = 0; for(int x : a) res ^= x; return res; }\n\n";
    }
};

#endif