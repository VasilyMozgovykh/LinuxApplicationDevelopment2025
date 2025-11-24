CC = gcc
CFLAGS = -Wall -Werror -O3
GENERATES = lab lab1* lab2* lab3*

All: lab lab1 lab2 lab3

run: lab lab1 lab2 lab3
	./lab;
	./lab1 8;
	./lab2 ' @' 5;
	./lab3 12 '.#' 4;
	./lab3 11 '.#' 4;
	./lab3 12 '.#' 4;

lab%: lab%.c
	$(CC) $(CFLAGS) $< -o $@

lab1.c: lab.c
	cp lab.c lab1.c;
	patch lab1.c < 0001-Define-size.patch;

lab2.c: lab1.c
	cp lab1.c lab2.c;
	patch lab2.c < 0002-Define-cells.patch;

lab3.c: lab2.c
	cp lab2.c lab3.c
	patch lab3.c < 0003-Define-seed.patch;

clean:
	rm -rf $(GENERATES)
