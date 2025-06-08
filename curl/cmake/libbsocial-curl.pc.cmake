prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
includedir=${prefix}/@CMAKE_INSTALL_INCLUDEDIR@
libdir=${prefix}/@CMAKE_INSTALL_LIBDIR@

Name: libbsocial-curl
Description: Library for interfacing with BojanSocial (cURL backend)
Requires.Private: @LIBBSOCIAL_CURL_REQUIRES_PRIVATE@
Version: @LIBBSOCIAL_CURL_VERSION_MAJOR@.@LIBBSOCIAL_CURL_VERSION_MINOR@
Cflags: -I${includedir}
Libs: -L${libdir} -lbsocial-curl
