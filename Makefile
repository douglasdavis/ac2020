CC := cc
CFLAGS := -O3 -mtune=native -march=native -std=c99 -Wall


all: day1 day2 day3 day5 day6 day8
	-@echo "Done"

day1: day1.c
	$(CC) $(CFLAGS) day1.c -o day1

day2: day2.c
	$(CC) $(CFLAGS) day2.c -o day2

day3: day3.c
	$(CC) $(CFLAGS) day3.c -o day3

day5: day5.c
	$(CC) $(CFLAGS) day5.c -o day5

day6: day6.c
	$(CC) $(CFLAGS) day6.c -o day6

day8: day8.c
	$(CC) $(CFLAGS) day8.c -o day8

.PHONY: clean all

clean:
	rm -f day1 day2 day3 day5 day6 day8
