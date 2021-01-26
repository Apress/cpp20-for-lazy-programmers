# A makefile that should work for any SSDL projects
# Adapt as needed
#  -- from the SSDL (Simple SDL) library, but no copyright is claimed

INCLUDE_FLAGS	= 	-I..\..\SDL2-MinGW\SDL2\i686-w64-mingw32\include\SDL2		\
					-I..\..\SDL2-MinGW\SDL2_image\i686-w64-mingw32\include\SDL2	\
					-I..\..\SDL2-MinGW\SDL2_mixer\i686-w64-mingw32\include\SDL2	\
					-I..\..\SDL2-MinGW\SDL2_ttf\i686-w64-mingw32\include\SDL2	\
					-I..\include 						#...and SSDL's includes		

	#What are our source files, and where are they?
C_SOURCES 	= $(wildcard ../src/*.c)
CPP_SOURCES	= $(wildcard ../src/*.cpp)
CC_SOURCES 	= $(wildcard ../src/*.cc)

	#So what are our object files, and where are they?
C_OBJECTS 		= ${C_SOURCES:  .c  =.o}
CPP_OBJECTS		= ${CPP_SOURCES:.cpp=.o}
CC_OBJECTS 		= ${CC_SOURCES: .cc =.o}
OBJECTS1 		= $(notdir $(C_OBJECTS) $(CPP_OBJECTS) $(CC_OBJECTS))
STATIC_OBJECTS 	= ${OBJECTS1:%=bin/static/%}

#############################################################################

all:  	static libssdl.a static-test.exe 
		 
.PHONY: all clean showvars static 

static:
		$(MAKE) -C bin/static

showvars:		
	@ echo	$(C_SOURCES) $(CPP_SOURCES) $(CC_SOURCES) cause $(STATIC_OBJECTS) 

clean:
	rm -f bin/static/*.o *.o 
	rm -f static-test  	

# MinGW, if it's shared not static, needs to have a .dll extension, not .so.  
# Or another page 
# See http://gernotklingler.com/blog/creating-using-shared-libraries-different-compilers-different-operating-systems/ says do something stranger so it will work with non-MinGW programs. 

# It is VERY IMPORTANT that testSSDL come first, then SSDL, then SDL2_*.  If not
#  the link will almost certainly fail.
# If something goes wrong and we get undefined references, try the second version.  It is expected
#  to take longer, but does seem to make g++'s linker ld resolve those references.  Note that
#  -Wl,--start-group and -Wl,--end-group must each have no space after the comma.
static-test.exe:	testSSDL.o libssdl.a
	g++ testSSDL.o -lmingw32 -lssdl -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -L. -o static-test.exe
#	g++ testSSDL.o -Wl,--start-group -lmingw32 -lssdl -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wl,--end-group -Lbin/static -o static-test.exe
				
testSSDL.o:					 ../test/testSSDL.cpp
	g++ -c  $(INCLUDE_FLAGS) ../test/testSSDL.cpp      -o testSSDL.o

libssdl.a:					$(STATIC_OBJECTS)
	ar rcs libssdl.a 		$(STATIC_OBJECTS)




