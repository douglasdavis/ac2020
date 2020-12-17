CC := cc
CXX := c++
CFLAGS := -O2 -mtune=native -march=native -std=c99 -Wall
CXXFLAGS := -O2 -mtune=native -march=native -std=c++17 -Wall

all: day01 day02 day03 day05 day06 day08 day09 day10
	-@echo "Done"

day01: day01.c
	$(CC) $(CFLAGS) day01.c -o day01

day02: day02.c
	$(CC) $(CFLAGS) day02.c -o day02

day03: day03.c
	$(CC) $(CFLAGS) day03.c -o day03

day05: day05.c
	$(CC) $(CFLAGS) day05.c -o day05

day06: day06.c
	$(CC) $(CFLAGS) day06.c -o day06

day08: day08.c
	$(CC) $(CFLAGS) day08.c -o day08

day09: day09.cpp
	$(CXX) $(CXXFLAGS) day09.cpp -o day09

day10: day10.cpp
	$(CXX) $(CXXFLAGS) day10.cpp -o day10

.PHONY: clean all

clean:
	rm -f day01 day02 day03 day05 day06 day08 day09 day10
