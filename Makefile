all: day1 day2 day3 day4 day5
	-@echo "Done"

day1: day1.c
	cc day1.c -o day1

day2: day2.c
	cc day2.c -o day2

day3: day3.c
	cc day3.c -o day3

day4: day4.c
	cc day4.c -o day4

day5: day5.c
	cc day5.c -o day5

.PHONY: clean all

clean:
	rm -f day1 day2 day3 day4 day5
