# Authors:  Mark Kelly, Ronan Timmons
# Date:     27 December 2017
# License:  GNU General Public License v3.0
# Brief:    4th Year Wator simulation Project

TARGET_EXEC = start
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
	$(CC) $(CFLAGS) $(CFILES) Cell.cpp -o $(TARGET_EXEC) $(SFML) $(DEBUGFLAGS)

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
