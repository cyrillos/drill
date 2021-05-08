CXXFLAGS := -ggdb3 -std=c++17 -O0 -Wall
CC := g++

all: solution

solution: solution.cpp
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) solution

.PHONY: clean all
