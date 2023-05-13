
all:encuentraUmbral

encuentraUmbral: encuentraUmbral.o histograma.o gaussianIntersection.o
	g++ -Wall -o encuentraUmbral encuentraUmbral.o histograma.o gaussianIntersection.o `pkg-config opencv4 --libs`

encuentraUmbral.o: encuentraUmbral.cpp histograma.h gaussianIntersection.h
	g++ -Wall -DVERBOSE `pkg-config opencv4 --cflags` -c encuentraUmbral.cpp

histograma.o: histograma.cpp histograma.h
	g++ -Wall -DVERBOSE `pkg-config opencv4 --cflags` -c histograma.cpp

gaussianIntersection.o: gaussianIntersection.cpp gaussianIntersection.h
	g++ -Wall -DVERBOSE `pkg-config opencv4 --cflags` -c gaussianIntersection.cpp
clean:
	rm encuentraUmbral *.o
