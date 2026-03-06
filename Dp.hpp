#ifndef DP_EXPERT_HPP
#define DP_EXPERT_HPP

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class DPExpert {
public:

    /* --- 1. CLASSICAL SELECTION (Knapsack Variations) --- */

    // 0/1 Knapsack: O(W) Space Optimization
    static string getKnapsack01() {
        return "int knapsack01(int W, vector<int>& wt, vector<int>& val, int n) {\n"
               "    vector<int> dp(W + 1, 0);\n"
               "    for (int i = 0; i < n; i++) \n"
               "        for (int w = W; w >= wt[i]; w--)\n"
               "            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);\n"
               "    return dp[W];\n}\n\n";
    }

    // Unbounded Knapsack: Infinite supply of items
    static string getUnboundedKnapsack() {
        return "int unboundedKnapsack(int W, vector<int>& wt, vector<int>& val, int n) {\n"
               "    vector<int> dp(W + 1, 0);\n"
               "    for (int i = 0; i <= W; i++)\n"
               "        for (int j = 0; j < n; j++)\n"
               "            if (wt[j] <= i) dp[i] = max(dp[i], dp[i - wt[j]] + val[j]);\n"
               "    return dp[W];\n}\n\n";
    }

    /* --- 2. GRID & PATH OPTIMIZATION --- */

    // Grid DP: Minimum Path Sum with O(M) Space
    static string getGridDP() {
        return "int minPathSum(vector<vector<int>>& grid) {\n"
               "    int n = grid.size(), m = grid[0].size();\n"
               "    vector<int> dp(m, 1e9); dp[0] = grid[0][0];\n"
               "    for (int j = 1; j < m; j++) dp[j] = dp[j-1] + grid[0][j];\n"
               "    for (int i = 1; i < n; i++) {\n"
               "        dp[0] += grid[i][0];\n"
               "        for (int j = 1; j < m; j++) dp[j] = grid[i][j] + min(dp[j], dp[j-1]);\n"
               "    } return dp[m-1];\n}\n\n";
    }

    /* --- 3. STATE MACHINES & STRINGS --- */

    // Stock DP: Buy, Sell, and Cooldown States
    // [Image of stock trading state machine with buy sell and cooldown]
    static string getStockDP() {
        return "int stockWithCooldown(vector<int>& prices) {\n"
               "    int sold = 0, hold = -1e9, rest = 0;\n"
               "    for (int p : prices) {\n"
               "        int prev_sold = sold;\n"
               "        sold = hold + p; hold = max(hold, rest - p); rest = max(rest, prev_sold);\n"
               "    } return max(sold, rest);\n}\n\n";
    }

    // LCS: Longest Common Subsequence (Space Optimized)
    static string getLCS() {
        return "int lcs(string& s1, string& s2) {\n"
               "    int n = s1.size(), m = s2.size();\n"
               "    vector<int> prev(m + 1, 0), curr(m + 1, 0);\n"
               "    for (int i = 1; i <= n; i++) {\n"
               "        for (int j = 1; j <= m; j++) {\n"
               "            if (s1[i - 1] == s2[j - 1]) curr[j] = 1 + prev[j - 1];\n"
               "            else curr[j] = max(prev[j], curr[j - 1]);\n"
               "        } prev = curr;\n"
               "    } return prev[m];\n}\n\n";
    }

    /* --- 4. PARTITION & TREE STRUCTURES --- */

    // Partition DP: Matrix Chain Multiplication (MCM)
    // [Image of matrix chain multiplication recursive tree]
    static string getPartitionDP() {
        return "int mcm(vector<int>& p, int n) {\n"
               "    vector<vector<int>> dp(n, vector<int>(n, 0));\n"
               "    for (int len = 2; len < n; len++) {\n"
               "        for (int i = 1; i < n - len + 1; i++) {\n"
               "            int j = i + len - 1; dp[i][j] = 1e9;\n"
               "            for (int k = i; k < j; k++)\n"
               "                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j]);\n"
               "        }\n"
               "    } return dp[1][n-1];\n}\n\n";
    }

    // DP on Trees: Node Selection logic
    // [Image of dynamic programming on trees state transitions]
    static string getTreeDP() {
        return "pair<int, int> solveTreeDP(Node* root) {\n"
               "    if (!root) return {0, 0};\n"
               "    auto left = solveTreeDP(root->left), right = solveTreeDP(root->right);\n"
               "    int include = root->val + left.second + right.second;\n"
               "    int exclude = max(left.first, left.second) + max(right.first, right.second);\n"
               "    return {include, exclude};\n}\n\n";
    }

    /* --- 5. ADVANCED & MATH OPTIMIZATION --- */

    // Bitmask DP: Traveling Salesperson Problem (TSP)
    static string getBitmaskDP() {
        return "int tsp(int mask, int pos, int n, vector<vector<int>>& dist, vector<vector<int>>& dp) {\n"
               "    if (mask == (1 << n) - 1) return dist[pos][0];\n"
               "    if (dp[mask][pos] != -1) return dp[mask][pos];\n"
               "    int ans = 1e9;\n"
               "    for (int city = 0; city < n; city++) \n"
               "        if ((mask & (1 << city)) == 0)\n"
               "            ans = min(ans, dist[pos][city] + tsp(mask | (1 << city), city, n, dist, dp));\n"
               "    return dp[mask][pos] = ans;\n}\n\n";
    }

    // Matrix Exponentiation: Recurrence optimization
    // [Image of matrix exponentiation for linear recurrence relation]
    static string getMatrixExp() {
        return "struct Matrix {\n"
               "    ll mat[2][2];\n"
               "    Matrix() { memset(mat, 0, sizeof(mat)); }\n"
               "    static Matrix identity() { Matrix res; res.mat[0][0] = res.mat[1][1] = 1; return res; }\n"
               "    Matrix operator*(const Matrix& other) const {\n"
               "        Matrix res; for(int i=0; i<2; i++) for(int j=0; j<2; j++) for(int k=0; k<2; k++)\n"
               "            res.mat[i][j] = (res.mat[i][j] + mat[i][k] * other.mat[k][j]) % 1000000007;\n"
               "        return res;\n"
               "    }\n};\n\n";
    }
};

#endif