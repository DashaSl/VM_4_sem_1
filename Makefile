all: MyProg

MyProg: main.o 
	g++ main.o -o MyProg
main.o: main.cpp functions.h
	g++ -c main.cpp
clean:
	rm -rf *.o

