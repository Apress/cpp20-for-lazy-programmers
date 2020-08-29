# A makefile that should work for any SSDL projects
# Adapt as needed
#  -- from the SSDL (Simple SDL) library, but no copyright is claimed

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
SHARED_OBJS		= ${OBJS1:%=bin/shared/%}

#############################################################################

all:  	shared a.out 
		 
.PHONY: shared all clean showvars 

showvars:		
		@ echo	$(C_SRCS) $(CPP_SRCS) $(CC_SRCS) cause $(STATIC_OBJS) and $(SHARED_OBJS)

clean:
		rm -f bin/shared/*.o *.o 
		rm -f a.out	

shared:
		$(MAKE) -C bin/shared
		
a.out:	shared testSSDL.o $(SHARED_OBJS)
	g++ -g `sdl2-config --cflags --libs` testSSDL.o $(SHARED_OBJS) -lSDL2_image -lSDL2_mixer -lSDL2_ttf -L. 
			
testSSDL.o:	../test/testSSDL.cpp
	g++ -c -g  $(INCLUDE_FLAGS) ../test/testSSDL.cpp      -o testSSDL.o





