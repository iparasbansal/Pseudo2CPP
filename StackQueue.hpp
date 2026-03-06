#ifndef STACKS_QUEUES_EXPERT_HPP
#define STACKS_QUEUES_EXPERT_HPP

#include <bits/stdc++.h>
using namespace std;

class StacksQueuesExpert {
public:

    /* --- 1. CORE DESIGN PATTERNS --- */

    // Valid Parentheses: The Foundation of Stack Parsing
    static string getValidParentheses() {
        return "bool isValid(string s) {\n"
               "    stack<char> st; for(char c : s) {\n"
               "        if(c=='(' || c=='{' || c=='[') st.push(c);\n"
               "        else {\n"
               "            if(st.empty()) return false;\n"
               "            if((c==')' && st.top()=='(') || (c=='}' && st.top()=='{') || (c==']' && st.top()=='[')) st.pop();\n"
               "            else return false;\n"
               "        }\n"
               "    } return st.empty();\n}\n\n";
    }

    // Min Stack: O(1) Time for getMin() using Pair/Math
    static string getMinStack() {
        return "struct MinStack {\n"
               "    stack<pair<int, int>> st;\n"
               "    void push(int val) { int mn = st.empty() ? val : min(val, st.top().second); st.push({val, mn}); }\n"
               "    void pop() { st.pop(); } int top() { return st.top().first; } int getMin() { return st.top().second; }\n"
               "};\n\n";
    }

    /* --- 2. MONOTONIC STACK (The Placement Specialist) --- */

    // Next Greater Element: Circular Array Variation
    static string getNextGreater() {
        return "vector<int> nextGreater(vector<int>& a) {\n"
               "    int n = a.size(); vector<int> res(n, -1); stack<int> st;\n"
               "    for(int i = 2*n - 1; i >= 0; i--) {\n"
               "        while(!st.empty() && st.top() <= a[i%n]) st.pop();\n"
               "        if(i < n && !st.empty()) res[i] = st.top();\n"
               "        st.push(a[i%n]);\n"
               "    } return res;\n}\n\n";
    }

    // Largest Rectangle in Histogram: Single Pass O(N)
    
    static string getHistogram() {
        return "int largestRectangle(vector<int>& h) {\n"
               "    int n = h.size(), maxA = 0; stack<int> st;\n"
               "    for(int i=0; i<=n; i++) {\n"
               "        while(!st.empty() && (i==n || h[st.top()] >= h[i])) {\n"
               "            int height = h[st.top()]; st.pop();\n"
               "            int width = st.empty() ? i : i - st.top() - 1;\n"
               "            maxA = max(maxA, height * width);\n"
               "        } st.push(i);\n"
               "    } return maxA;\n}\n\n";
    }

    /* --- 3. QUEUE & DEQUE (Advanced Window Logic) --- */

    // Sliding Window Maximum: The Monotonic Deque Pattern
    
    static string getSlidingWindowMax() {
        return "vector<int> maxSlidingWindow(vector<int>& nums, int k) {\n"
               "    deque<int> dq; vector<int> res;\n"
               "    for(int i=0; i<nums.size(); i++) {\n"
               "        if(!dq.empty() && dq.front() == i-k) dq.pop_front();\n"
               "        while(!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();\n"
               "        dq.push_back(i); if(i >= k-1) res.push_back(nums[dq.front()]);\n"
               "    } return res;\n}\n\n";
    }

    // First Negative in every window of size K
    static string getFirstNegative() {
        return "vector<long long> firstNegative(vector<long long> a, int n, int k) {\n"
               "    deque<int> dq; vector<long long> res;\n"
               "    for(int i=0; i<n; i++) {\n"
               "        if(!dq.empty() && dq.front() == i-k) dq.pop_front();\n"
               "        if(a[i] < 0) dq.push_back(i);\n"
               "        if(i >= k-1) res.push_back(dq.empty() ? 0 : a[dq.front()]);\n"
               "    } return res;\n}\n\n";
    }

    /* --- 4. SYSTEM & GREEDY VARIATIONS --- */

    // LRU Cache: O(1) Operations using List + Hashmap
    
    static string getLRUCache() {
        return "class LRUCache {\n"
               "    int cap; list<pair<int, int>> l; unordered_map<int, list<pair<int, int>>::iterator> m;\n"
               "public:\n"
               "    LRUCache(int n) : cap(n) {}\n"
               "    int get(int k) {\n"
               "        if(m.find(k) == m.end()) return -1;\n"
               "        l.splice(l.begin(), l, m[k]); return m[k]->second;\n"
               "    }\n"
               "    void put(int k, int v) {\n"
               "        if(get(k) != -1) { m[k]->second = v; return; }\n"
               "        if(l.size() == cap) { m.erase(l.back().first); l.pop_back(); }\n"
               "        l.push_front({k, v}); m[k] = l.begin();\n"
               "    }\n};\n\n";
    }

    // Remove K Digits: Greedy Stack Optimization
    static string getRemoveKDigits() {
        return "string removeKdigits(string num, int k) {\n"
               "    string res = \"\"; for(char c : num) {\n"
               "        while(res.size() && res.back() > c && k) { res.pop_back(); k--; }\n"
               "        if(res.size() || c != '0') res.push_back(c);\n"
               "    } while(res.size() && k--) res.pop_back();\n"
               "    return res.empty() ? \"0\" : res;\n}\n\n";
    }
};

#endif