CFLAGS = -g -Wall -Wextra -pedantic -std=gnu11

csim: main.o
	g++ -o $@ main.o

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

clean:
	rm -f *.o csim *~