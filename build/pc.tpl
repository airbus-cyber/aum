prefix=%PREFIX%
includedir=${prefix}/include
libdir=${prefix}/lib

Name: %NAME%
Description: %DESCRIPTION%
Version: %VERSION%
Requires: %DEPENDS%
Cflags:-I${includedir}
Libs:-L${libdir} -l%NAME%

