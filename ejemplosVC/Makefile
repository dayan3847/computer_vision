
all:simple ejemplo2 ejemplo3

simple: simple.o
	g++ -Wall -o simple simple.o `pkg-config opencv4 --libs`

simple.o: simple.cpp
	g++ -Wall `pkg-config opencv4 --cflags` -c simple.cpp

ejemplo2: ejemplo2.o
	g++ -Wall -o ejemplo2 ejemplo2.o `pkg-config opencv4 --libs`

ejemplo2.o: ejemplo2.cpp
	g++ -Wall `pkg-config opencv4 --cflags` -c ejemplo2.cpp

ejemplo3: ejemplo3.o
	g++ -Wall -g -o ejemplo3 ejemplo3.o `pkg-config opencv4 --libs`

ejemplo3.o: ejemplo3.cpp
	g++ -Wall -g `pkg-config opencv4 --cflags` -c ejemplo3.cpp

clean:
	rm simple ejemplo2 ejemplo3 *.o
