SSDL, the Simple SDL wrapper library.
Copyright 2020, Will Briggs

This is a simple library designed to work with SDL2, SDL2_image, SDL2_mixer, and SDL2_ttf to make programming with SDL easy for beginners.  3rd-party dll's needed by the above libraries, and thus also needed by SSDL, include

libFLAC, by Josh Coalson and Xiph.org
freetype, by the FreeType Project
libjpeg, by the Independent JPEG Group
modplug, now public domain
mpg123, by Michael Hipp and others
opus and ogg-vorbis libraries, by Xiph.org
libpng16, by Glenn Randers-Pehrson and others
libtiff, by Sam Leffler and Silicon Graphics
libwebp, by Google
zlib, by Jean-loup Gailly and Mark Adler

--

To use with Microsoft Visual Studio, compile the SSDL project if needed, and ensure that <SSDL folder>/include is in your project's include path, and that <SSDL folder>/lib/<architecture> is in your project's library path.  There is no dll.

To use with MinGW, build SSDL with the associated Makefile, and when compiling ensure that <SSDL folder>/include is in your include path and <SSDL folder>/MinGW is in the library path.

To use with Unix, build SSDL with the associated Makefile, and when compiling ensure that <SSDL folder>/include is in your include path and <SSDL folder>/unix is in the library path.

--

Visual Studio and Microsoft are trademarks of the Microsoft Corporation.  All other trademarks referenced herein are property of their respective owners.

This code repository, and its author, are neither affiliated with, nor authorized, sponsored, or approved by, Microsoft Corporation.

--

This library is under the zlib License, see the file "COPYING.SSDL.txt" for details.
