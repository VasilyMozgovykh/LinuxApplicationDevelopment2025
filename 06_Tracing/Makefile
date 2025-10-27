CC = gcc
CFLAGS = -O3
GENERATES = move protect.so

All: move protect.so

move: move.c
	$(CC) $(CFLAGS) $< -o $@

protect.so: protect.c
	$(CC) $(CFLAGS) -fPIC -shared -ldl $< -o $@

clean:
	rm -rf $(GENERATES)
