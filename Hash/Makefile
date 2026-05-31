CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TEST_LIB = libHashTest.a
TARGET = run_tests

all: $(TARGET)

$(TARGET): Hash.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) Hash.o $(TEST_LIB)

Hash.o: Hash.cpp HashTable.h
	$(CXX) $(CXXFLAGS) -c Hash.cpp -o Hash.o

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f Hash.o $(TARGET)

.PHONY: all run clean
