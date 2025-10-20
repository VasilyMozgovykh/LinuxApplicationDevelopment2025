CC = gcc
CFLAGS = -O0 -Wall -Werror
GENERATES = test_esub*.txt test_sed*.txt

All: esub

esub: main.c
	$(CC) $(CFLAGS) $< -o $@

test: esub
	@./esub "abc" "zxc" "abcabcabc" > test_esub1.txt;
	@echo "abcabcabc" | sed -E 's/abc/zxc/' > test_sed1.txt;
	@cmp test_esub1.txt test_sed1.txt && echo "Test 1 success" || echo "Test 1 failed";

clean:
	rm -rf esub $(GENERATES)
