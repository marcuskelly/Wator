#Mark Kelly C00198041 02/10/2017

EXE = mySfml
CC = g++
CFLAGS = -std=c++11 -pthread -I.
CFILES = main.o

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

SFML: SFML = -lsfml-graphics -lsfml-window -lsfml-system
SFML: ALL

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

ALL: $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(EXE) $(SFML) $(DEBUGFLAGS)

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
