#ifndef SEARCH_MATH_EXPERT_HPP
#define SEARCH_MATH_EXPERT_HPP

#include <bits/stdc++.h>
using namespace std;

class SearchMathExpert {
public:
    // Pattern: Find the maximum/minimum value such that check(mid) is true
    static string getBinarySearchOnAnswer() {
        return "// Complexity: O(log(Range) * Cost_of_Check)\n"
               "bool check(ll mid, vector<int>& a, int k) {\n"
               "    // Implementation-specific logic (e.g., Aggressive Cows, Allocate Books)\n"
               "    return true; \n"
               "}\n"
               "ll solveBS(vector<int>& a, int k) {\n"
               "    ll low = 0, high = 1e18, res = -1;\n"
               "    while(low <= high) {\n"
               "        ll mid = low + (high - low) / 2;\n"
               "        if(check(mid, a, k)) { res = mid; low = mid + 1; } // Maximize mid\n"
               "        else high = mid - 1;\n"
               "    } return res;\n}\n\n";
    }

    /* --- 2. NUMBER THEORY (The Encryption Core) --- */

    
    // Sieve of Eratosthenes: Prime generation O(N log log N)
    static string getSieve() {
        return "vector<bool> sieve(int n) {\n"
               "    vector<bool> is_prime(n + 1, true);\n"
               "    is_prime[0] = is_prime[1] = false;\n"
               "    for (int p = 2; p * p <= n; p++)\n"
               "        if (is_prime[p])\n"
               "            for (int i = p * p; i <= n; i += p) is_prime[i] = false;\n"
               "    return is_prime;\n}\n\n";
    }

    // Modular Exponentiation: (a^b) % m in O(log b)
    static string getModExp() {
        return "ll power(ll a, ll b, ll m) {\n"
               "    ll res = 1; a %= m;\n"
               "    while (b > 0) {\n"
               "        if (b & 1) res = (__int128)res * a % m; // __int128 to prevent overflow\n"
               "        a = (__int128)a * a % m; b >>= 1;\n"
               "    } return res;\n}\n\n";
    }

    /* --- 3. COMBINATORICS (Placement Math) --- */

    // nCr with Modular Inverse (Fermat's Little Theorem)
    static string getNCR() {
        return "ll nCr(int n, int r, vector<ll>& fact) {\n"
               "    if (r < 0 || r > n) return 0;\n"
               "    ll num = fact[n];\n"
               "    ll den = (power(fact[r], MOD - 2, MOD) * power(fact[n - r], MOD - 2, MOD)) % MOD;\n"
               "    return (num * den) % MOD;\n}\n\n";
    }

    /* --- 4. BIT MANIPULATION (The Low-Level Expert) --- */

    
    static string getBitwiseOps() {
        return "// Standard bit utilities used in Subnetting and Masks\n"
               "bool isPowerOfTwo(ll n) { return n > 0 && (n & (n - 1)) == 0; }\n"
               "int countSetBits(ll n) { return __builtin_popcountll(n); }\n"
               "// Find the only non-repeating element in a stream where others repeat twice\n"
               "int findUnique(vector<int>& a) { int res = 0; for(int x : a) res ^= x; return res; }\n\n";
    }
};

#endif