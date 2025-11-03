CFLAGS = -Wall -Werror -O0 -g

bin_PROGRAMS=rhasher

rhasher_SOURCES=rhasher.c

rhasher_LDADD=$(LIBS)

rhasher_CPPFLAGS=$(DEFS)

gitclean:
	git clean -df;
	rm -rf *.o rhasher
