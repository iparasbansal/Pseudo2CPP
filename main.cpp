#include <bits/stdc++.h>
#include <fstream>

#include "LogicAnalyzer.hpp"
#include "Templates.hpp"

using namespace std;

/* ======================================================
   ALGORITHM → TEMPLATE DISPATCHER
   ====================================================== */

string generateExpertCode(AlgoType type) {

    static unordered_map<AlgoType, function<string()>> dispatch = {

        /* ---------- GRAPHS ---------- */
        {AlgoType::DIJKSTRA, Templates::dijkstra},
        {AlgoType::BFS, Templates::bfs},
        {AlgoType::DFS, Templates::dfs},
        {AlgoType::TOPO_SORT, Templates::topoSort},
        {AlgoType::KRUSKAL, Templates::kruskal},
        {AlgoType::BELLMAN_FORD, Templates::bellmanFord},
        {AlgoType::FLOYD_WARSHALL, Templates::floydWarshall},
        {AlgoType::TARJAN_SCC, Templates::tarjanSCC},

        /* ---------- TREES ---------- */
        {AlgoType::LCA_BINARY_LIFTING, Templates::lcaBinaryLifting},
        {AlgoType::TREE_DIAMETER, Templates::treeDiameter},
        {AlgoType::BURN_TREE, Templates::burnTree},
        {AlgoType::MORRIS_TRAVERSAL, Templates::morrisTraversal},
        {AlgoType::BST_VALIDATE, Templates::bstValidate},

        /* ---------- DP ---------- */
        {AlgoType::DP_KNAPSACK, Templates::knapsack01},
        {AlgoType::DP_LCS, Templates::dpLCS},
        {AlgoType::DP_LIS, Templates::dpLIS},
        {AlgoType::DP_GRID_PATH, Templates::gridPathDP},
        {AlgoType::DP_STOCK, Templates::stockDP},
        {AlgoType::DP_PARTITION_MCM, Templates::partitionMCM},
        {AlgoType::DP_TREE, Templates::treeDP},
        {AlgoType::DP_BITMASK, Templates::bitmaskDP},
        {AlgoType::DP_DIGIT, Templates::digitDP},
        {AlgoType::MATRIX_EXP, Templates::matrixExp},

        /* ---------- STACK / QUEUE ---------- */
        {AlgoType::STACK_PARENTHESES, Templates::validParentheses},
        {AlgoType::STACK_NGE, Templates::nextGreater},
        {AlgoType::STACK_HISTOGRAM, Templates::histogramArea},
        {AlgoType::SLIDING_WINDOW_MAX, Templates::slidingWindowMax},
        {AlgoType::LRU_CACHE, Templates::lruCache},
        {AlgoType::STACK_REMOVE_K, Templates::removeKDigits},

        /* ---------- LINEAR ---------- */
        {AlgoType::THREE_SUM, Templates::threeSum},
        {AlgoType::TRAPPING_RAIN_WATER, Templates::trappingRainWater},
        {AlgoType::CONTAINER_WATER, Templates::containerWithMostWater},
        {AlgoType::SLIDING_WINDOW_VAR, Templates::slidingWindowVariable},

        /* ---------- LINKED LIST ---------- */
        {AlgoType::LL_REVERSE, Templates::reverseLL},
        {AlgoType::LL_K_REVERSE, Templates::reverseKGroup},
        {AlgoType::LL_CYCLE_DETECTION, Templates::detectCycle},
        {AlgoType::LL_FLATTEN, Templates::flattenLL},
        {AlgoType::LL_MERGE_SORT, Templates::mergeSortLL},

        /* ---------- HEAP / HASH ---------- */
        {AlgoType::HEAP_KTH_LARGEST, Templates::kthLargest},
        {AlgoType::HEAP_MEDIAN_STREAM, Templates::medianInStream},
        {AlgoType::HEAP_MERGE_K_LISTS, Templates::mergeKLists},
        {AlgoType::HASH_SUBARRAY_SUM_K, Templates::subarraySumK},
        {AlgoType::HASH_LONGEST_CONSECUTIVE, Templates::longestConsecutive},

        /* ---------- STRINGS ---------- */
        {AlgoType::STR_KMP, Templates::kmp},
        {AlgoType::STR_Z_ALGO, Templates::zAlgo},
        {AlgoType::STR_TRIE, Templates::trie},
        {AlgoType::STR_MANACHER, Templates::manacher},
        {AlgoType::STR_RABIN_KARP, Templates::rabinKarp},

        /* ---------- MATH ---------- */
        {AlgoType::MATH_BS_ON_ANSWER, Templates::bsOnAnswer},
        {AlgoType::MATH_SIEVE, Templates::sieve},
        {AlgoType::MATH_MOD_EXP, Templates::modExp},
        {AlgoType::MATH_NCR, Templates::nCr},
        {AlgoType::MATH_BIT_MANIP, Templates::bitManip}
    };

    if(dispatch.count(type))
        return dispatch[type]();

    return "// [!] No specific logic found. Please implement manually.\n";
}

/* ======================================================
   MAIN TRANSPILER ENGINE
   ====================================================== */

int main() {

    cout << "========================================================\n";
    cout << "        UNIVERSAL DSA TRANSPILER ENGINE v2.0\n";
    cout << "        Developed by Paras Bansal\n";
    cout << "========================================================\n\n";

    string input;

    cout << "[>] Enter pseudocode or problem statement:\n> ";
    getline(cin, input);

    cout << "\n[*] Analyzing Natural Language Syntax...\n";

    LogicAnalyzer analyzer;

    vector<IntentResult> ranked = analyzer.detectIntent(input);

    if(ranked.empty()) {
        cout << "[!] Analyzer returned no results.\n";
        return 0;
    }

    IntentResult bestIntent = ranked.front();

    cout << "[*] Semantic Mapping Complete.\n";
    cout << "    - Target Domain: " << bestIntent.domain << "\n";
    cout << "    - Confidence:   " << bestIntent.confidence << "%\n\n";

    cout << "[*] Generating Expert C++ Code...\n";

    string finalCode;

    /* ---------- HEADER ---------- */

    finalCode += Templates::header();

    /* ---------- METADATA ---------- */

    finalCode += "// ==========================================\n";
    finalCode += "// Generated by Bansal Universal Transpiler\n";
    finalCode += "// Domain: " + bestIntent.domain + "\n";
    finalCode += "// Confidence: " + to_string(bestIntent.confidence) + "%\n";
    finalCode += "// ==========================================\n\n";

    /* ---------- ALGORITHM CODE ---------- */

    finalCode += generateExpertCode(bestIntent.type);

    /* ---------- CP BOILERPLATE ---------- */

    finalCode += R"(

void solve() {

    // TODO: read input and call algorithm above

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}

)";

    /* ---------- WRITE FILE ---------- */

    ofstream fout("solution.cpp", ios::trunc);
    fout << finalCode;
    fout.close();

    cout << "[+] SUCCESS: solution.cpp generated successfully.\n";
    cout << "========================================================\n";

    return 0;
}