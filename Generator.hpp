#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <string>
#include "LogicAnalyzer.hpp"
#include "Templates.hpp"

using namespace std;

class Generator {
public:
    static string generate(AlgoType type) {
        string code = "";
        
        switch(type) {
            
            // ==========================================
            // 1. GRAPHS
            // ==========================================
            case AlgoType::DIJKSTRA:
                code += Templates::dijkstra();
                break;
                
            case AlgoType::BFS:
                code += Templates::bfs();
                break;
                
            case AlgoType::DFS:
                code += Templates::dfs();
                break;
                
            case AlgoType::TOPO_SORT:
                code += Templates::topoSort();
                break;
                
            case AlgoType::KRUSKAL:
                code += Templates::kruskal();
                break;
                
            case AlgoType::BELLMAN_FORD:
                code += Templates::bellmanFord();
                break;
                
            case AlgoType::FLOYD_WARSHALL:
                code += Templates::floydWarshall();
                break;
                
            case AlgoType::TARJAN_SCC:
                code += Templates::tarjanSCC();
                break;

            // ==========================================
            // 2. TREES
            // ==========================================
            case AlgoType::LCA_BINARY_LIFTING:
                code += Templates::lcaBinaryLifting();
                break;
                
            case AlgoType::TREE_DIAMETER:
                code += Templates::treeDiameter();
                break;
                
            case AlgoType::BURN_TREE:
                code += Templates::burnTree();
                break;
                
            case AlgoType::MORRIS_TRAVERSAL:
                code += Templates::morrisTraversal();
                break;
                
            case AlgoType::BST_VALIDATE:
                code += Templates::bstValidate();
                break;

            // ==========================================
            // 3. DYNAMIC PROGRAMMING
            // ==========================================
            case AlgoType::DP_KNAPSACK:
                code += Templates::knapsack01();
                break;
                
            case AlgoType::DP_LCS:
                code += Templates::dpLCS();
                break;
                
            case AlgoType::DP_LIS:
                code += Templates::dpLIS();
                break;
                
            case AlgoType::DP_GRID_PATH:
                code += Templates::gridPathDP();
                break;
                
            case AlgoType::DP_STOCK:
                code += Templates::stockDP();
                break;
                
            case AlgoType::DP_PARTITION_MCM:
                code += Templates::partitionMCM();
                break;
                
            case AlgoType::DP_TREE:
                code += Templates::treeDP();
                break;
                
            case AlgoType::DP_BITMASK:
                code += Templates::bitmaskDP();
                break;
                
            case AlgoType::DP_DIGIT:
                code += Templates::digitDP();
                break;
                
            case AlgoType::MATRIX_EXP:
                code += Templates::matrixExp();
                break;

            // ==========================================
            // 4. STACKS & QUEUES
            // ==========================================
            case AlgoType::STACK_PARENTHESES:
                code += Templates::validParentheses();
                break;
                
            case AlgoType::STACK_NGE:
                code += Templates::nextGreater();
                break;
                
            case AlgoType::STACK_HISTOGRAM:
                code += Templates::histogramArea();
                break;
                
            case AlgoType::SLIDING_WINDOW_MAX:
                code += Templates::slidingWindowMax();
                break;
                
            case AlgoType::LRU_CACHE:
                code += Templates::lruCache();
                break;
                
            case AlgoType::STACK_REMOVE_K:
                code += Templates::removeKDigits();
                break;

            // ==========================================
            // 5. LINEAR & TWO POINTERS
            // ==========================================
            case AlgoType::THREE_SUM:
                code += Templates::threeSum();
                break;
                
            case AlgoType::TRAPPING_RAIN_WATER:
                code += Templates::trappingRainWater();
                break;
                
            case AlgoType::CONTAINER_WATER:
                code += Templates::containerWithMostWater();
                break;
                
            case AlgoType::SLIDING_WINDOW_VAR:
                code += Templates::slidingWindowVariable();
                break;

            // ==========================================
            // 6. LINKED LIST
            // ==========================================
            case AlgoType::LL_REVERSE:
                code += Templates::reverseLL();
                break;
                
            case AlgoType::LL_K_REVERSE:
                code += Templates::reverseKGroup();
                break;
                
            case AlgoType::LL_CYCLE_DETECTION:
                code += Templates::detectCycle();
                break;
                
            case AlgoType::LL_FLATTEN:
                code += Templates::flattenLL();
                break;
                
            case AlgoType::LL_MERGE_SORT:
                code += Templates::mergeSortLL();
                break;

            // ==========================================
            // 7. HEAPS & HASHING
            // ==========================================
            case AlgoType::HEAP_KTH_LARGEST:
                code += Templates::kthLargest();
                break;
                
            case AlgoType::HEAP_MEDIAN_STREAM:
                code += Templates::medianInStream();
                break;
                
            case AlgoType::HEAP_MERGE_K_LISTS:
                code += Templates::mergeKLists();
                break;
                
            case AlgoType::HASH_SUBARRAY_SUM_K:
                code += Templates::subarraySumK();
                break;
                
            case AlgoType::HASH_LONGEST_CONSECUTIVE:
                code += Templates::longestConsecutive();
                break;

            // ==========================================
            // 8. STRINGS
            // ==========================================
            case AlgoType::STR_KMP:
                code += Templates::kmp();
                break;
                
            case AlgoType::STR_Z_ALGO:
                code += Templates::zAlgo();
                break;
                
            case AlgoType::STR_TRIE:
                code += Templates::trie();
                break;
                
            case AlgoType::STR_MANACHER:
                code += Templates::manacher();
                break;
                
            case AlgoType::STR_RABIN_KARP:
                code += Templates::rabinKarp();
                break;

            // ==========================================
            // 9. MATH & SEARCH
            // ==========================================
            case AlgoType::MATH_BS_ON_ANSWER:
                code += Templates::bsOnAnswer();
                break;
                
            case AlgoType::MATH_SIEVE:
                code += Templates::sieve();
                break;
                
            case AlgoType::MATH_MOD_EXP:
                code += Templates::modExp();
                break;
                
            case AlgoType::MATH_NCR:
                code += Templates::nCr();
                break;
                
            case AlgoType::MATH_BIT_MANIP:
                code += Templates::bitManip();
                break;

            // ==========================================
            // 10. ADVANCED DATA STRUCTURES (Legacy Fallbacks)
            // ==========================================
            // Uncomment these IF you have added them to AlgoType enum and Templates.hpp
            /*
            case AlgoType::SEGMENT_TREE:
                code += Templates::segmentTree();
                break;
                
            case AlgoType::FENWICK:
                code += Templates::fenwick();
                break;
            */

            default: 
                code += "// [!] No specific logic found. Please write manual code.\n"; 
                break;
        }
        
        return code;
    }
};

#endif