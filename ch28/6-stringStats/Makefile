# A makefile that should work for any C and C++ projects requiring no special libraries
# Adapt as needed
#  -- from _C++20 for Lazy Programmers_, but I claim no copyright

EXECUTABLE	= a.out	#Yes, call it this and it should run, even in MinGW

C_SOURCES	= $(wildcard *.c)
CPP_SOURCES	= $(wildcard *.cpp)
CC_SOURCES	= $(wildcard *.cc)

C_OBJECTS	= ${C_SOURCES:.c=.o}
CPP_OBJECTS	= ${CPP_SOURCES:.cpp=.o}
CC_OBJECTS	= ${CC_SOURCES:.cc=.o}
ALL_OBJECTS	= $(C_OBJECTS) $(CPP_OBJECTS) $(CC_OBJECTS)

ALL_DEPENDENCIES = $(ALL_OBJECTS:.o=.dep)

##########################################################

all: $(EXECUTABLE)

$(EXECUTABLE): $(ALL_OBJECTS)
		g++ -o $@ -g $^
		@ # -g means: 	 support debugging
		@ # $^ means:  	 use all the objects
		@ # -o $@ means: let the output be called $(EXECUTABLE)

clean:
		rm -f $(EXECUTABLE)
		rm -f *.o
		rm -f *.dep
		rm -f core
		rm -f *.ncb *.sdf
		rm -r -f Debug Release .vs

########### How to compile .o, and .dep, files ##########

%.o: 	%.cpp
		g++ -g -o $@ -c $<
		@ # $< means "the next object right of the : (a .cpp file)"

%.o: 	%.cc
		g++ -g -o $@ -c $<

%.o: 	%.c
		gcc -g -o $@ -c $<

%.dep: 	%.cpp 
		g++ -MM -MT "$*.o $@" $< > $@
		@ # -MM means:	let output be a dependency rule listing headers
		@ # -MT means:	the left side of the rule (see below) is
		@ #				the pattern specified
		@ #				not system headers, just ours
		@ # > $@     	puts output in the .dep file

################# Explanation: ############################
#g++/gcc -MM produces a pattern like so:
#       main.o: main.cc include1.h include2.h
#  listing the .o file and all it depends on. We also want the .dep file
#  to depend on itself:
#       main.o main.dep: main.cc include1.h include2.h
#  so if an include changes, main.dep will have to update itself
#  Otherwise if you alter include1.h, say, you rebuild the .o but not the .dep
#     and if include1.h now includes some other file, we needed to add that
#  Now it will
##########################################################

%.dep: 	%.cc
		g++ -MM -MT "$*.o $@" $< > $@

%.dep: 	%.c 
		gcc -MM -MT "$*.o $@" $< > $@

ifneq ($(MAKECMDGOALS),clean) # If not cleaning up...
-include $(ALL_DEPENDENCIES)
endif
		#This says: include all those .dep files you made
		#  as if they were part of the Makefile
		#The - at the start says "don't gripe if none are found
		#  (we'll be building them anyway)"
		#...but only if it's not "make clean"
		#  because we don't want to rebuild dep's just to erase them

