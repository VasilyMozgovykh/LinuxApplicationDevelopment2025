CC = gcc
FLAGS = -O0 -g

All: range

range: range.c
	$(CC) $(FLAGS) $< -o $@;

test: range gdb1.gdb gdb2.gdb
	@gdb --batch --quiet -x gdb1.gdb ./range | grep "^@@@" > pred1.txt;
	@cmp pred1.txt ground_truth1.txt && echo "Test 1 ok" || echo "Test 1 fail";

	@gdb --batch --quiet -x gdb2.gdb ./range | grep "^@@@" > pred2.txt;
	@cmp pred2.txt ground_truth2.txt && echo "Test 2 ok" || echo "Test 2 fail";

clean:
	rm -rf range pred1.txt pred2.txt;
