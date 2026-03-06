#ifndef HEAP_EXPERT_HPP
#define HEAP_EXPERT_HPP

#include <bits/stdc++.h>
using namespace std;

class HeapExpert {
public:

    /* --- 1. CORE SELECTION LOGIC --- */

    // K-th Largest Element: O(N log K) Time | O(K) Space
    static string getKthLargest() {
        return "int findKthLargest(vector<int>& nums, int k) {\n"
               "    priority_queue<int, vector<int>, greater<int>> minHeap;\n"
               "    for (int x : nums) {\n"
               "        minHeap.push(x);\n"
               "        if (minHeap.size() > k) minHeap.pop();\n"
               "    } return minHeap.top();\n}\n\n";
    }

    /* --- 2. THE "TWO-HEAP" PATTERN (Top-Tier Quality) --- */

    // Median in a Stream: Continuous O(log N) updates
    static string getMedianInStream() {
        return "// MedianFinder using Max-Heap (left half) and Min-Heap (right half)\n"
               "class MedianFinder {\n"
               "    priority_queue<int> maxH; // Left side\n"
               "    priority_queue<int, vector<int>, greater<int>> minH; // Right side\n"
               "public:\n"
               "    void addNum(int num) {\n"
               "        maxH.push(num);\n"
               "        minH.push(maxH.top()); maxH.pop();\n"
               "        if (minH.size() > maxH.size()) { maxH.push(minH.top()); minH.pop(); }\n"
               "    }\n"
               "    double findMedian() {\n"
               "        if (maxH.size() > minH.size()) return maxH.top();\n"
               "        return (maxH.top() + minH.top()) / 2.0;\n"
               "    }\n};\n\n";
    }

    /* --- 3. MULTI-STREAM MERGING --- */

    // Merge K Sorted Lists: O(Total_Elements * log K)
    static string getMergeKSorted() {
        return "struct NodeComparator { \n"
               "    bool operator()(ListNode* a, ListNode* b) { return a->val > b->val; }\n"
               "};\n"
               "ListNode* mergeKLists(vector<ListNode*>& lists) {\n"
               "    priority_queue<ListNode*, vector<ListNode*>, NodeComparator> pq;\n"
               "    for (auto l : lists) if (l) pq.push(l);\n"
               "    ListNode* dummy = new ListNode(0), *curr = dummy;\n"
               "    while (!pq.empty()) {\n"
               "        ListNode* top = pq.top(); pq.pop();\n"
               "        curr->next = top; curr = curr->next;\n"
               "        if (top->next) pq.push(top->next);\n"
               "    } return dummy->next;\n}\n\n";
    }

    /* --- 4. FREQUENCY OPTIMIZATION --- */

    // Top K Frequent Elements: O(N log K)
    static string getTopKFrequent() {
        return "vector<int> topKFrequent(vector<int>& nums, int k) {\n"
               "    unordered_map<int, int> count; for (int x : nums) count[x]++;\n"
               "    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;\n"
               "    for (auto& it : count) {\n"
               "        pq.push({it.second, it.first});\n"
               "        if (pq.size() > k) pq.pop();\n"
               "    } \n"
               "    vector<int> res; while(!pq.empty()) { res.push_back(pq.top().second); pq.pop(); }\n"
               "    return res;\n}\n\n";
    }
};

#endif