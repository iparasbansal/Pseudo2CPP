#ifndef ALGORITHM_REGISTRY_HPP
#define ALGORITHM_REGISTRY_HPP

#include <string>
#include <vector>

#include "LogicAnalyzer.hpp"

using namespace std;

struct AlgorithmProfile {
    AlgoType type;
    string name;
    string domain;
    string timeComplexity;
    string spaceComplexity;
    string useCase;
    string warning;
};

class AlgorithmRegistry {
public:
    static vector<AlgorithmProfile> all() {
        return {
            {AlgoType::DIJKSTRA, "Dijkstra", "Graphs", "O((V + E) log V)", "O(V + E)", "Single-source shortest path with non-negative weights.", "Do not use when negative edges exist."},
            {AlgoType::BFS, "Breadth-First Search", "Graphs", "O(V + E)", "O(V)", "Shortest path in unweighted graphs and level traversal.", "Weighted edges need a different algorithm."},
            {AlgoType::DFS, "Depth-First Search", "Graphs", "O(V + E)", "O(V)", "Reachability, components, recursion, and backtracking.", "Recursive DFS can overflow on very deep graphs."},
            {AlgoType::TOPO_SORT, "Topological Sort", "Graphs", "O(V + E)", "O(V)", "Ordering tasks/courses with dependency constraints.", "Only valid for directed acyclic graphs."},
            {AlgoType::KRUSKAL, "Kruskal MST", "Graphs", "O(E log E)", "O(V)", "Minimum spanning tree / connect all nodes with minimum cost.", "Requires undirected weighted graph."},
            {AlgoType::BELLMAN_FORD, "Bellman-Ford", "Graphs", "O(VE)", "O(V)", "Shortest path with negative weights and negative-cycle checks.", "Slower than Dijkstra on non-negative graphs."},
            {AlgoType::FLOYD_WARSHALL, "Floyd-Warshall", "Graphs", "O(V^3)", "O(V^2)", "All-pairs shortest paths on dense/small graphs.", "Too slow for large sparse graphs."},
            {AlgoType::TARJAN_SCC, "Tarjan SCC", "Graphs", "O(V + E)", "O(V)", "Strongly connected components in directed graphs.", "Implementation needs careful low-link handling."},
            {AlgoType::DSU, "Disjoint Set Union", "Graphs", "Almost O(1) amortized", "O(V)", "Connectivity groups, union/find, cycle checks in undirected graphs.", "Current generator does not emit a standalone DSU template yet."},

            {AlgoType::LCA_BINARY_LIFTING, "LCA Binary Lifting", "Trees", "O(N log N) build, O(log N) query", "O(N log N)", "Ancestor and distance queries in trees.", "Requires preprocessing from a fixed root."},
            {AlgoType::TREE_DIAMETER, "Tree Diameter", "Trees", "O(N)", "O(H)", "Longest path in a tree.", "For weighted trees, template must include weights."},
            {AlgoType::BURN_TREE, "Burn Tree", "Trees", "O(N)", "O(N)", "Spread/infection time from a target node.", "Needs tree converted to an undirected adjacency map."},
            {AlgoType::MORRIS_TRAVERSAL, "Morris Traversal", "Trees", "O(N)", "O(1)", "Inorder traversal without recursion or stack.", "Temporarily modifies tree links during traversal."},
            {AlgoType::BST_VALIDATE, "Validate BST", "Trees", "O(N)", "O(H)", "Check if a binary tree satisfies BST ordering.", "Use wide numeric bounds for int extremes."},

            {AlgoType::DP_KNAPSACK, "0/1 Knapsack", "Dynamic Programming", "O(NW)", "O(W)", "Capacity/weight/profit optimization.", "Pseudo-polynomial in capacity."},
            {AlgoType::DP_LCS, "Longest Common Subsequence", "Dynamic Programming", "O(NM)", "O(M)", "Common subsequence and edit-style string DP.", "This template returns length, not reconstruction."},
            {AlgoType::DP_LIS, "Longest Increasing Subsequence", "Dynamic Programming", "O(N log N)", "O(N)", "Longest increasing subsequence length.", "Template returns length only."},
            {AlgoType::DP_GRID_PATH, "Grid Path DP", "Dynamic Programming", "O(NM)", "O(M)", "Minimum/unique path style grid transitions.", "Assumes right/down movement pattern."},
            {AlgoType::DP_STOCK, "Stock DP", "Dynamic Programming", "O(N)", "O(1)", "Buy/sell stock with cooldown-style states.", "Different transaction rules need state changes."},
            {AlgoType::DP_PARTITION_MCM, "Partition / MCM DP", "Dynamic Programming", "O(N^3)", "O(N^2)", "Matrix chain and range partition decisions.", "Needs custom transition per problem."},
            {AlgoType::DP_TREE, "Tree DP", "Dynamic Programming", "O(N)", "O(N)", "DP states over parent-child tree structure.", "Rooting choice matters."},
            {AlgoType::DP_BITMASK, "Bitmask DP", "Dynamic Programming", "O(N * 2^N)", "O(N * 2^N)", "TSP/subset state compression for small N.", "Only practical for small N."},
            {AlgoType::DP_DIGIT, "Digit DP", "Dynamic Programming", "O(digits * states)", "O(digits * states)", "Count numbers under bounds with digit constraints.", "State design is problem-specific."},
            {AlgoType::MATRIX_EXP, "Matrix Exponentiation", "Dynamic Programming", "O(K^3 log N)", "O(K^2)", "Fast linear recurrences such as Fibonacci.", "Requires recurrence matrix setup."},

            {AlgoType::STACK_PARENTHESES, "Valid Parentheses", "Stacks & Queues", "O(N)", "O(N)", "Balanced bracket validation.", "Only validates configured bracket types."},
            {AlgoType::STACK_NGE, "Next Greater Element", "Stacks & Queues", "O(N)", "O(N)", "Monotonic stack next/nearest element queries.", "Change comparison for smaller/greater variants."},
            {AlgoType::STACK_HISTOGRAM, "Largest Rectangle in Histogram", "Stacks & Queues", "O(N)", "O(N)", "Maximum rectangle area in bars/histograms.", "Bar width is assumed to be 1."},
            {AlgoType::SLIDING_WINDOW_MAX, "Sliding Window Maximum", "Stacks & Queues", "O(N)", "O(K)", "Window maximum using deque.", "Fixed-size window only."},
            {AlgoType::LRU_CACHE, "LRU Cache", "Stacks & Queues", "O(1)", "O(capacity)", "Least-recently-used cache design.", "Needs integration with object-oriented driver code."},
            {AlgoType::STACK_REMOVE_K, "Remove K Digits", "Stacks & Queues", "O(N)", "O(N)", "Build smallest number after removing K digits.", "String formatting matters for leading zeroes."},

            {AlgoType::THREE_SUM, "3Sum", "Linear & Two Pointers", "O(N^2)", "O(1) extra", "Triplets with target sum.", "Requires sorting."},
            {AlgoType::TRAPPING_RAIN_WATER, "Trapping Rain Water", "Linear & Two Pointers", "O(N)", "O(1)", "Water trapped between elevations.", "Input must represent bar heights."},
            {AlgoType::CONTAINER_WATER, "Container With Most Water", "Linear & Two Pointers", "O(N)", "O(1)", "Max area between two vertical lines.", "Different from trapping rain water."},
            {AlgoType::SLIDING_WINDOW_VAR, "Variable Sliding Window", "Linear & Two Pointers", "O(N)", "O(N)", "Longest/smallest subarray or substring with constraints.", "Constraint must be monotonic for classic window."},

            {AlgoType::LL_REVERSE, "Reverse Linked List", "Linked List", "O(N)", "O(1)", "Reverse a singly linked list.", "Node definition must match platform."},
            {AlgoType::LL_K_REVERSE, "Reverse Nodes in K Group", "Linked List", "O(N)", "O(1)", "Reverse linked-list nodes in fixed-size groups.", "Tail group behavior varies by problem."},
            {AlgoType::LL_CYCLE_DETECTION, "Linked List Cycle Detection", "Linked List", "O(N)", "O(1)", "Detect cycle using slow/fast pointers.", "Graph cycles are a different problem."},
            {AlgoType::LL_FLATTEN, "Flatten Linked List", "Linked List", "O(N log K)", "O(1)", "Flatten multi-level or sorted linked lists.", "Node shape varies across platforms."},
            {AlgoType::LL_MERGE_SORT, "Merge Sort Linked List", "Linked List", "O(N log N)", "O(log N)", "Sort linked list efficiently.", "Recursive version uses call stack."},

            {AlgoType::HEAP_KTH_LARGEST, "Kth Largest / Smallest", "Heaps & Hashing", "O(N log K)", "O(K)", "Kth order statistic using heap.", "Quickselect can be faster on average."},
            {AlgoType::HEAP_MEDIAN_STREAM, "Median in Data Stream", "Heaps & Hashing", "O(log N) insert, O(1) median", "O(N)", "Maintain median from streaming values.", "Needs two heaps balanced carefully."},
            {AlgoType::HEAP_MERGE_K_LISTS, "Merge K Sorted Lists", "Heaps & Hashing", "O(N log K)", "O(K)", "Merge multiple sorted linked lists/arrays.", "Node type must match the source platform."},
            {AlgoType::HASH_SUBARRAY_SUM_K, "Subarray Sum Equals K", "Heaps & Hashing", "O(N)", "O(N)", "Count subarrays using prefix sums and hash map.", "Works with negative numbers unlike sliding window."},
            {AlgoType::HASH_LONGEST_CONSECUTIVE, "Longest Consecutive Sequence", "Heaps & Hashing", "O(N)", "O(N)", "Longest consecutive integer run.", "Depends on hash set performance."},

            {AlgoType::STR_KMP, "KMP Pattern Matching", "Strings", "O(N + M)", "O(M)", "Find pattern occurrences using LPS prefix table.", "Rolling hash may be preferred for many hash queries."},
            {AlgoType::STR_Z_ALGO, "Z Algorithm", "Strings", "O(N + M)", "O(N + M)", "Pattern matching and prefix similarity.", "String concatenation sentinel must be unique."},
            {AlgoType::STR_TRIE, "Trie", "Strings", "O(L)", "O(total characters)", "Prefix dictionary/autocomplete lookup.", "Memory-heavy for large alphabets."},
            {AlgoType::STR_MANACHER, "Manacher", "Strings", "O(N)", "O(N)", "Longest palindromic substring.", "Template must handle transformed string indices."},
            {AlgoType::STR_RABIN_KARP, "Rabin-Karp", "Strings", "O(N + M) average", "O(1)", "Pattern matching with rolling hash.", "Hash collisions are possible."},

            {AlgoType::MATH_BS_ON_ANSWER, "Binary Search on Answer", "Search & Math", "O(log range * check)", "Depends on check", "Optimize monotonic yes/no answer spaces.", "Requires a valid monotonic predicate."},
            {AlgoType::MATH_SIEVE, "Sieve of Eratosthenes", "Search & Math", "O(N log log N)", "O(N)", "Prime generation and primality precomputation.", "Memory grows with maximum value."},
            {AlgoType::MATH_MOD_EXP, "Modular Exponentiation", "Search & Math", "O(log power)", "O(1)", "Fast power under modulo.", "Use modular multiplication carefully for huge values."},
            {AlgoType::MATH_NCR, "Combinatorics nCr", "Search & Math", "O(N) precompute, O(1) query", "O(N)", "Combinations/permutations under modulo.", "Modulo should usually be prime for inverse factorials."},
            {AlgoType::MATH_BIT_MANIP, "Bit Manipulation", "Search & Math", "O(bits)", "O(1)", "XOR/set-bit/bitwise logic.", "Problem-specific bit interpretation matters."}
        };
    }

    static AlgorithmProfile get(AlgoType type) {
        for(const AlgorithmProfile& profile : all()) {
            if(profile.type == type) return profile;
        }

        return {AlgoType::NONE, "Manual Implementation", "Undefined", "N/A", "N/A",
                "No confident algorithm match was found.", "Clarify the problem constraints and input format."};
    }
};

#endif
