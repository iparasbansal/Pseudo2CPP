#ifndef HASHING_EXPERT_HPP
#define HASHING_EXPERT_HPP

#include <bits/stdc++.h>
using namespace std;

class HashingExpert {
public:

    /* --- 1. SUBARRAY OPTIMIZATION (Prefix Sum + Hashing) --- */

    // Subarray Sum Equals K: O(N) Time | O(N) Space
    static string getSubarraySumK() {
        return "\n"
               "int subarraySum(vector<int>& nums, int k) {\n"
               "    unordered_map<int, int> mp; mp[0] = 1; \n"
               "    int sum = 0, count = 0;\n"
               "    for (int x : nums) {\n"
               "        sum += x;\n"
               "        if (mp.find(sum - k) != mp.end()) count += mp[sum - k];\n"
               "        mp[sum]++;\n"
               "    } return count;\n}\n\n";
    }

    /* --- 2. SEQUENCE & SET OPTIMIZATION --- */

    // Longest Consecutive Sequence: O(N) logic using Unordered Set
    static string getLongestConsecutive() {
        return "int longestConsecutive(vector<int>& nums) {\n"
               "    unordered_set<int> s(nums.begin(), nums.end());\n"
               "    int res = 0;\n"
               "    for (int x : nums) {\n"
               "        if (s.find(x - 1) == s.end()) {\n"
               "            int curr = x, count = 1;\n"
               "            while (s.find(curr + 1) != s.end()) { curr++; count++; }\n"
               "            res = max(res, count);\n"
               "        }\n"
               "    } return res;\n}\n\n";
    }

    /* --- 3. PATTERN GROUPING --- */

    // Group Anagrams: Frequency-based Hashing
    static string getGroupAnagrams() {
        return "vector<vector<string>> groupAnagrams(vector<string>& strs) {\n"
               "    unordered_map<string, vector<string>> mp;\n"
               "    for (string& s : strs) {\n"
               "        string t = s; sort(t.begin(), t.end());\n"
               "        mp[t].push_back(s);\n"
               "    }\n"
               "    vector<vector<string>> res;\n"
               "    for (auto& it : mp) res.push_back(it.second);\n"
               "    return res;\n}\n\n";
    }

    /* --- 4. MULTI-POINTER HASHING --- */

    // Four Sum: Optimized O(N^3) with Map/Set check
    static string getFourSum() {
        return "vector<vector<int>> fourSum(vector<int>& nums, int target) {\n"
               "    int n = nums.size(); sort(nums.begin(), nums.end());\n"
               "    vector<vector<int>> res;\n"
               "    for (int i = 0; i < n; i++) {\n"
               "        if (i > 0 && nums[i] == nums[i-1]) continue;\n"
               "        for (int j = i + 1; j < n; j++) {\n"
               "            if (j > i + 1 && nums[j] == nums[j-1]) continue;\n"
               "            int l = j + 1, r = n - 1;\n"
               "            while (l < r) {\n"
               "                long long sum = (long long)nums[i]+nums[j]+nums[l]+nums[r];\n"
               "                if (sum == target) {\n"
               "                    res.push_back({nums[i], nums[j], nums[l], nums[r]});\n"
               "                    while (l < r && nums[l] == nums[l+1]) l++;\n"
               "                    while (l < r && nums[r] == nums[r-1]) r--;\n"
               "                    l++; r--;\n"
               "                } else if (sum < target) l++; else r--;\n"
               "            }\n"
               "        }\n"
               "    } return res;\n}\n\n";
    }
};

#endif