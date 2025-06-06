prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
includedir=${prefix}/@CMAKE_INSTALL_INCLUDEDIR@
libdir=${prefix}/@CMAKE_INSTALL_LIBDIR@

Name: libbsocial
Description: Library for interfacing with BojanSocial
Requires.Private: @LIBBSOCIAL_REQUIRES_PRIVATE@
Version: @LIBBSOCIAL_VERSION_MAJOR@.@LIBBSOCIAL_VERSION_MINOR@
Cflags: -I${includedir}
Libs: -L${libdir} -lbsocial
