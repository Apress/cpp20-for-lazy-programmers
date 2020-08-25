To install SSDL for MinGW, run make in this directory.

It currently makes the static version of the library.  If you want shared, you can move the resulting libssdl.dll to a path where the OS can find it, or edit runw and gdbw scripts to know the path to this folder too. 

static-test tests the library; you can run it to verify that make worked (that is, that the library built and the program runs). Run it thus: bash runw
