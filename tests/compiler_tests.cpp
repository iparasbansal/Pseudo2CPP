#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "../TranspilerCore.hpp"

using namespace std;

static string stripWhitespace(string s) {
    string res = "";
    for(char c : s) {
        if(!isspace(c)) res += c;
    }
    return res;
}

struct CompilerTestCase {
    string name;
    string pseudocode;
    string expectedCPP;
};

void runCase(const CompilerTestCase& tc) {
    string got = transpiler::TranspilerCore::transpile(tc.pseudocode);
    string gotClean = stripWhitespace(got);
    string expectedClean = stripWhitespace(tc.expectedCPP);
    
    if (gotClean.find("[Transpilation Error]") != string::npos || gotClean != expectedClean) {
        cerr << "[FAIL] " << tc.name << "\n"
             << "  Input:\n" << tc.pseudocode << "\n"
             << "  Expected C++:\n" << tc.expectedCPP << "\n"
             << "  Got C++:\n" << got << "\n";
        exit(1);
    }
    cout << "[PASS] " << tc.name << "\n";
}

int main() {
    vector<CompilerTestCase> cases = {
        {
            "variable declaration",
            "let x = 10",
            "auto x = 10;"
        },
        {
            "binary expression",
            "let y = x + 5 * 2",
            "auto y = (x + (5 * 2));"
        },
        {
            "for loop translation",
            "for i from 0 to n - 1 {\n"
            "    sum = sum + arr[i]\n"
            "}",
            "for (int i = 0; i <= (n - 1); i++) {\n"
            "    sum = (sum + arr[i]);\n"
            "}"
        },
        {
            "if-else statement",
            "if (val % 2 == 0) {\n"
            "    return 1\n"
            "} else {\n"
            "    return 0\n"
            "}",
            "if ((val % 2 == 0)) {\n"
            "    return 1;\n"
            "} else {\n"
            "    return 0;\n"
            "}"
        },
        {
            "function definition with templates",
            "function solve(arr, n) {\n"
            "    return arr[n]\n"
            "}",
            "template<typename T_arr, typename T_n>\n"
            "auto solve(T_arr arr, T_n n) {\n"
            "    return arr[n];\n"
            "}"
        }
    };
    
    for(const auto& tc : cases) {
        runCase(tc);
    }
    
    cout << "[+] All compiler tests passed.\n";
    return 0;
}
