#ifndef TREE_EXPERT_HPP
#define TREE_EXPERT_HPP

#include <string>

class TreeExpert {
public:

    /* --- 1. TRAVERSALS (Recursive & Iterative) --- */

    static std::string getTraversals() {
        return "// Recursive & Iterative Variations\n"
               "void preorder(Node* root) {\n"
               "    if(!root) return;\n"
               "    cout << root->val << \" \"; preorder(root->left); preorder(root->right);\n"
               "}\n\n"
               "vector<int> iterativeInorder(Node* root) {\n"
               "    vector<int> res; stack<Node*> s; Node* curr = root;\n"
               "    while(curr || !s.empty()) {\n"
               "        while(curr) { s.push(curr); curr = curr->left; }\n"
               "        curr = s.top(); s.pop(); res.push_back(curr->val);\n"
               "        curr = curr->right;\n"
               "    } return res;\n"
               "}\n\n";
    }

    /* --- 2. STRUCTURAL PROPERTIES --- */

    static std::string getProperties() {
        return "// Height, Diameter, Balanced, Symmetric\n"
               "int height(Node* root) {\n"
               "    if(!root) return 0;\n"
               "    return 1 + max(height(root->left), height(root->right));\n"
               "}\n\n"
               "// Optimized Diameter O(N)\n"
               "int diameter(Node* root, int& res) {\n"
               "    if(!root) return 0;\n"
               "    int l = diameter(root->left, res), r = diameter(root->right, res);\n"
               "    res = max(res, l + r); return 1 + max(l, r);\n"
               "}\n\n"
               "bool isBalanced(Node* root, int& h) {\n"
               "    if(!root) { h = 0; return true; }\n"
               "    int lh, rh; if(!isBalanced(root->left, lh) || !isBalanced(root->right, rh)) return false;\n"
               "    if(abs(lh - rh) > 1) return false;\n"
               "    h = 1 + max(lh, rh); return true;\n"
               "}\n\n"
               "bool isSymmetric(Node* l, Node* r) {\n"
               "    if(!l || !r) return l == r;\n"
               "    return (l->val == r->val) && isSymmetric(l->left, r->right) && isSymmetric(l->right, r->left);\n"
               "}\n\n";
    }

    /* --- 3. BINARY SEARCH TREE (BST) VARIATIONS --- */

    static std::string getBSTOps() {
        return "// BST Validation, Insertion, K-th Smallest\n"
               "bool isValidBST(Node* root, long minV, long maxV) {\n"
               "    if(!root) return true;\n"
               "    if(root->val <= minV || root->val >= maxV) return false;\n"
               "    return isValidBST(root->left, minV, root->val) && isValidBST(root->right, root->val, maxV);\n"
               "}\n\n"
               "Node* kthSmallest(Node* root, int& k) {\n"
               "    if(!root) return nullptr;\n"
               "    Node* left = kthSmallest(root->left, k);\n"
               "    if(left) return left;\n"
               "    if(--k == 0) return root;\n"
               "    return kthSmallest(root->right, k);\n"
               "}\n\n";
    }

    /* --- 4. ADVANCED PATHS & DISTANCES --- */

    static std::string getPathLogics() {
        return "// Maximum Path Sum & Burn Tree\n"
               "int maxPathSum(Node* root, int& res) {\n"
               "    if(!root) return 0;\n"
               "    int l = max(0, maxPathSum(root->left, res));\n"
               "    int r = max(0, maxPathSum(root->right, res));\n"
               "    res = max(res, l + r + root->val);\n"
               "    return root->val + max(l, r);\n"
               "}\n\n"
               "// Burn Tree: Time to burn entire tree from a target node\n"
               "int burnTree(Node* root, int target) {\n"
               "    map<Node*, Node*> parent; Node* startNode = nullptr;\n"
               "    // BFS to map parents and find target...\n"
               "    // Then second BFS to find max distance...\n"
               "    return maxTime;\n"
               "}\n\n";
    }

    /* --- 5. LOGARITHMIC LCA (Binary Lifting) --- */

    static std::string getLCA() {
        return "\n"
               "// Complexity: O(log N) Query | O(N log N) Preprocessing\n"
               "struct BinaryLiftingLCA {\n"
               "    int n, LOG; vector<vector<int>> up; vector<int> depth;\n"
               "    BinaryLiftingLCA(int nodes, vector<vector<int>>& adj) {\n"
               "        n = nodes; LOG = 20; \n"
               "        up.assign(n + 1, vector<int>(LOG)); depth.assign(n + 1, 0);\n"
               "        dfs(1, 1, adj);\n"
               "    }\n"
               "    void dfs(int u, int p, vector<vector<int>>& adj) {\n"
               "        up[u][0] = p;\n"
               "        for(int i=1; i<LOG; i++) up[u][i] = up[up[u][i-1]][i-1];\n"
               "        for(int v : adj[u]) if(v != p) { depth[v] = depth[u] + 1; dfs(v, u, adj); }\n"
               "    }\n"
               "    int getLCA(int u, int v) {\n"
               "        if(depth[u] < depth[v]) swap(u, v);\n"
               "        for(int i=LOG-1; i>=0; i--) if(depth[u] - (1<<i) >= depth[v]) u = up[u][i];\n"
               "        if(u == v) return u;\n"
               "        for(int i=LOG-1; i>=0; i--) if(up[u][i] != up[v][i]) { u = up[u][i]; v = up[v][i]; }\n"
               "        return up[u][0];\n"
               "    }\n};\n\n";
    }
};

#endif
