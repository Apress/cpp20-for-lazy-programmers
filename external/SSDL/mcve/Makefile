# A makefile that should work for any SSDL projects running on Unix
# Adapt as needed
#  -- from _C++20 for Lazy Programmers_, but I claim no copyright

EXECUTABLE	= a.out			

	#What are our source files, and where are they?
	# All .c, .cpp, and .cc files
C_SOURCES 	= $(wildcard *.c)
CPP_SOURCES	= $(wildcard *.cpp)
CC_SOURCES 	= $(wildcard *.cc)

	#So what are our object files, and where are they?
	# Anything we can make with those source files
C_OBJECTS 	= ${C_SOURCES:  .c  =.o}
CPP_OBJECTS	= ${CPP_SOURCES:.cpp=.o}
CC_OBJECTS 	= ${CC_SOURCES: .cc =.o}
ALL_OBJECTS	= $(notdir $(C_OBJECTS) $(CPP_OBJECTS) $(CC_OBJECTS))

	#Tell g++ where to find include files for SDL2, SSDL
INCLUDE_FLAGS	= `sdl2-config --cflags` \
	          -I../../external/fmt-master/include

LANGUAGE_FLAGS	= -std=gnu++2a	#Specify language standard: C++20

        #Tell g++ where to find library files for SDL2, SSDL
LIBRARIES	= SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer
LIBRARY_DIRS	= ../../external/SSDL/unix
LIB_FLAGS	= $(foreach library,$(LIBRARIES),    -l$(library))
LIB_DIR_FLAGS   = $(foreach libdir, $(LIBRARY_DIRS), -L$(libdir))

ALL_FLAGS   	= $(LANGUAGE_FLAGS) $(INCLUDE_FLAGS) $(LIB_FLAGS) $(LIB_DIR_FLAGS)

##########################################################################

all: $(EXECUTABLE)

.PHONY: all clean showvars 

showvars:  
	@ echo $(CPP_SOURCES) "-->" $(CPP_OBJECTS)
	@ echo ALL_FLAGS  $(ALL_FLAGS)
	
$(EXECUTABLE): $(ALL_OBJECTS)
#	@ echo 'ALL_FLAGS :' $(ALL_FLAGS)
	g++ -o $@ -g $^ $(ALL_FLAGS) 
#	@ # -g means: 	 support debugging
#	@ # $^ means:  	 use all the objects
#	@ # -o $@ means: let the output be called $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
	rm -f $(ALL_OBJECTS)
	rm -f core
	rm -f *.ncb *.sdf
	rm -r -f Debug Release .vs Backup	

$(C_OBJECTS): %.o : 	%.c
	g++ -c -g $(LANGUAGE_FLAGS) $(INCLUDE_FLAGS) $< -o $@

$(CC_OBJECTS): %.o : 	%.cc
	g++ -c -g $(LANGUAGE_FLAGS) $(INCLUDE_FLAGS) $< -o $@

$(CPP_OBJECTS): %.o : 	%.cpp
	g++ -c -g $(LANGUAGE_FLAGS) $(INCLUDE_FLAGS) $< -o $@
