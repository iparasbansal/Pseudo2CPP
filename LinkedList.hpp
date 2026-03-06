#ifndef LINKED_LIST_EXPERT_HPP
#define LINKED_LIST_EXPERT_HPP

#include <bits/stdc++.h>
using namespace std;

class LinkedListExpert {
public:

    /* --- 1. CORE MANIPULATION --- */

    // Reverse List: Iterative O(N) Time | O(1) Space
    static string getReverse() {
        return "ListNode* reverseList(ListNode* head) {\n"
               "    ListNode *prev = NULL, *curr = head;\n"
               "    while(curr) {\n"
               "        ListNode* next = curr->next;\n"
               "        curr->next = prev; prev = curr; curr = next;\n"
               "    } return prev;\n}\n\n";
    }

    // Reverse in K-Groups: The ultimate pointer challenge
    static string getReverseKGroups() {
        return "ListNode* reverseKGroup(ListNode* head, int k) {\n"
               "    ListNode* temp = head; for(int i=0; i<k; i++) { if(!temp) return head; temp = temp->next; }\n"
               "    ListNode *prev = NULL, *curr = head, *next = NULL;\n"
               "    for(int i=0; i<k; i++) {\n"
               "        next = curr->next; curr->next = prev; prev = curr; curr = next;\n"
               "    }\n"
               "    head->next = reverseKGroup(curr, k);\n"
               "    return prev;\n}\n\n";
    }

    /* --- 2. CYCLE & INTERSECTION (Floyd's Algorithm) --- */

    // Detect Cycle & Find Entry Point: O(N) Time | O(1) Space
    static string getCycleLogic() {
        return "\n"
               "ListNode* detectCycle(ListNode* head) {\n"
               "    ListNode *slow = head, *fast = head;\n"
               "    while(fast && fast->next) {\n"
               "        slow = slow->next; fast = fast->next->next;\n"
               "        if(slow == fast) {\n"
               "            slow = head;\n"
               "            while(slow != fast) { slow = slow->next; fast = fast->next; }\n"
               "            return slow;\n"
               "        }\n"
               "    } return NULL;\n}\n\n";
    }

    /* --- 3. STRUCTURE TRANSFORMATION --- */

    // Flattening a Linked List (Sorted Merge logic)
    static string getFlattening() {
        return "ListNode* merge(ListNode* a, ListNode* b) {\n"
               "    if(!a) return b; if(!b) return a;\n"
               "    ListNode* res; if(a->val < b->val) { res = a; res->bottom = merge(a->bottom, b); }\n"
               "    else { res = b; res->bottom = merge(a, b->bottom); }\n"
               "    return res;\n}\n"
               "ListNode* flatten(ListNode* root) {\n"
               "    if(!root || !root->next) return root;\n"
               "    return merge(root, flatten(root->next));\n}\n\n";
    }

    /* --- 4. OPTIMIZATION & SORTING --- */

    // Merge Sort on Linked List: O(N log N)
    static string getMergeSort() {
        return "ListNode* sortList(ListNode* head) {\n"
               "    if(!head || !head->next) return head;\n"
               "    ListNode *slow = head, *fast = head->next;\n"
               "    while(fast && fast->next) { slow = slow->next; fast = fast->next->next; }\n"
               "    ListNode* mid = slow->next; slow->next = NULL;\n"
               "    return merge(sortList(head), sortList(mid));\n}\n\n";
    }

    // Remove N-th node from end (Single Pass)
    static string getRemoveNth() {
        return "ListNode* removeNthFromEnd(ListNode* head, int n) {\n"
               "    ListNode *dummy = new ListNode(0); dummy->next = head;\n"
               "    ListNode *fast = dummy, *slow = dummy;\n"
               "    for(int i=0; i<n; i++) fast = fast->next;\n"
               "    while(fast->next) { fast = fast->next; slow = slow->next; }\n"
               "    slow->next = slow->next->next; return dummy->next;\n}\n\n";
    }
};

#endif