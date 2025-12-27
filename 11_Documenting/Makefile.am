SUBDIRS = src po

@DX_RULES@

all-local: doxygen-doc

docs: doxygen-doc

man1_MANS = doxygen-doc/man/man1/guess.c.1

http: doxygen-doc
	python3 -m http.server --directory $</html

gitclean:
	git clean -df;
	rm -rf *.o src/*.o src/guess
