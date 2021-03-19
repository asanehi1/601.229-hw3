#
# CSF Assignment 3 Makefile
#

EXES = csim tests main.o functions.o 

CFLAGS = -g -Wall -Wextra -pedantic

all: $(EXES)

csim: main.o functions.o
	g++ -o $@ main.o functions.o

#tests: tests.o
#	g++ -o $@ tests.o

main.o: main.cpp functions.h
	g++ $(CFLAGS) -c main.cpp

finctions.o: functions.cpp functions.h
	g++ $(CFLAGS) -c functions.cpp

clean:
	rm -f *.o csim *~
