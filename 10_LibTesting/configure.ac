AC_PREREQ([2.69])
AC_INIT([Growable buf test cases], [0.0], [vasily.mozgovykh@yandex.ru], [buf])
AM_INIT_AUTOMAKE([foreign])

LT_INIT([disable-static])
AC_CONFIG_SRCDIR([src/buf.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

PKG_CHECK_MODULES([CHECK],[check])

AC_SUBST(CHECK_CFLAGS)
AC_SUBST(CHECK_LIBS)

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    tests/Makefile
])

AC_OUTPUT
