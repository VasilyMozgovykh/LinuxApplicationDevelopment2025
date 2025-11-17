AC_INIT([guess], [0.0], [vasily.mozgovykh@yandex.ru])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)

AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])

ALL_LINGUAS="ru"

AC_PROG_CC

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h stdio.h string.h])

AC_CHECK_FUNCS([realpath setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in src/Makefile])
AC_OUTPUT
