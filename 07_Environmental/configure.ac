AC_INIT([rhasher], [0.0], [vasily.mozgovykh@yandex.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_PROG_CC

AC_CHECK_LIB(
    [rhash],
    [rhash_init],
    [],
    [
        AC_MSG_ERROR([Required dependency 'librhash' is not installed])
    ]
)
AC_CHECK_HEADER([rhash.h])

AC_ARG_ENABLE(
    [readline],
    [
        AS_HELP_STRING(
            [--enable-readline],
            [Override getline with readline]
        )
    ],
    [readline_override=yes],
    [readline_override=no]
)

AS_IF(
    [test "x$readline_override" = "xyes"],
    [
        AC_CHECK_LIB(
            [readline],
            [readline],
            [
                AC_DEFINE([READLINE_OVERRIDE], ["TRUE"], [This overrides getline])
                LIBS="$LIBS -lreadline"
            ],
            []
        )
    ]
)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
