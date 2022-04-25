CXXFLAGS := -ggdb3 -O0 -Wall -fsanitize=address
CC := g++

all: solution

solution: solution.cpp
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) solution

.PHONY: clean all
