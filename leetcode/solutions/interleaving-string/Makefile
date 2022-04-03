CXXFLAGS := -ggdb3 -O0 -Wall
CC := g++

all: solution

solution: solution.cc
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) solution

.PHONY: clean all
