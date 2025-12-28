bin_PROGRAMS = guess
guess_SOURCES = guess.c
guess_LDADD = libroman_converter.la

lib_LTLIBRARIES = libroman_converter.la
libroman_converter_la_SOURCES = roman_converter.c roman_converter.h
libroman_converter_la_LDFLAGS = -version-info 1:0:0

AM_CFLAGS=-D'LOCALE_PATH="$(localedir)"'
