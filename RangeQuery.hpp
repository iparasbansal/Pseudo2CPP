#ifndef RANGE_QUERY_EXPERT_HPP
#define RANGE_QUERY_EXPERT_HPP

#include <bits/stdc++.h>
using namespace std;

class RangeQueryExpert {
public:
    // 1. Lazy Segment Tree: Range Updates + Range Queries
    static string getLazySegmentTree() {
        return "struct LazySegTree {\n"
               "    int n; vector<ll> tree, lazy;\n"
               "    LazySegTree(int n) : n(n) { tree.assign(4*n, 0); lazy.assign(4*n, 0); }\n"
               "    void push(int v, int tl, int tr) {\n"
               "        if (lazy[v] != 0) {\n"
               "            tree[2*v] += lazy[v] * ( (tl+tr)/2 - tl + 1 );\n"
               "            lazy[2*v] += lazy[v];\n"
               "            tree[2*v+1] += lazy[v] * ( tr - (tl+tr)/2 );\n"
               "            lazy[2*v+1] += lazy[v]; lazy[v] = 0;\n"
               "        }\n"
               "    }\n"
               "    void update(int v, int tl, int tr, int l, int r, ll add) {\n"
               "        if (l > r) return;\n"
               "        if (l == tl && r == tr) { tree[v] += add * (tr - tl + 1); lazy[v] += add; }\n"
               "        else {\n"
               "            push(v, tl, tr); int tm = (tl + tr) / 2;\n"
               "            update(2*v, tl, tm, l, min(r, tm), add);\n"
               "            update(2*v+1, tm+1, tr, max(l, tm+1), r, add);\n"
               "            tree[v] = tree[2*v] + tree[2*v+1];\n"
               "        }\n"
               "    }\n"
               "    ll query(int v, int tl, int tr, int l, int r) {\n"
               "        if (l > r) return 0;\n"
               "        if (l == tl && r == tr) return tree[v];\n"
               "        push(v, tl, tr); int tm = (tl + tr) / 2;\n"
               "        return query(2*v, tl, tm, l, min(r, tm)) + query(2*v+1, tm+1, tr, max(l, tm+1), r);\n"
               "    }\n"
               "};\n\n";
    }

    // 2. Sparse Table: O(1) Range Minimum Query after O(N log N) build
    static string getSparseTable() {
        return "struct SparseTable {\n"
               "    int n, LOG; vector<vector<int>> st;\n"
               "    SparseTable(vector<int>& a) {\n"
               "        n = a.size(); LOG = log2(n) + 1;\n"
               "        st.assign(n, vector<int>(LOG));\n"
               "        for(int i=0; i<n; i++) st[i][0] = a[i];\n"
               "        for(int j=1; j<LOG; j++) {\n"
               "            for(int i=0; i+(1<<j)<=n; i++)\n"
               "                st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);\n"
               "        }\n"
               "    }\n"
               "    int query(int l, int r) {\n"
               "        int j = log2(r - l + 1);\n"
               "        return min(st[l][j], st[r - (1<<j) + 1][j]);\n"
               "    }\n"
               "};\n\n";
    }
};

#endif