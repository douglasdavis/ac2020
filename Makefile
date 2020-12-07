all: day1 day2 day3
	-@echo "Done"

day1: day1.c
	cc day1.c -o day1

day2: day2.c
	cc day2.c -o day2

day3: day3.c
	cc day3.c -o day3

.PHONY: clean all

clean:
	rm -f day1 day2 day3
