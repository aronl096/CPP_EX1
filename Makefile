# Makefile

CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Source files for different targets
DEMO_SOURCES=Graph.cpp Algorithms.cpp Demo.cpp
TEST_SOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp

# Object files
DEMO_OBJECTS=$(subst .cpp,.o,$(DEMO_SOURCES))
TEST_OBJECTS=$(subst .cpp,.o,$(TEST_SOURCES))

# Default target
all: demo test

# Build demo executable
demo: $(DEMO_OBJECTS)
	$(CXX) $(CXXFLAGS) -o demo $(DEMO_OBJECTS)

# Build test executable
test: $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJECTS)

# Compile each source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the demo executable
run: demo
	./demo

# Run tests
valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

# Clean up build artifacts
clean:
	rm -f *.o demo test