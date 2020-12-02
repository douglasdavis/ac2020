all: day1 day2
	-@echo "Done"

day1:
	cc day1.c -o day1

day2:
	cc day2.c -o day2

.PHONY: clean

clean:
	rm -f day1 day2
