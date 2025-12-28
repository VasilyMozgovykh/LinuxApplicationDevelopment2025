SUBDIRS = src po

@DX_RULES@

all-local: doxygen-doc

docs: doxygen-doc

doxygen-doc/man/man1/guess.1: doxygen-doc
	help2man -N ./src/guess > $@

man1_MANS = doxygen-doc/man/man1/guess.1

http: doxygen-doc
	python3 -m http.server --directory $</html

gitclean:
	git clean -df;
	rm -rf *.o src/*.o src/guess
