#                                               -*- Autoconf -*-
# Process this file preferable with autoreconf -i to produce a configure script.



define(AC_FUX_NAME, fusekit)
define(AC_FUX_MAJOR_VERSION, 0)
define(AC_FUX_MINOR_VERSION, 6)
define(AC_FUX_MICRO_VERSION, 5)
define(AC_FUX_VERSION, AC_FUX_MAJOR_VERSION.AC_FUX_MINOR_VERSION.AC_FUX_MICRO_VERSION)

AC_INIT(AC_FUX_NAME,AC_FUX_VERSION)
AC_PREREQ(2.61)
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])


AC_MSG_CHECKING([whether to build debug variant])
AC_ARG_ENABLE(debug,
	AC_HELP_STRING(
		[--enable-debug],
		[set debug compile flags [default=no]]
		),
	[],
	[enable_debug="no"]
)
AC_MSG_RESULT([$enable_debug])

if test "$enable_debug" = "yes"; then
   CXXFLAGS="$CXXFLAGS -g -DDEBUG"
fi

PKG_CHECK_MODULES(FUSE, fuse >= 2.4.0)
AC_SUBST(FUSE_CFLAGS)
AC_SUBST(FUSE_LIBS)

LIBS="$LIBS $FUSE_LIBS"
CPPFLAGS="$CPPFLAGS $FUSE_CFLAGS"

AC_MSG_CHECKING([which fuse interface version to use])
AC_ARG_WITH(fuse-version,
	AC_HELP_STRING(
		[--with-fuse-version],
		[specify the fuse interface version [default=27]]
		),
	[],
	[with_fuse_version="27"]
)
AC_MSG_RESULT([$with_fuse_version])
CPPFLAGS="$CPPFLAGS -DFUSE_USE_VERSION=$with_fuse_version"

AC_MSG_CHECKING([whether to use boost tr1 implementation])
AC_ARG_WITH(boost-tr1,
	AC_HELP_STRING(
		[--with-boost-tr1],
		[specify the path to boost if you want to use boost tr1 implementation [default=no]]
		),
	[],
	[with_boost_tr1="no"]
)
AC_MSG_RESULT([$with_boost_tr1])

if test "$with_boost_tr1" != "no"; then
   CPPFLAGS="$CPPFLAGS -I$with_boost_tr1/boost/tr1 -I$with_boost_tr1"	
fi


AC_PROG_CXX
AM_SANITY_CHECK

AC_LANG([C++])

# Checks for std header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h string.h unistd.h])
AC_CHECK_HEADERS([tr1/unordered_map])
AC_CHECK_HEADERS([tr1/functional])



# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_STAT
AC_CHECK_FUNCS([memset])

AX_CREATE_PKGCONFIG_INFO

# Config files to create after running configure
AC_CONFIG_FILES([Makefile
		include/Makefile
		example/Makefile])

AC_OUTPUT
