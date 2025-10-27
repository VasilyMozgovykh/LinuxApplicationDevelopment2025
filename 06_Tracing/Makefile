CC = gcc
CFLAGS = -O3
GENERATES = move

All: move

move: move.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(GENERATES)
