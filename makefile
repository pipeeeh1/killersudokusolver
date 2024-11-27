# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Iincludes  # Add -Iincludes here for all files

# Source files
SRCS = $(wildcard src/*.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output binary name
OUT = solver

# Default target: build the program
all: $(OUT)

$(OUT): $(OBJS) main.o
	$(CXX) $(CXXFLAGS) -o $(OUT) $(OBJS) main.o

# Compile .cpp files into object files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main.cpp into an object file
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Clean up build files
clean:
	rm -f $(OBJS) main.o $(OUT)

# Run the program
run: $(OUT)
	./$(OUT)