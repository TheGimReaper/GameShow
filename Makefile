CFLAGS = -std=c++14 -g 

all: Program2

run: Program2
	./Program2

Program2: Program2.o Priority_Queue.o Contestant.o
	g++ $(CFLAGS) Program2.o Priority_Queue.o Contestant.o -o Program2

Program2.o : Priority_Queue.o Contestant.o Program2.cpp
	g++ -c $(CFLAGS) Program2.cpp -o Program2.o 

Priority_Queue.o: Priority_Queue.h Priority_Queue.cpp Contestant.o
	g++ -c $(CFLAGS) Priority_Queue.cpp -o Priority_Queue.o 

Contestant.o: Contestant.h Contestant.cpp
	g++ -c $(CFLAGS) Contestant.cpp -o  Contestant.o

clean:
	rm -vf *.o Program2