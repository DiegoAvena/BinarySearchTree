# A simple Makefile for CPSC 350
# Assumes the following directory hierarchy:
# Assignment X
# 	src
#       include

#this Makefile goes in the src directory

#change this to the correct assignment #
EXECUTABLE := BinarySearchTree

# the source files to be built
SOURCES := *.cpp

#stuff you don't need to worry about
INCLUDES := -I ../include
EXT := exe
CC := g++

#the command given to run an executable
RUNCOMMAND := ./

#compiles the source files into an executable
all:
	$(CC) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE).$(EXT)

#runs the executable
#$(file) will allow the user to pass in a command line argument using make run arg1=the name of the file the user wants to pass in
run:
	$(RUNCOMMAND)$(EXECUTABLE).$(EXT)

#deletes any files that are not a source file
realclean:
	find . -type f -name "*.o" -exec rm '{}' \;
	find . -type f -name "*.exe" -exec rm '{}' \;

# this line required by make - don't delete
