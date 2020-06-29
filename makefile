#especify target
trgt:= TrainNoiseWireMap
#especify output directory
otdr:= cmpltd/
#compiler
cc:= g++
#compiler flags
cflgs:= -fconcepts-ts
#include
incld:= -Iincld
#libs
libs:= -lSDL2 -lGLU -lGL
all: $(trgt).cpp
	$(cc) $(trgt).cpp $(cflgs) $(incld) $(libs) -o $(otdr)$(trgt)
