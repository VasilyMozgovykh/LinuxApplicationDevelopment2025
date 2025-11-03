CFLAGS = -Wall -Werror -O0 -g

bin_PROGRAMS=rhasher

rhasher_SOURCES=rhasher.c

rhasher_LDADD=$(LIBS)

rhasher_CPPFLAGS=$(DEFS)

TESTS = tests/test_1.sh tests/test_2.sh tests/test_3.sh

gitclean:
	git clean -df;
	rm -rf *.o rhasher
