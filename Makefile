all:
	g++ -Wall -pedantic -O0 -g -o main main.cpp

clean:
	shred -uz main *.o
