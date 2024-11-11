# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall

# Source files
SRCS = $(wildcard *.cpp)

# Output binary name
OUT = solver

# Default target: build and run the program
all: $(OUT)

$(OUT): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRCS)

# Clean up build files
clean:
	rm -f $(OUT)

# Run the program
run: $(OUT)
	./$(OUT)