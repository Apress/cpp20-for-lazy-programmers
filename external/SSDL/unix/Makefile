# A makefile that should work for any SSDL projects
# Adapt as needed
#  -- from the SSDL (Simple SDL) library, but no copyright is claimed

#If you decide to use static not shared libraries:
# take shared libssdl.so shared-test out of the "all" line
# put static libssdl.a static-test in
INCLUDE_FLAGS	= `sdl2-config --cflags` -I../include 

	#What are our source files, and where are they?
C_SRCS 	= $(wildcard ../src/*.c)
CPP_SRCS= $(wildcard ../src/*.cpp)
CC_SRCS = $(wildcard ../src/*.cc)

	#So what are our object files, and where are they?
C_OBJS 			= ${C_SRCS:  .c  =.o}
CPP_OBJS		= ${CPP_SRCS:.cpp=.o}
CC_OBJS 		= ${CC_SRCS: .cc =.o}
OBJS1 			= $(notdir $(C_OBJS) $(CPP_OBJS) $(CC_OBJS))
STATIC_OBJS 	= ${OBJS1:%=bin/static/%}
SHARED_OBJS		= ${OBJS1:%=bin/shared/%}

#############################################################################

all:  	shared libssdl.so shared-test #static libssdl.a static-test 
		 
.PHONY: all clean showvars static shared

static:
		$(MAKE) -C bin/static
shared:
		$(MAKE) -C bin/shared

showvars:		
	@ echo	$(C_SRCS) $(CPP_SRCS) $(CC_SRCS) cause $(STATIC_OBJS) and $(SHARED_OBJS)

clean:
	rm -f bin/static/*.o bin/shared/*.o *.o 
	rm -f static-test shared-test 	

# It is VERY IMPORTANT that testSSDL come first, then SSDL, then SDL2_*.  If not
#  the link will almost certainly fail.
# If something goes wrong and we get undefined references, try the second version.  It is expected
#  to take longer, but does seem to make g++'s linker ld resolve those references.  Note that
#  -Wl,--start-group and -Wl,--end-group must each have no space after the comma.
static-test:	testSSDL.o libssdl.a
	g++ `sdl2-config --cflags --libs` testSSDL.o -lssdl -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -L. -o static-test
#	g++ `sdl2-config --cflags --libs` testSSDL.o -Wl,--start-group -lssdl -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wl,--end-group -L. -o static-test
shared-test:	testSSDL.o libssdl.so  
	g++ `sdl2-config --cflags --libs` testSSDL.o -lssdl -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -L. -o shared-test
#	g++ `sdl2-config --cflags --libs` testSSDL.o -Wl,--start-group -lssdl -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wl,--end-group -L. -o shared-test
				
testSSDL.o:					 ../test/testSSDL.cpp
	g++ -c  $(INCLUDE_FLAGS) ../test/testSSDL.cpp      -o testSSDL.o

libssdl.a:	static			$(STATIC_OBJS)
	ar rcs libssdl.a 		$(STATIC_OBJS)
libssdl.so:	shared			$(SHARED_OBJS)
	g++ -shared 			$(SHARED_OBJS) -o libssdl.so





