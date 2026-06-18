# Pseudo2CPP - Build Script

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET = transpiler
TEST_TARGET = tests/intent_tests

all: $(TARGET)

$(TARGET): main.cpp LogicAnalyzer.hpp AlgorithmRegistry.hpp Generator.hpp Templates.hpp
	@echo "[*] Compiling the Transpiler Engine..."
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)
	@echo "[+] Build Successful! Run using ./$(TARGET)"

COMPILER_TEST_TARGET = tests/compiler_tests

test: $(TEST_TARGET) $(COMPILER_TEST_TARGET)
	@echo "[*] Running intent analyzer tests..."
	./$(TEST_TARGET)
	@echo "[*] Running compiler tests..."
	./$(COMPILER_TEST_TARGET)

$(TEST_TARGET): tests/intent_tests.cpp LogicAnalyzer.hpp AlgorithmRegistry.hpp
	@echo "[*] Compiling intent tests..."
	$(CXX) $(CXXFLAGS) tests/intent_tests.cpp -o $(TEST_TARGET)

$(COMPILER_TEST_TARGET): tests/compiler_tests.cpp TranspilerCore.hpp
	@echo "[*] Compiling compiler tests..."
	$(CXX) $(CXXFLAGS) tests/compiler_tests.cpp -o $(COMPILER_TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

list: $(TARGET)
	./$(TARGET) --list-algorithms

clean:
	@echo "[*] Cleaning up build files..."
	rm -f $(TARGET) $(TEST_TARGET) $(COMPILER_TEST_TARGET)
	rm -rf out
	@echo "[+] Clean complete."
