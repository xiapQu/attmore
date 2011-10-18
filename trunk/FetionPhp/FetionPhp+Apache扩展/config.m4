dnl $Id$
dnl config.m4 for extension libfetion

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(libfetion, for libfetion support,
dnl Make sure that the comment is aligned:
[  --with-libfetion             Include libfetion support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(libfetion, whether to enable libfetion support,
dnl Make sure that the comment is aligned:
dnl [  --enable-libfetion           Enable libfetion support])

if test "$PHP_LIBFETION" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-libfetion -> check with-path
  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  SEARCH_FOR="/include/libfetion/libfetion.h"  # you most likely want to change this
  dnl if test -r $PHP_LIBFETION/$SEARCH_FOR; then # path given as parameter
  dnl   LIBFETION_DIR=$PHP_LIBFETION
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for libfetion files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       LIBFETION_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$LIBFETION_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the libfetion distribution])
  dnl fi

  dnl # --with-libfetion -> add include path
  PHP_ADD_INCLUDE($LIBFETION_DIR/include)

  dnl # --with-libfetion -> check for lib and symbol presence
  LIBNAME=fetion_32 # you may want to change this
  LIBSYMBOL=fx_init # you most likely want to change this 
  FETION_SHARED_LIBADD = " -lfetion_32 -lcurl -lstdc++ "

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl  [
  dnl    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $LIBFETION_DIR/lib, LIBFETION_SHARED_LIBADD)
  dnl    AC_DEFINE(HAVE_LIBFETIONLIB,1,[ ])
  dnl ],[
  dnl    AC_MSG_ERROR([wrong libfetion lib version or lib not found])
  dnl  ],[
  dnl    -L$LIBFETION_DIR/lib -lm
  dnl  ])
  dnl
  dnl PHP_SUBST(LIBFETION_SHARED_LIBADD)
  PHP_REQUIRE_CXX()
  PHP_ADD_LIBRARY(stdc++,"",LIBFETION_SHARED_LIBADD) 
  PHP_ADD_LIBRARY( $LIBNAME ,"",LIBFETION_SHARED_LIBADD) 
  if test -f /usr/lib/libcurl.a ; then
    LIBFETION_SHARED_LIBADD=" $LIBFETION_SHARED_LIBADD /tmp/curl-7.19.6/lib/.libs/libcurl.a "
  else
    PHP_ADD_LIBRARY( curl ,"",LIBFETION_SHARED_LIBADD) 
  fi;
  dnl PHP_SUBST(FETION_SHARED_LIBADD)
  PHP_SUBST(LIBFETION_SHARED_LIBADD) 
  PHP_NEW_EXTENSION(libfetion, libfetion.cpp, $ext_shared)
fi
