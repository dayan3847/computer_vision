all: dMahalanobis.o ejemploCIE-Lab

CXXFLAGS = -Wall -g -I ../include

dMahalanobis.o: dMahalanobis.cpp
	g++ $(CXXFLAGS) -c dMahalanobis.cpp `pkg-config opencv4 --cflags`

ejemploCIE-Lab.o: ejemploCIE-Lab.cpp
	g++ $(CXXFLAGS) -c ejemploCIE-Lab.cpp `pkg-config opencv4 --cflags`

ejemploCIE-Lab: ejemploCIE-Lab.o
	g++ $(CXXFLAGS) -o ejemploCIE-Lab ejemploCIE-Lab.o `pkg-config opencv4 --libs`

clean:
	rm *.o
	rm ejemploCIE-Lab
