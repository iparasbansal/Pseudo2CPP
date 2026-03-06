#ifndef STRING_EXPERT_HPP
#define STRING_EXPERT_HPP

#include <bits/stdc++.h>
using namespace std;

class StringExpert {
public:

    /* --- 1. PATTERN MATCHING (Linear Time) --- */

    // KMP Algorithm: O(N + M) using Prefix Function
    static string getKMP() {
        return "vector<int> computeLPS(string pat) {\n"
               "    int m = pat.size(); vector<int> lps(m, 0);\n"
               "    for (int i = 1, j = 0; i < m; i++) {\n"
               "        while (j > 0 && pat[i] != pat[j]) j = lps[j-1];\n"
               "        if (pat[i] == pat[j]) j++; lps[i] = j;\n"
               "    } return lps;\n"
               "}\n"
               "vector<int> kmpSearch(string txt, string pat) {\n"
               "    vector<int> lps = computeLPS(pat), res;\n"
               "    for (int i = 0, j = 0; i < txt.size(); i++) {\n"
               "        while (j > 0 && txt[i] != pat[j]) j = lps[j-1];\n"
               "        if (txt[i] == pat[j]) j++;\n"
               "        if (j == pat.size()) { res.push_back(i - j + 1); j = lps[j-1]; }\n"
               "    } return res;\n}\n\n";
    }

    // Z-Algorithm: Linear time string matching using Z-array
    static string getZAlgorithm() {
        return "vector<int> z_function(string s) {\n"
               "    int n = s.size(); vector<int> z(n, 0);\n"
               "    for (int i = 1, l = 0, r = 0; i < n; i++) {\n"
               "        if (i <= r) z[i] = min(r - i + 1, z[i - l]);\n"
               "        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;\n"
               "        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;\n"
               "    } return z;\n}\n\n";
    }

    /* --- 2. PREFIX TREES (The Trie Specialist) --- */

    
    static string getTrie() {
        return "struct TrieNode {\n"
               "    TrieNode *child[26]; bool isEnd;\n"
               "    TrieNode() { isEnd = false; for(int i=0; i<26; i++) child[i] = NULL; }\n"
               "};\n"
               "class Trie {\n"
               "    TrieNode* root;\n"
               "public:\n"
               "    Trie() { root = new TrieNode(); }\n"
               "    void insert(string s) {\n"
               "        TrieNode* curr = root;\n"
               "        for(char c : s) { if(!curr->child[c-'a']) curr->child[c-'a'] = new TrieNode(); curr = curr->child[c-'a']; }\n"
               "        curr->isEnd = true;\n"
               "    }\n"
               "    bool startsWith(string prefix) {\n"
               "        TrieNode* curr = root;\n"
               "        for(char c : prefix) { if(!curr->child[c-'a']) return false; curr = curr->child[c-'a']; }\n"
               "        return true;\n"
               "    }\n};\n\n";
    }

    /* --- 3. PALINDROME OPTIMIZATION --- */

    
    // Manacher's Algorithm: O(N) for Longest Palindromic Substring
    static string getManachers() {
        return "string longestPalindrome(string s) {\n"
               "    string t = \"#\"; for(char c : s) { t += c; t += \"#\"; }\n"
               "    int n = t.size(); vector<int> p(n, 0);\n"
               "    int c = 0, r = 0, maxLen = 0, centerIndex = 0;\n"
               "    for(int i = 0; i < n; i++) {\n"
               "        int mirror = 2*c - i;\n"
               "        if(i < r) p[i] = min(r - i, p[mirror]);\n"
               "        while(i + 1 + p[i] < n && i - 1 - p[i] >= 0 && t[i + 1 + p[i]] == t[i - 1 - p[i]]) p[i]++;\n"
               "        if(i + p[i] > r) { c = i; r = i + p[i]; }\n"
               "        if(p[i] > maxLen) { maxLen = p[i]; centerIndex = i; }\n"
               "    } return s.substr((centerIndex - maxLen)/2, maxLen);\n}\n\n";
    }

    /* --- 4. ROLLING HASH --- */

    // Rabin-Karp: Pattern matching using rolling hash
    static string getRabinKarp() {
        return "void rabinKarp(string txt, string pat) {\n"
               "    int n = txt.size(), m = pat.size(); ll p = 31, m_val = 1e9+9;\n"
               "    vector<ll> h(n + 1, 0), p_pow(n + 1, 1);\n"
               "    for(int i=0; i<n; i++) p_pow[i+1] = (p_pow[i] * p) % m_val;\n"
               "    for(int i=0; i<n; i++) h[i+1] = (h[i] + (txt[i]-'a'+1) * p_pow[i]) % m_val;\n"
               "    ll h_pat = 0; for(int i=0; i<m; i++) h_pat = (h_pat + (pat[i]-'a'+1) * p_pow[i]) % m_val;\n"
               "    for(int i=0; i <= n-m; i++) {\n"
               "        ll cur_h = (h[i+m] + m_val - h[i]) % m_val;\n"
               "        if(cur_h == (h_pat * p_pow[i]) % m_val) cout << \"Match at \" << i << endl;\n"
               "    }\n}\n\n";
    }
};

#endif