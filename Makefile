# Universal DSA Transpiler Engine - Build Script

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall
TARGET = transpiler

all: $(TARGET)

$(TARGET): main.cpp
	@echo "[*] Compiling the Transpiler Engine..."
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)
	@echo "[+] Build Successful! Run using ./$(TARGET)"

clean:
	@echo "[*] Cleaning up build files..."
	rm -f $(TARGET) solution.cpp
	@echo "[+] Clean complete."