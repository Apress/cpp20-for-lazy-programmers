# A makefile that should work for any SSDL projects
# Adapt as needed
#  -- from the SSDL (Simple SDL) library, but no copyright is claimed

INCLUDE_FLAGS	= `sdl2-config --cflags` -I../../../include #-I../../../external/SDL2/include

	#What are our source files, and where are they?
C_SOURCES 	= $(wildcard ../../../src/*.c)
CPP_SOURCES	= $(wildcard ../../../src/*.cpp)
CC_SOURCES 	= $(wildcard ../../../src/*.cc)

	#So what are our object files, and where are they?
C_OBJECTS 	= $(notdir ${C_SOURCES  :.c=  .o})
CPP_OBJECTS	= $(notdir ${CPP_SOURCES:.cpp=.o})
CC_OBJECTS 	= $(notdir ${CC_SOURCES :.cc= .o})
OBJECTS 	= $(notdir $(C_OBJECTS) $(CPP_OBJECTS) $(CC_OBJECTS))

##################################################################

all: 	$(OBJECTS)

.PHONY: all clean showvars

showvars:
	@ echo	$(C_SOURCES) "-->" $(CPP_OBJECTS) "-->" $(OBJECTS)
	
clean:
	@ rm -f *.o

$(C_OBJECTS): %.o : 	../../../src/%.c
	g++ -c -fPIC $(INCLUDE_FLAGS) $< -o $@

$(CC_OBJECTS): %.o : 	../../../src/%.cc
	g++ -c -fPIC $(INCLUDE_FLAGS) $< -o $@

$(CPP_OBJECTS): %.o : 	../../../src/%.cpp
	g++ -c -fPIC $(INCLUDE_FLAGS) $< -o $@


