#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "AlgorithmRegistry.hpp"
#include "Generator.hpp"
#include "LogicAnalyzer.hpp"
#include "Templates.hpp"
#include "TranspilerCore.hpp"

using namespace std;
namespace fs = std::filesystem;

struct CliOptions {
    string query;
    string inputFile;
    string outputFile = "solution.cpp";
    bool explain = false;
    bool listAlgorithms = false;
    bool help = false;
};

static void printUsage() {
    cout << "Pseudo2CPP - Explainable DSA Transpiler\n\n"
         << "Usage:\n"
         << "  ./transpiler --query \"shortest path with negative weights\" [--explain]\n"
         << "  ./transpiler --input examples/query.txt --output solution.cpp\n"
         << "  ./transpiler --list-algorithms\n\n"
         << "Options:\n"
         << "  --query <text>          Analyze this problem statement.\n"
         << "  --input <file>          Read the problem statement from a file.\n"
         << "  --output <file>         Write generated C++ code here. Default: solution.cpp\n"
         << "  --explain               Show matched signals and penalties.\n"
         << "  --list-algorithms       Print supported algorithms and complexity metadata.\n"
         << "  --help                  Show this help message.\n";
}

static bool parseArgs(int argc, char* argv[], CliOptions& options) {
    for(int i = 1; i < argc; i++) {
        string arg = argv[i];

        if(arg == "--help" || arg == "-h") {
            options.help = true;
        } else if(arg == "--explain") {
            options.explain = true;
        } else if(arg == "--list-algorithms") {
            options.listAlgorithms = true;
        } else if(arg == "--query" || arg == "-q") {
            if(i + 1 >= argc) {
                cerr << "[!] Missing value for " << arg << "\n";
                return false;
            }
            i++;
            while(i < argc) {
                string part = argv[i];
                if(part.rfind("--", 0) == 0) {
                    i--;
                    break;
                }
                if(!options.query.empty()) options.query += " ";
                options.query += part;
                i++;
            }
        } else if(arg == "--input" || arg == "-i") {
            if(i + 1 >= argc) {
                cerr << "[!] Missing value for " << arg << "\n";
                return false;
            }
            options.inputFile = argv[++i];
        } else if(arg == "--output" || arg == "-o") {
            if(i + 1 >= argc) {
                cerr << "[!] Missing value for " << arg << "\n";
                return false;
            }
            options.outputFile = argv[++i];
        } else {
            cerr << "[!] Unknown option: " << arg << "\n";
            return false;
        }
    }

    return true;
}

static string readFile(const string& path) {
    ifstream fin(path);
    if(!fin) return "";

    stringstream buffer;
    buffer << fin.rdbuf();
    return buffer.str();
}

static void printAlgorithms() {
    cout << "Supported Algorithms\n";
    cout << "====================\n";

    for(const AlgorithmProfile& profile : AlgorithmRegistry::all()) {
        cout << "- " << profile.name << " [" << profile.domain << "]\n"
             << "  Time: " << profile.timeComplexity
             << " | Space: " << profile.spaceComplexity << "\n"
             << "  Use: " << profile.useCase << "\n";
    }
}

static void printSignals(const vector<string>& values, const string& label) {
    if(values.empty()) return;

    cout << "    " << label << ": ";
    for(size_t i = 0; i < values.size(); i++) {
        if(i) cout << ", ";
        cout << values[i];
    }
    cout << "\n";
}

static void printRankedResults(const vector<IntentResult>& ranked, bool explain) {
    cout << "[*] Top intent matches:\n";

    for(size_t i = 0; i < ranked.size(); i++) {
        AlgorithmProfile profile = AlgorithmRegistry::get(ranked[i].type);

        cout << "    " << i + 1 << ". " << profile.name
             << " (" << ranked[i].domain << ")"
             << " - " << ranked[i].confidence << "%"
             << " [score: " << ranked[i].rawScore << "]\n";

        if(explain) {
            printSignals(ranked[i].matchedSignals, "matched");
            printSignals(ranked[i].penalties, "penalties");
        }
    }
}

static string inputSkeleton(AlgoType type) {
    switch(type) {
        case AlgoType::DIJKSTRA:
            return "    int n, m, src;\n"
                   "    cin >> n >> m >> src;\n"
                   "    vector<vector<pair<int,int>>> g(n);\n"
                   "    for(int i = 0; i < m; i++) {\n"
                   "        int u, v, w;\n"
                   "        cin >> u >> v >> w;\n"
                   "        g[u].push_back({v, w});\n"
                   "    }\n"
                   "    vector<ll> dist = dijkstra(n, g, src);\n";
        case AlgoType::BFS:
            return "    int n, m, src;\n"
                   "    cin >> n >> m >> src;\n"
                   "    vector<vector<int>> g(n);\n"
                   "    for(int i = 0; i < m; i++) {\n"
                   "        int u, v;\n"
                   "        cin >> u >> v;\n"
                   "        g[u].push_back(v);\n"
                   "        g[v].push_back(u);\n"
                   "    }\n"
                   "    vector<int> dist = bfs(n, g, src);\n";
        case AlgoType::BELLMAN_FORD:
            return "    int n, m, src;\n"
                   "    cin >> n >> m >> src;\n"
                   "    vector<vector<int>> edges;\n"
                   "    for(int i = 0; i < m; i++) {\n"
                   "        int u, v, w;\n"
                   "        cin >> u >> v >> w;\n"
                   "        edges.push_back({u, v, w});\n"
                   "    }\n"
                   "    vector<ll> dist = bellmanFord(n, edges, src);\n";
        case AlgoType::DP_KNAPSACK:
            return "    int n, capacity;\n"
                   "    cin >> n >> capacity;\n"
                   "    vector<int> weight(n), value(n);\n"
                   "    for(int i = 0; i < n; i++) cin >> weight[i];\n"
                   "    for(int i = 0; i < n; i++) cin >> value[i];\n"
                   "    cout << knapsack(capacity, weight, value, n) << '\\n';\n";
        default:
            return "    // TODO: read input and call the generated algorithm above.\n";
    }
}

static bool shouldInvokeGeneratedSolve(const string& transpiled) {
    return transpiled.find("template<") == string::npos &&
           transpiled.find("auto solve(") != string::npos;
}

static string buildSolution(const IntentResult& bestIntent, const string& rawInput) {
    AlgorithmProfile profile = AlgorithmRegistry::get(bestIntent.type);
    string code;

    code += Templates::header();
    code += "// ==========================================\n";
    code += "// Generated by Pseudo2CPP\n";
    code += "// Algorithm: " + profile.name + "\n";
    code += "// Domain: " + profile.domain + "\n";
    code += "// Confidence: " + to_string(bestIntent.confidence) + "%\n";
    code += "// Time: " + profile.timeComplexity + "\n";
    code += "// Space: " + profile.spaceComplexity + "\n";
    code += "// Use case: " + profile.useCase + "\n";
    code += "// Warning: " + profile.warning + "\n";
    code += "// ==========================================\n\n";

    code += Generator::generate(bestIntent.type);

    bool hasCustomSolve = false;
    bool shouldCallSolve = true;

    if (transpiler::TranspilerCore::containsStructuredCode(rawInput)) {
        string transpiled = transpiler::TranspilerCore::transpile(rawInput);
        hasCustomSolve = (transpiled.find("solve(") != string::npos);
        shouldCallSolve = !hasCustomSolve || shouldInvokeGeneratedSolve(transpiled);
        if (hasCustomSolve) {
            code += "\n" + transpiled + "\n";
        } else {
            code += "\nvoid solve() {\n";
            code += transpiled;
            code += "}\n\n";
        }
    } else {
        code += "\nvoid solve() {\n";
        code += inputSkeleton(bestIntent.type);
        code += "}\n\n";
    }

    code += "int main() {\n"
            "    ios::sync_with_stdio(false);\n"
            "    cin.tie(nullptr);\n\n"
            "    int t = 1;\n"
            "    // cin >> t;\n\n";

    if (shouldCallSolve) {
        code += "    while(t--) solve();\n";
    } else {
        code += "    // Custom transpiled solve() may require arguments or a custom driver.\n";
    }

    code += "    return 0;\n"
            "}\n";

    return code;
}

static bool writeSolution(const string& path, const string& code) {
    fs::path outputPath(path);
    if(outputPath.has_parent_path()) {
        fs::create_directories(outputPath.parent_path());
    }

    ofstream fout(path, ios::trunc);
    if(!fout) return false;

    fout << code;
    return true;
}

int main(int argc, char* argv[]) {
    CliOptions options;
    if(!parseArgs(argc, argv, options)) {
        printUsage();
        return 1;
    }

    if(options.help) {
        printUsage();
        return 0;
    }

    if(options.listAlgorithms) {
        printAlgorithms();
        return 0;
    }

    string input = options.query;

    if(!options.inputFile.empty()) {
        input = readFile(options.inputFile);
        if(input.empty()) {
            cerr << "[!] Could not read input file: " << options.inputFile << "\n";
            return 1;
        }
    }

    cout << "========================================================\n";
    cout << "        PSEUDO2CPP EXPLAINABLE TRANSPILER\n";
    cout << "========================================================\n\n";

    if(input.empty()) {
        cout << "[>] Enter pseudocode or problem statement:\n> ";
        getline(cin, input);
    }

    LogicAnalyzer analyzer;
    vector<IntentResult> ranked = analyzer.detectIntent(input);

    if(ranked.empty() || ranked.front().type == AlgoType::NONE) {
        cout << "[!] No confident intent found. Try adding constraints, data structure, or target operation.\n";
        return 0;
    }

    printRankedResults(ranked, options.explain);

    IntentResult bestIntent = ranked.front();
    AlgorithmProfile profile = AlgorithmRegistry::get(bestIntent.type);

    if(bestIntent.confidence < 45) {
        cout << "\n[!] Low confidence result. Generated code is a starting point, not a final recommendation.\n";
    }

    string solution = buildSolution(bestIntent, input);
    if(!writeSolution(options.outputFile, solution)) {
        cerr << "[!] Could not write output file: " << options.outputFile << "\n";
        return 1;
    }

    cout << "\n[+] Selected: " << profile.name << "\n";
    cout << "[+] Generated: " << options.outputFile << "\n";
    cout << "========================================================\n";

    return 0;
}
