
all:ej1

ej1: ej1.o
	g++ -Wall -o ej1 ej1.o `pkg-config opencv4 --libs`

ej1.o: ej1.cpp
	g++ -Wall `pkg-config opencv4 --cflags` -c ej1.cpp

clean:
	rm ej1 *.o
