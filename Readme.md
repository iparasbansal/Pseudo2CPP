# 🚀 Pseudo2CPP: Universal DSA Transpiler Engine v2.0

An NLP-powered, intelligent C++ code generator designed for Competitive Programming and algorithmic problem-solving. **Pseudo2CPP** analyzes natural language problem statements, detects the underlying algorithmic intent using semantic scoring, and generates a fully optimized, submission-ready C++ boilerplate.


**Developed by:** Paras Bansal
**Github** https://github.com/iparasbansal
**Portfolio** https://parasbansal-portfolio.vercel.app
**LinkedIn** https://linkedin.com/in/iparasbansal
**Codeforces** https://codeforces.com/profile/parasbansal
**CodeChef** https://www.codechef.com/users/i_parasbansal
**LeetCode** https://leetcode.com/u/iparasbansal/


---

## ✨ Key Features

* **🧠 Semantic Intent Detection:** Uses a weighted NLP scoring system to understand problem descriptions (e.g., accurately distinguishing between "shortest path in unweighted graph" vs. "negative weight cycles").
* **⚡ 50+ Expert Algorithms:** Pre-loaded with highly optimized `O(N)` and `O(log N)` C++ templates spanning Graphs, DP, Trees, Strings, Heaps, and Advanced Math.
* **🛡️ Contextual Conflict Resolution:** Automatically resolves algorithmic ambiguity (e.g., applying heavy penalties to Dijkstra if the context explicitly mentions a "Tree" or "Negative Edges").
* **⚙️ Decoupled Architecture:** Clean separation of concerns between the NLP Brain (`LogicAnalyzer`) and the Code Database (`Templates`), making the system highly modular and scalable.
* **🏆 CP-Ready Output:** Generates a complete `solution.cpp` file equipped with Fast I/O, modular `solve()` functions, and test-case loops ready for Codeforces/LeetCode submission.

---

## 🏗️ System Architecture

The transpiler follows a highly modular, 3-tier architectural pattern:

1. **The Brain (`LogicAnalyzer.hpp`):** Normalizes input synonyms, applies domain-specific contextual boosts/penalties, and calculates a percentage-based **Confidence Score** for the predicted algorithm.
2. **The Muscle (`Templates.hpp` & Expert Modules):** A comprehensive database of optimized C++ snippets utilizing modern C++17 features.
3. **The Glue (`main.cpp` & `Generator.hpp`):** The CLI entry point that acts as a Factory, linking the detected intent to the specific template and injecting competitive programming boilerplate.

### 📂 Directory Structure
```text
Pseudo2CPP/
├── LogicAnalyzer.hpp    # NLP & Semantic Scoring Engine
├── Generator.hpp        # Algorithm-to-Template Router
├── Templates.hpp        # Core Logic & Code Snippets
├── main.cpp             # CLI Engine & Boilerplate Injector
├── Makefile             # Build automation
└── examples/            
    └── queries.txt      # Sample complex queries for testing