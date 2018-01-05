#Mark Kelly C00198041 02/10/2017

EXE = mySfml
CC = g++
CFLAGS = -std=c++11 -pthread -I.
CFILES = main.o

#g++ main.cpp -lsfml-window -lsfml-graphics -lsfml-system



#g++ -c main.cpp -I<sfml-install-path>/include

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
		$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)



SFML: SFML = -lsfml-graphics -lsfml-window -lsfml-system
SFML: ALL

ALL: $(CFILES)
		$(CC) $(CFLAGS) main.cpp -o $(EXE) $(SFML) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
