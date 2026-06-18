#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "../AlgorithmRegistry.hpp"
#include "../LogicAnalyzer.hpp"

using namespace std;

struct IntentCase {
    string name;
    string query;
    AlgoType expected;
};

static void runCase(const IntentCase& testCase) {
    LogicAnalyzer analyzer;
    vector<IntentResult> ranked = analyzer.detectIntent(testCase.query);

    assert(!ranked.empty());

    if(ranked.front().type != testCase.expected) {
        cerr << "[FAIL] " << testCase.name << "\n"
             << "  Query: " << testCase.query << "\n"
             << "  Expected: " << AlgorithmRegistry::get(testCase.expected).name << "\n"
             << "  Got: " << AlgorithmRegistry::get(ranked.front().type).name << "\n";
        exit(1);
    }

    cout << "[PASS] " << testCase.name << " -> "
         << AlgorithmRegistry::get(ranked.front().type).name
         << " (" << ranked.front().confidence << "%)\n";
}

int main() {
    vector<IntentCase> cases = {
        {
            "negative toll wording maps to Bellman-Ford",
            "Find the cheapest route between cities where roads have negative toll values.",
            AlgoType::BELLMAN_FORD
        },
        {
            "fewest edges maps to BFS",
            "Find the minimum number of edges needed to reach every node in an unweighted network.",
            AlgoType::BFS
        },
        {
            "course schedule wording maps to topological sort",
            "Build a course schedule from prerequisite constraints and return a valid ordering.",
            AlgoType::TOPO_SORT
        },
        {
            "tree shortest path context maps to LCA",
            "In a tree, answer distance between nodes for many queries using ancestors.",
            AlgoType::LCA_BINARY_LIFTING
        },
        {
            "autocomplete wording maps to trie",
            "Create an autocomplete dictionary that returns words sharing the same prefix.",
            AlgoType::STR_TRIE
        },
        {
            "streaming median wording maps to heap median",
            "Numbers arrive as a continuous stream and I need the running median after each insert.",
            AlgoType::HEAP_MEDIAN_STREAM
        },
        {
            "answer-space optimization maps to binary search on answer",
            "Allocate servers so the minimum distance is maximized using a monotonic feasibility check.",
            AlgoType::MATH_BS_ON_ANSWER
        },
        {
            "typo tolerance still catches Dijkstra",
            "Use dijsktra for shortest path in a weighted graph with non negative weights.",
            AlgoType::DIJKSTRA
        },
        {
            "least weights source destination maps to Dijkstra",
            "least weights from source to destination node",
            AlgoType::DIJKSTRA
        }
    };

    for(const IntentCase& testCase : cases) {
        runCase(testCase);
    }

    cout << "[+] All intent tests passed.\n";
    return 0;
}
