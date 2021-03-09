CFLAGS = -g -Wall -Wextra -pedantic

csim: main.o functions.o
	g++ -o $@ main.o functions.o

main.o: main.cpp functions.h
	g++ $(CFLAGS) -c main.cpp

finctions.o: functions.cpp functions.h
	g++ $(CFLAGS) -c functions.cpp

clean:
	rm -f *.o csim *~