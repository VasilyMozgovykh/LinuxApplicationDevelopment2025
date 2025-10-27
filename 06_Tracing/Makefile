CC = gcc
CFLAGS = -O3
GENERATES = move protect.so

All: move protect.so

move: move.c
	$(CC) $(CFLAGS) $< -o $@

protect.so: protect.c
	$(CC) $(CFLAGS) -fPIC -shared -ldl $< -o $@

test: move protect.so
	@echo "Running test 1: 'Cant open file'";
	@strace -P "nothing.txt" -e inject=fopen ./move nothing.txt nowhere.txt 2> /dev/null || echo "Test 1 ok";

	@echo "Running test 2: 'Dont copy infile to infile";
	@./move test.txt test.txt && test -f test.txt && echo "Test 2 ok";

	@echo "Running test 3: 'Dont remove PROTECT file";
	@LD_PRELOAD=./protect.so ./move tePROTECT.txt test_2.txt && test -f test_2.txt || echo "Test 3 ok";


clean:
	rm -rf $(GENERATES)
