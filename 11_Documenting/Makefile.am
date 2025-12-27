SUBDIRS = src po

@DX_RULES@

docs:	doxygen-doc

http:	doxygen-doc
	python3 -m http.server --directory $</html

gitclean:
	git clean -df;
	rm -rf *.o src/*.o src/guess
