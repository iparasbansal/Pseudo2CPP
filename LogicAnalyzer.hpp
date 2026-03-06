#ifndef LOGIC_ANALYZER_HPP
#define LOGIC_ANALYZER_HPP

#include <bits/stdc++.h>
using namespace std;

enum class AlgoType {
    NONE,
    // --- GRAPHS (1-9) ---
    DIJKSTRA, BFS, DFS, TOPO_SORT, KRUSKAL, BELLMAN_FORD, FLOYD_WARSHALL, TARJAN_SCC, DSU,
    // --- TREES (10-14) ---
    LCA_BINARY_LIFTING, TREE_DIAMETER, BURN_TREE, MORRIS_TRAVERSAL, BST_VALIDATE,
    // --- DP (15-24) ---
    DP_KNAPSACK, DP_LCS, DP_LIS, DP_GRID_PATH, DP_STOCK, DP_PARTITION_MCM, DP_TREE, DP_BITMASK, DP_DIGIT, MATRIX_EXP,
    // --- STACKS & QUEUES (25-30) ---
    STACK_PARENTHESES, STACK_NGE, STACK_HISTOGRAM, SLIDING_WINDOW_MAX, LRU_CACHE, STACK_REMOVE_K,
    // --- LINEAR & TWO POINTERS (31-34) ---
    THREE_SUM, TRAPPING_RAIN_WATER, CONTAINER_WATER, SLIDING_WINDOW_VAR,
    // --- LINKED LIST (35-39) ---
    LL_REVERSE, LL_K_REVERSE, LL_CYCLE_DETECTION, LL_FLATTEN, LL_MERGE_SORT,
    // --- HEAPS & HASHING (40-44) ---
    HEAP_KTH_LARGEST, HEAP_MEDIAN_STREAM, HEAP_MERGE_K_LISTS, HASH_SUBARRAY_SUM_K, HASH_LONGEST_CONSECUTIVE,
    // --- STRINGS (45-49) ---
    STR_KMP, STR_Z_ALGO, STR_TRIE, STR_MANACHER, STR_RABIN_KARP,
    // --- SEARCH & MATH (50+) ---
    MATH_BS_ON_ANSWER, MATH_SIEVE, MATH_MOD_EXP, MATH_NCR, MATH_BIT_MANIP
};

struct Keyword { string word; int weight; };
struct IntentResult { AlgoType type; int confidence; string domain; };

class LogicAnalyzer {
private:
    map<AlgoType, vector<Keyword>> brain;
    map<string, string> synonyms;

    string getDomainName(AlgoType type) {
        int val = static_cast<int>(type);
        if (val >= 1 && val <= 9) return "Graphs";
        if (val >= 10 && val <= 14) return "Trees";
        if (val >= 15 && val <= 24) return "Dynamic Programming";
        if (val >= 25 && val <= 30) return "Stacks & Queues";
        if (val >= 31 && val <= 34) return "Linear & Two Pointers";
        if (val >= 35 && val <= 39) return "Linked List";
        if (val >= 40 && val <= 44) return "Heaps & Hashing";
        if (val >= 45 && val <= 49) return "Strings";
        if (val >= 50) return "Search & Math";
        return "General";
    }

public:
    LogicAnalyzer() {
        // --- SYNONYMS (Normalization Layer) ---
        synonyms["minimum path"] = "shortest"; synonyms["cycle"] = "loop";
        synonyms["prefix"] = "trie"; synonyms["palindrome"] = "manacher";
        synonyms["all nodes"] = "spanning"; synonyms["dependency"] = "topological";
        synonyms["maximize minimum"] = "bs_ans"; synonyms["minimize maximum"] = "bs_ans";
        synonyms["next greater"] = "nge"; synonyms["rectangle"] = "histogram";

        // --- 1. GRAPHS ---
        brain[AlgoType::DIJKSTRA] = {{"shortest", 5}, {"weighted", 4}, {"non-negative", 5}, {"unweighted", -15}};
        brain[AlgoType::BFS] = {{"unweighted", 6}, {"level", 5}, {"shortest", 2}, {"queue", 2}};
        brain[AlgoType::DFS] = {{"recursion", 4}, {"reachability", 4}, {"backtracking", 3}, {"stack", 2}};
        brain[AlgoType::TOPO_SORT] = {{"topological", 10}, {"order", 3}, {"tasks", 3}, {"dependency", 5}};
        brain[AlgoType::KRUSKAL] = {{"spanning", 8}, {"mst", 10}, {"connect all", 5}, {"minimum cost", 3}};
        brain[AlgoType::BELLMAN_FORD] = {{"negative edge", 12}, {"negative weight", 12}, {"shortest", 2}};
        brain[AlgoType::FLOYD_WARSHALL] = {{"all pairs", 10}, {"apsp", 10}, {"matrix shortest", 5}};
        brain[AlgoType::TARJAN_SCC] = {{"strongly connected", 12}, {"scc", 10}, {"critical", 5}};
        brain[AlgoType::DSU] = {{"disjoint", 10}, {"union", 8}, {"find", 5}, {"groups", 3}};

        // --- 2. TREES ---
        brain[AlgoType::LCA_BINARY_LIFTING] = {{"lca", 10}, {"ancestor", 8}, {"distance between nodes", 6}};
        brain[AlgoType::TREE_DIAMETER] = {{"diameter", 10}, {"longest path", 8}, {"farthest", 5}};
        brain[AlgoType::BURN_TREE] = {{"burn", 10}, {"fire", 10}, {"spread", 5}, {"infection", 5}};
        brain[AlgoType::MORRIS_TRAVERSAL] = {{"morris", 12}, {"o(1) space", 8}, {"inorder", 2}};
        brain[AlgoType::BST_VALIDATE] = {{"validate bst", 10}, {"check binary search tree", 10}};

        // --- 3. DYNAMIC PROGRAMMING ---
        brain[AlgoType::DP_KNAPSACK] = {{"knapsack", 12}, {"capacity", 6}, {"weight", 5}, {"profit", 6}};
        brain[AlgoType::DP_LCS] = {{"common subsequence", 10}, {"lcs", 10}, {"edit distance", 5}};
        brain[AlgoType::DP_LIS] = {{"increasing subsequence", 10}, {"lis", 10}, {"longest increasing", 8}};
        brain[AlgoType::DP_GRID_PATH] = {{"grid path", 10}, {"matrix path", 8}, {"unique paths", 5}};
        brain[AlgoType::DP_STOCK] = {{"stock", 10}, {"buy sell", 10}, {"cooldown", 8}, {"transaction", 5}};
        brain[AlgoType::DP_PARTITION_MCM] = {{"mcm", 10}, {"partition", 8}, {"matrix chain", 10}, {"range dp", 5}};
        brain[AlgoType::DP_TREE] = {{"tree dp", 12}, {"independent set", 8}, {"node weight", 5}};
        brain[AlgoType::DP_BITMASK] = {{"bitmask", 10}, {"tsp", 10}, {"masking", 8}, {"subset dp", 5}};
        brain[AlgoType::DP_DIGIT] = {{"digit dp", 12}, {"sum of digits", 10}, {"count between", 5}};
        brain[AlgoType::MATRIX_EXP] = {{"matrix exponentiation", 12}, {"linear recurrence", 10}, {"nth fibonacci", 5}};

        // --- 4. STACKS & QUEUES ---
        brain[AlgoType::STACK_PARENTHESES] = {{"balanced", 10}, {"parenthesis", 10}, {"valid brackets", 8}};
        brain[AlgoType::STACK_NGE] = {{"nge", 10}, {"next greater", 10}, {"nearest smaller", 8}};
        brain[AlgoType::STACK_HISTOGRAM] = {{"histogram", 10}, {"largest area", 10}, {"bar area", 5}};
        brain[AlgoType::SLIDING_WINDOW_MAX] = {{"sliding window maximum", 12}, {"window max", 10}, {"deque", 5}};
        brain[AlgoType::LRU_CACHE] = {{"lru", 12}, {"cache", 10}, {"least recently used", 10}};
        brain[AlgoType::STACK_REMOVE_K] = {{"remove k", 10}, {"smallest number", 8}, {"digits", 5}};

        // --- 5. LINEAR & TWO POINTERS ---
        brain[AlgoType::THREE_SUM] = {{"3sum", 10}, {"triplet", 8}, {"three sum", 10}};
        brain[AlgoType::TRAPPING_RAIN_WATER] = {{"trap", 10}, {"rain", 10}, {"water", 10}, {"elevation", 5}};
        brain[AlgoType::CONTAINER_WATER] = {{"container", 10}, {"most water", 10}, {"walls", 5}};
        brain[AlgoType::SLIDING_WINDOW_VAR] = {{"variable window", 10}, {"smallest subarray", 8}, {"unique characters", 5}};

        // --- 6. LINKED LIST ---
        brain[AlgoType::LL_REVERSE] = {{"reverse list", 10}, {"reversal", 5}};
        brain[AlgoType::LL_K_REVERSE] = {{"reverse in k", 12}, {"k groups", 12}, {"group reversal", 10}};
        brain[AlgoType::LL_CYCLE_DETECTION] = {{"cycle", 8}, {"loop", 8}, {"detect cycle", 10}, {"intersection", 5}};
        brain[AlgoType::LL_FLATTEN] = {{"flatten", 10}, {"multilevel", 8}, {"linked list flatten", 10}};
        brain[AlgoType::LL_MERGE_SORT] = {{"sort list", 10}, {"merge sort linked list", 10}};

        // --- 7. HEAPS & HASHING ---
        brain[AlgoType::HEAP_KTH_LARGEST] = {{"kth largest", 10}, {"k smallest", 10}, {"min heap", 5}};
        brain[AlgoType::HEAP_MEDIAN_STREAM] = {{"median", 10}, {"running data", 8}, {"streaming median", 10}};
        brain[AlgoType::HEAP_MERGE_K_LISTS] = {{"merge k", 10}, {"k sorted", 10}, {"multiple lists", 5}};
        brain[AlgoType::HASH_SUBARRAY_SUM_K] = {{"subarray sum", 10}, {"target sum", 8}, {"equals k", 10}};
        brain[AlgoType::HASH_LONGEST_CONSECUTIVE] = {{"consecutive", 10}, {"longest sequence", 8}, {"unordered_set", 2}};

        // --- 8. STRINGS ---
        brain[AlgoType::STR_KMP] = {{"kmp", 10}, {"pattern", 6}, {"substring match", 6}, {"lps", 5}};
        brain[AlgoType::STR_Z_ALGO] = {{"z-algo", 10}, {"z function", 10}, {"matching", 4}};
        brain[AlgoType::STR_TRIE] = {{"trie", 12}, {"prefix", 10}, {"autocomplete", 8}, {"dictionary", 5}};
        brain[AlgoType::STR_MANACHER] = {{"manacher", 12}, {"longest palindromic", 10}, {"palindromes", 6}};
        brain[AlgoType::STR_RABIN_KARP] = {{"rabin karp", 10}, {"rolling hash", 10}, {"hash matching", 8}};

        // --- 9. SEARCH & MATH ---
        brain[AlgoType::MATH_BS_ON_ANSWER] = {{"bs_ans", 15}, {"aggressive", 10}, {"allocate", 10}, {"search space", 5}, {"monotonic", 4}};
        brain[AlgoType::MATH_SIEVE] = {{"prime", 8}, {"sieve", 10}, {"eratosthenes", 10}};
        brain[AlgoType::MATH_MOD_EXP] = {{"power mod", 10}, {"exponentiation", 8}, {"large power", 5}};
        brain[AlgoType::MATH_NCR] = {{"ncr", 10}, {"combination", 8}, {"npr", 5}, {"permutation", 5}};
        brain[AlgoType::MATH_BIT_MANIP] = {{"bits", 8}, {"xor", 8}, {"set bit", 5}, {"bitwise", 5}};
    }

    void normalize(string &input) {
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        for(auto const& [key, val] : synonyms) {
            size_t pos = input.find(key);
            if(pos != string::npos) input.replace(pos, key.length(), val);
        }
    }

    vector<IntentResult> detectIntent(string input) {
        normalize(input);
        map<AlgoType, int> scores;

        for(auto &entry : brain) {
            for(auto &k : entry.second) {
                if(input.find(k.word) != string::npos) scores[entry.first] += k.weight;
            }
        }

        // --- CONTEXTUAL CROSS-CHECK (The Intelligence Layer) ---
        bool isTree = input.find("tree") != string::npos || input.find("bst") != string::npos;
        bool hasNegative = input.find("negative") != string::npos;
        bool isGraph = input.find("graph") != string::npos || input.find("nodes") != string::npos || input.find("vertices") != string::npos;
        bool isString = input.find("string") != string::npos || input.find("text") != string::npos || input.find("characters") != string::npos;
        bool isList = input.find("linked list") != string::npos || input.find("pointer") != string::npos;

        // 1. Tree Overrides
        if(isTree) {
            scores[AlgoType::LCA_BINARY_LIFTING] += 10;
            scores[AlgoType::DP_TREE] += 10;
            scores[AlgoType::DIJKSTRA] -= 25; 
            scores[AlgoType::LL_CYCLE_DETECTION] -= 20; // Prevent cycle clash
        }
        
        // 2. Graph Overrides
        if(isGraph) {
            scores[AlgoType::LL_CYCLE_DETECTION] -= 25; // If it's a graph, it's NOT a linked list cycle
            if(hasNegative) {
                scores[AlgoType::BELLMAN_FORD] += 15;
                scores[AlgoType::FLOYD_WARSHALL] += 8;
                scores[AlgoType::DIJKSTRA] -= 20; 
            }
        }

        // 3. String & Hash Overrides
        if(isString) {
            scores[AlgoType::STR_KMP] += 5;
            scores[AlgoType::STR_TRIE] += 5;
            scores[AlgoType::STR_RABIN_KARP] += 5;
            scores[AlgoType::SLIDING_WINDOW_VAR] += 8; // "unique characters" usually means sliding window
        }

        if(input.find("rolling hash") != string::npos || input.find("rabin karp") != string::npos) {
            scores[AlgoType::STR_RABIN_KARP] += 25;
            scores[AlgoType::STR_KMP] -= 15;
        }

        // 4. Linked List Overrides
        if(isList) {
            scores[AlgoType::LL_REVERSE] += 5;
            scores[AlgoType::LL_CYCLE_DETECTION] += 5;
            scores[AlgoType::DIJKSTRA] -= 20; // Don't run shortest path on a simple list
        }

        // --- RANKING & RESULTS ---
        vector<pair<AlgoType, int>> ranked;
        for(auto &p : scores) if(p.second > 2) ranked.push_back(p);
        
        sort(ranked.begin(), ranked.end(), [](auto &a, auto &b){ 
            if(a.second == b.second) return (int)a.first > (int)b.first; // Stability
            return a.second > b.second; 
        });

        vector<IntentResult> results;
        int totalTop = 0;
        int count = min((int)ranked.size(), 3);
        for(int i=0; i < count; i++) totalTop += ranked[i].second;

        for(int i=0; i < count; i++) {
            int conf = (totalTop > 0) ? (ranked[i].second * 100 / totalTop) : 0;
            results.push_back({ranked[i].first, conf, getDomainName(ranked[i].first)});
        }

        if(results.empty()) results.push_back({AlgoType::NONE, 0, "Undefined"});
        return results;
    }
};

#endif