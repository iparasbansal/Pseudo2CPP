#ifndef LOGIC_ANALYZER_HPP
#define LOGIC_ANALYZER_HPP

#include <algorithm>
#include <cctype>
#include <cmath>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

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

struct Keyword {
    string signal;
    int weight;
};

struct IntentResult {
    AlgoType type;
    int confidence;
    string domain;
    int rawScore;
    vector<string> matchedSignals;
    vector<string> penalties;
};

class LogicAnalyzer {
private:
    struct DocVector {
        map<string, double> tf;
        double magnitude = 0.0;
    };

    map<AlgoType, vector<Keyword>> brain;
    vector<pair<string, string>> normalizations;

    // TF-IDF engine structures
    map<AlgoType, DocVector> docVectors;
    map<string, double> idf;
    set<string> vocabulary;

    static bool containsPhrase(const string& input, const string& phrase) {
        return input.find(phrase) != string::npos;
    }

    static string collapseSpaces(const string& input) {
        stringstream ss(input);
        string word;
        string out;

        while(ss >> word) {
            if(!out.empty()) out += " ";
            out += word;
        }

        return out;
    }

    static int editDistanceAtMostTwo(const string& a, const string& b) {
        const int n = (int)a.size(), m = (int)b.size();
        if(abs(n - m) > 2) return 3;

        vector<int> prev(m + 1), curr(m + 1);
        iota(prev.begin(), prev.end(), 0);

        for(int i = 1; i <= n; i++) {
            curr[0] = i;
            int rowBest = curr[0];

            for(int j = 1; j <= m; j++) {
                int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
                curr[j] = min({prev[j] + 1, curr[j - 1] + 1, prev[j - 1] + cost});
                rowBest = min(rowBest, curr[j]);
            }

            if(rowBest > 2) return 3;
            swap(prev, curr);
        }

        return prev[m];
    }

    static vector<string> tokenize(const string& input) {
        stringstream ss(input);
        vector<string> tokens;
        string word;

        while(ss >> word) tokens.push_back(word);
        return tokens;
    }

    string getDomainName(AlgoType type) const {
        int val = static_cast<int>(type);
        if(val >= 1 && val <= 9) return "Graphs";
        if(val >= 10 && val <= 14) return "Trees";
        if(val >= 15 && val <= 24) return "Dynamic Programming";
        if(val >= 25 && val <= 30) return "Stacks & Queues";
        if(val >= 31 && val <= 34) return "Linear & Two Pointers";
        if(val >= 35 && val <= 39) return "Linked List";
        if(val >= 40 && val <= 44) return "Heaps & Hashing";
        if(val >= 45 && val <= 49) return "Strings";
        if(val >= 50) return "Search & Math";
        return "General";
    }

public:
    LogicAnalyzer() {
        normalizations = {
            {"minimum path", "shortest path"},
            {"minimum distance", "shortest path"},
            {"least distance", "shortest path"},
            {"least weight", "shortest path weighted"},
            {"least weights", "shortest path weighted"},
            {"minimum weight", "shortest path weighted"},
            {"minimum weights", "shortest path weighted"},
            {"least cost route", "shortest path"},
            {"cheapest route", "shortest path"},
            {"minimum cost route", "shortest path"},
            {"lowest cost", "minimum cost"},
            {"roads have toll", "weighted"},
            {"road toll", "weighted"},
            {"edge cost", "weighted"},
            {"latency credit", "negative weight"},
            {"negative toll", "negative weight"},
            {"no negative edges", "non negative"},
            {"positive weights", "non negative"},
            {"fewest edges", "unweighted shortest path"},
            {"minimum number of edges", "unweighted shortest path"},
            {"course schedule", "topological dependency"},
            {"task ordering", "topological dependency"},
            {"precedence constraints", "topological dependency"},
            {"connect all", "spanning"},
            {"all nodes", "spanning"},
            {"maximize minimum", "bs answer"},
            {"minimize maximum", "bs answer"},
            {"binary search on answer", "bs answer"},
            {"answer space", "search space"},
            {"next greater", "nge"},
            {"nearest greater", "nge"},
            {"largest rectangle", "histogram"},
            {"autocomplete", "trie prefix dictionary"},
            {"auto complete", "trie prefix dictionary"},
            {"palindrome", "palindromic"},
            {"running median", "streaming median"},
            {"continuous stream", "streaming"},
            {"disjoint set", "dsu union find"}
        };

        brain[AlgoType::DIJKSTRA] = {{"dijkstra", 14}, {"shortest path", 8}, {"weighted", 5}, {"non negative", 7}, {"single source", 4}};
        brain[AlgoType::BFS] = {{"unweighted shortest path", 12}, {"unweighted", 7}, {"level order", 6}, {"minimum edges", 6}, {"queue", 2}};
        brain[AlgoType::DFS] = {{"dfs", 10}, {"recursion", 4}, {"reachability", 5}, {"backtracking", 4}, {"connected component", 4}};
        brain[AlgoType::TOPO_SORT] = {{"topological", 12}, {"dependency", 8}, {"dag", 7}, {"tasks", 4}, {"course", 4}};
        brain[AlgoType::KRUSKAL] = {{"kruskal", 12}, {"mst", 12}, {"spanning", 9}, {"minimum cost", 5}, {"connect all", 5}};
        brain[AlgoType::BELLMAN_FORD] = {{"bellman", 14}, {"negative weight", 14}, {"negative edge", 14}, {"negative cycle", 16}, {"shortest path", 4}};
        brain[AlgoType::FLOYD_WARSHALL] = {{"floyd", 14}, {"all pairs", 13}, {"apsp", 13}, {"matrix shortest", 8}};
        brain[AlgoType::TARJAN_SCC] = {{"tarjan", 14}, {"strongly connected", 14}, {"scc", 12}, {"critical", 5}};
        brain[AlgoType::DSU] = {{"dsu", 12}, {"union find", 12}, {"disjoint", 10}, {"groups", 4}};

        brain[AlgoType::LCA_BINARY_LIFTING] = {{"lca", 13}, {"ancestor", 10}, {"binary lifting", 12}, {"distance between nodes", 8}};
        brain[AlgoType::TREE_DIAMETER] = {{"diameter", 12}, {"longest path", 9}, {"farthest", 6}};
        brain[AlgoType::BURN_TREE] = {{"burn", 10}, {"fire", 10}, {"spread", 6}, {"infection", 6}};
        brain[AlgoType::MORRIS_TRAVERSAL] = {{"morris", 13}, {"o 1 space", 8}, {"inorder", 3}};
        brain[AlgoType::BST_VALIDATE] = {{"validate bst", 12}, {"binary search tree", 8}};

        brain[AlgoType::DP_KNAPSACK] = {{"knapsack", 13}, {"capacity", 7}, {"weight", 5}, {"profit", 6}};
        brain[AlgoType::DP_LCS] = {{"common subsequence", 12}, {"lcs", 12}, {"edit distance", 6}};
        brain[AlgoType::DP_LIS] = {{"increasing subsequence", 12}, {"lis", 12}, {"longest increasing", 10}};
        brain[AlgoType::DP_GRID_PATH] = {{"grid path", 12}, {"matrix path", 9}, {"unique paths", 7}};
        brain[AlgoType::DP_STOCK] = {{"stock", 11}, {"buy sell", 11}, {"cooldown", 9}, {"transaction", 6}};
        brain[AlgoType::DP_PARTITION_MCM] = {{"mcm", 12}, {"partition", 9}, {"matrix chain", 12}, {"range dp", 7}};
        brain[AlgoType::DP_TREE] = {{"tree dp", 13}, {"independent set", 9}, {"node weight", 6}};
        brain[AlgoType::DP_BITMASK] = {{"bitmask", 12}, {"tsp", 13}, {"masking", 9}, {"subset dp", 8}, {"visit all", 5}};
        brain[AlgoType::DP_DIGIT] = {{"digit dp", 13}, {"sum of digits", 11}, {"count between", 7}};
        brain[AlgoType::MATRIX_EXP] = {{"matrix exponentiation", 13}, {"linear recurrence", 12}, {"nth fibonacci", 6}};

        brain[AlgoType::STACK_PARENTHESES] = {{"balanced", 10}, {"parenthesis", 10}, {"valid brackets", 9}};
        brain[AlgoType::STACK_NGE] = {{"nge", 12}, {"nearest smaller", 9}, {"monotonic stack", 8}};
        brain[AlgoType::STACK_HISTOGRAM] = {{"histogram", 13}, {"largest area", 10}, {"bar area", 6}, {"rectangle", 4}};
        brain[AlgoType::SLIDING_WINDOW_MAX] = {{"sliding window maximum", 13}, {"window max", 11}, {"deque", 6}};
        brain[AlgoType::LRU_CACHE] = {{"lru", 13}, {"cache", 11}, {"least recently used", 12}};
        brain[AlgoType::STACK_REMOVE_K] = {{"remove k", 11}, {"smallest number", 9}, {"digits", 5}};

        brain[AlgoType::THREE_SUM] = {{"3sum", 12}, {"triplet", 9}, {"three sum", 12}};
        brain[AlgoType::TRAPPING_RAIN_WATER] = {{"trap", 10}, {"rain", 10}, {"water", 8}, {"elevation", 6}};
        brain[AlgoType::CONTAINER_WATER] = {{"container", 11}, {"most water", 11}, {"walls", 6}};
        brain[AlgoType::SLIDING_WINDOW_VAR] = {{"variable window", 11}, {"smallest subarray", 9}, {"unique characters", 8}, {"longest substring", 7}};

        brain[AlgoType::LL_REVERSE] = {{"reverse list", 12}, {"reversal", 6}};
        brain[AlgoType::LL_K_REVERSE] = {{"reverse in k", 13}, {"k groups", 13}, {"group reversal", 11}};
        brain[AlgoType::LL_CYCLE_DETECTION] = {{"cycle", 8}, {"loop", 8}, {"detect cycle", 11}, {"intersection", 6}};
        brain[AlgoType::LL_FLATTEN] = {{"flatten", 11}, {"multilevel", 9}, {"linked list flatten", 12}};
        brain[AlgoType::LL_MERGE_SORT] = {{"sort list", 11}, {"merge sort linked list", 12}};

        brain[AlgoType::HEAP_KTH_LARGEST] = {{"kth largest", 12}, {"k smallest", 11}, {"min heap", 6}};
        brain[AlgoType::HEAP_MEDIAN_STREAM] = {{"median", 10}, {"streaming median", 14}, {"streaming", 5}};
        brain[AlgoType::HEAP_MERGE_K_LISTS] = {{"merge k", 11}, {"k sorted", 11}, {"multiple lists", 6}};
        brain[AlgoType::HASH_SUBARRAY_SUM_K] = {{"subarray sum", 12}, {"target sum", 9}, {"equals k", 11}, {"prefix sum", 5}};
        brain[AlgoType::HASH_LONGEST_CONSECUTIVE] = {{"consecutive", 11}, {"longest sequence", 9}, {"unordered set", 3}};

        brain[AlgoType::STR_KMP] = {{"kmp", 12}, {"pattern", 7}, {"substring match", 8}, {"lps", 6}};
        brain[AlgoType::STR_Z_ALGO] = {{"z algo", 12}, {"z function", 12}, {"matching", 4}};
        brain[AlgoType::STR_TRIE] = {{"trie", 14}, {"prefix", 10}, {"dictionary", 7}};
        brain[AlgoType::STR_MANACHER] = {{"manacher", 14}, {"longest palindromic", 12}, {"palindromic substring", 8}};
        brain[AlgoType::STR_RABIN_KARP] = {{"rabin karp", 13}, {"rolling hash", 13}, {"hash matching", 9}};

        brain[AlgoType::MATH_BS_ON_ANSWER] = {{"bs answer", 15}, {"aggressive", 10}, {"allocate", 10}, {"search space", 6}, {"monotonic", 5}};
        brain[AlgoType::MATH_SIEVE] = {{"prime", 9}, {"sieve", 12}, {"eratosthenes", 12}};
        brain[AlgoType::MATH_MOD_EXP] = {{"power mod", 11}, {"exponentiation", 9}, {"large power", 6}};
        brain[AlgoType::MATH_NCR] = {{"ncr", 12}, {"combination", 9}, {"npr", 6}, {"permutation", 6}};
        brain[AlgoType::MATH_BIT_MANIP] = {{"bits", 9}, {"xor", 9}, {"set bit", 6}, {"bitwise", 6}};

        // Build TF-IDF representations
        map<string, set<AlgoType>> docFreq;
        int numDocs = 0;

        for(const auto& entry : brain) {
            AlgoType type = entry.first;
            numDocs++;
            for(const auto& k : entry.second) {
                string normalizedSignal = normalize(k.signal);
                vector<string> words = tokenize(normalizedSignal);
                for(const string& w : words) {
                    docVectors[type].tf[w] += k.weight;
                    docFreq[w].insert(type);
                    vocabulary.insert(w);
                }
            }
        }

        for(const string& w : vocabulary) {
            int df = docFreq[w].size();
            idf[w] = log((numDocs + 1.0) / (df + 1.0)) + 1.0;
        }

        for(auto& [type, doc] : docVectors) {
            double sumSq = 0.0;
            for(auto& [word, tfVal] : doc.tf) {
                double tfIdfVal = tfVal * idf[word];
                sumSq += tfIdfVal * tfIdfVal;
            }
            doc.magnitude = sqrt(sumSq);
        }
    }

    string normalize(string input) const {
        transform(input.begin(), input.end(), input.begin(), [](unsigned char ch) {
            return (char)tolower(ch);
        });

        for(char& ch : input) {
            if(!isalnum((unsigned char)ch)) ch = ' ';
        }

        input = collapseSpaces(input);

        for(const auto& [from, to] : normalizations) {
            size_t pos = 0;
            while((pos = input.find(from, pos)) != string::npos) {
                input.replace(pos, from.size(), to);
                pos += to.size();
            }
        }

        return collapseSpaces(input);
    }

    vector<IntentResult> detectIntent(string input) const {
        string normalized = normalize(input);
        vector<string> tokens = tokenize(normalized);

        map<string, double> queryTf;
        map<AlgoType, vector<string>> matched;
        map<AlgoType, vector<string>> penalties;

        // Populate query TF vector with exact and fuzzy matching
        for(const string& q : tokens) {
            if(vocabulary.count(q)) {
                queryTf[q] += 1.0;
            } else {
                string bestMatch = "";
                double bestDist = 3.0;
                for(const string& v : vocabulary) {
                    if(v.size() >= 5 && q.size() >= 5) {
                        int dist = editDistanceAtMostTwo(q, v);
                        if(dist <= 1 && dist < bestDist) {
                            bestMatch = v;
                            bestDist = dist;
                        }
                    }
                }
                if(!bestMatch.empty()) {
                    queryTf[bestMatch] += 0.8;
                    for(const auto& entry : brain) {
                        for(const auto& k : entry.second) {
                            if(k.signal.find(bestMatch) != string::npos) {
                                matched[entry.first].push_back(bestMatch + " (fuzzy)");
                            }
                        }
                    }
                }
            }
        }

        map<string, double> queryTfIdf;
        double querySumSq = 0.0;
        for(auto& [word, freq] : queryTf) {
            double tfIdfVal = freq * idf.at(word);
            queryTfIdf[word] = tfIdfVal;
            querySumSq += tfIdfVal * tfIdfVal;
        }
        double queryMagnitude = sqrt(querySumSq);

        map<AlgoType, double> scores;
        for(auto& [type, doc] : docVectors) {
            double dotProduct = 0.0;
            for(auto& [word, queryVal] : queryTfIdf) {
                if(doc.tf.count(word)) {
                    double docVal = doc.tf.at(word) * idf.at(word);
                    dotProduct += queryVal * docVal;
                }
            }
            double cosineSim = 0.0;
            if(queryMagnitude > 0.0 && doc.magnitude > 0.0) {
                cosineSim = dotProduct / (queryMagnitude * doc.magnitude);
            }
            scores[type] = cosineSim;
        }

        // Phrase boosts and matched signal collection
        for(const auto& entry : brain) {
            AlgoType type = entry.first;
            for(const auto& k : entry.second) {
                if(containsPhrase(normalized, k.signal)) {
                    scores[type] += (k.weight / 50.0);
                    matched[type].push_back(k.signal);
                }
            }
        }

        for(auto& [type, list] : matched) {
            sort(list.begin(), list.end());
            list.erase(unique(list.begin(), list.end()), list.end());
        }

        // Domain & Context evaluation
        bool isTree = containsPhrase(normalized, "tree") || containsPhrase(normalized, "bst");
        bool hasNonNegative = containsPhrase(normalized, "non negative") ||
                              containsPhrase(normalized, "without negative") ||
                              containsPhrase(normalized, "no negative");
        bool hasNegative = containsPhrase(normalized, "negative") && !hasNonNegative;
        bool hasSourceDestination = containsPhrase(normalized, "source") &&
                                    (containsPhrase(normalized, "destination") ||
                                     containsPhrase(normalized, "target"));
        bool isGraph = containsPhrase(normalized, "graph") || containsPhrase(normalized, "node") ||
                       containsPhrase(normalized, "nodes") ||
                       containsPhrase(normalized, "vertices") || containsPhrase(normalized, "edges") ||
                       containsPhrase(normalized, "city") || containsPhrase(normalized, "cities") ||
                       containsPhrase(normalized, "road") || containsPhrase(normalized, "route") ||
                       hasSourceDestination;
        bool isString = containsPhrase(normalized, "string") || containsPhrase(normalized, "text") ||
                        containsPhrase(normalized, "characters") || containsPhrase(normalized, "word");
        bool isList = containsPhrase(normalized, "linked list") || containsPhrase(normalized, "pointer");
        bool allPairs = containsPhrase(normalized, "all pairs") || containsPhrase(normalized, "between every");

        for(auto& [type, score] : scores) {
            double multiplier = 1.0;
            string domain = getDomainName(type);

            if(isTree) {
                if(domain == "Trees" || type == AlgoType::DP_TREE) {
                    multiplier *= 1.4;
                } else if(domain == "Graphs" || domain == "Linked List") {
                    multiplier *= 0.5;
                    penalties[type].push_back("tree context reduces generic shortest-path/linked-list fit");
                }
            }

            if(isGraph) {
                if(domain == "Graphs") {
                    multiplier *= 1.4;
                } else if(domain == "Linked List") {
                    multiplier *= 0.5;
                    penalties[type].push_back("graph context is not linked-list cycle detection");
                } else if(type == AlgoType::DP_KNAPSACK) {
                    multiplier *= 0.5;
                    penalties[type].push_back("graph/route context is not capacity DP");
                }
            }

            if(isString) {
                if(domain == "Strings" || type == AlgoType::SLIDING_WINDOW_VAR) {
                    multiplier *= 1.4;
                }
            }

            if(isList) {
                if(domain == "Linked List") {
                    multiplier *= 1.4;
                } else if(domain == "Graphs") {
                    multiplier *= 0.5;
                    penalties[type].push_back("linked list is not a weighted graph");
                }
            }

            if(hasNegative) {
                if(type == AlgoType::BELLMAN_FORD || type == AlgoType::FLOYD_WARSHALL) {
                    multiplier *= 1.5;
                } else if(type == AlgoType::DIJKSTRA) {
                    multiplier *= 0.2;
                    penalties[type].push_back("Dijkstra requires non-negative weights");
                }
            }

            if(allPairs) {
                if(type == AlgoType::FLOYD_WARSHALL) {
                    multiplier *= 1.5;
                }
            }

            score *= multiplier;
        }

        vector<pair<AlgoType, double>> ranked;
        for(const auto& p : scores) {
            if(p.second > 0.05) {
                ranked.push_back(p);
            }
        }

        sort(ranked.begin(), ranked.end(), [](const auto& a, const auto& b) {
            if(abs(a.second - b.second) < 1e-6) return (int)a.first < (int)b.first;
            return a.second > b.second;
        });

        vector<IntentResult> results;
        int count = min((int)ranked.size(), 3);

        vector<double> softmaxProbs(count, 0.0);
        if(count > 0) {
            double sumExp = 0.0;
            for(int i = 0; i < count; i++) {
                sumExp += exp(8.0 * ranked[i].second);
            }
            for(int i = 0; i < count; i++) {
                softmaxProbs[i] = exp(8.0 * ranked[i].second) / sumExp;
            }
        }

        for(int i = 0; i < count; i++) {
            AlgoType type = ranked[i].first;
            int confidence = (int)(softmaxProbs[i] * 100.0);

            set<string> seenSignals(matched[type].begin(), matched[type].end());
            set<string> seenPenalties(penalties[type].begin(), penalties[type].end());

            results.push_back({
                type,
                confidence,
                getDomainName(type),
                (int)(ranked[i].second * 100),
                vector<string>(seenSignals.begin(), seenSignals.end()),
                vector<string>(seenPenalties.begin(), seenPenalties.end())
            });
        }

        if(results.empty()) {
            results.push_back({AlgoType::NONE, 0, "Undefined", 0, {}, {}});
        }

        return results;
    }
};

#endif
