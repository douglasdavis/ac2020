all: day1 day2
	-@echo "Done"

day1: day1.c
	cc day1.c -o day1

day2: day2.c
	cc day2.c -o day2

.PHONY: clean

clean:
	rm -f day1 day2
