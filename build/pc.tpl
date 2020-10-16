prefix=%CONFIG_PREFIX%
includedir=%CONFIG_PREFIX%/include
libdir=%CONFIG_LIBDIR%

Name: %NAME%
Description: %DESCRIPTION%
Version: %VERSION%
Requires: %DEPENDS%
Cflags:-I${includedir}
Libs:-L${libdir} -l%NAME%

