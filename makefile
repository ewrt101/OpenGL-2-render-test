#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall
OTHER = -lm -lGL -lGLU -lglut

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: main

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
main:  main.o Vector3.o Color.o Wall_border.o Plane.o TextureLoader.o MeshLoader.o
	$(CC) $(CFLAGS) -o main main.o Vector3.o Color.o Wall_border.o Plane.o TextureLoader.o MeshLoader.o $(OTHER)

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
main.o:  main.cpp BUILD_ORDER.h
	$(CC) $(CFLAGS) -c main.cpp $(OTHER)

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#


Vector3.o:  Vector3.cpp Vector3.h 
	$(CC) $(CFLAGS) -c Vector3.cpp $(OTHER)

Color.o:  Color.cpp Color.h 
	$(CC) $(CFLAGS) -c Color.cpp $(OTHER)

TextureLoader.o:  TextureLoader.cpp TextureLoader.h 
	$(CC) $(CFLAGS) -c TextureLoader.cpp $(OTHER)

Wall_border.o:  Wall_border.cpp Wall_border.h 
	$(CC) $(CFLAGS) -c Wall_border.cpp $(OTHER)

Plane.o:  Plane.cpp Plane.h 
	$(CC) $(CFLAGS) -c Plane.cpp $(OTHER)

MeshLoader.o:  MeshLoader.cpp MeshLoader.h
	$(CC) $(CFLAGS) -c MeshLoader.cpp $(OTHER)


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) count *.o *~