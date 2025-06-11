prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
includedir=${prefix}/@CMAKE_INSTALL_INCLUDEDIR@
libdir=${prefix}/@CMAKE_INSTALL_LIBDIR@

Name: libbsocial-jansson
Description: Library for interfacing with BojanSocial (cURL backend)
Requires.Private: @LIBBSOCIAL_JANSSON_REQUIRES_PRIVATE@
Version: @LIBBSOCIAL_JANSSON_VERSION_MAJOR@.@LIBBSOCIAL_JANSSON_VERSION_MINOR@
Cflags: -I${includedir}
Libs: -L${libdir} -lbsocial-jansson
