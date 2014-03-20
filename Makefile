all:
	g++ -ansi -Wall -pedantic -O0 -g -o main main.cpp

#alt:
#	g++ -Wall -pedantic -O0 -g -o alt alt.cpp

clean:
	shred -uz main
# shred -uz main *.o
#	shred -uz main alt *.o
