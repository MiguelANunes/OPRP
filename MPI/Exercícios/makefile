LDFLAGS = -fopenmp
CC = mpicc
.PHONY: all clean

all: mandel

mandel: mandel.o
	${CC} mandelbrot.o -o mandelbrot.out ${LDFLAGS}

mandel.o:
	${CC} mandelbrot.cpp

clean:
	rm *.o *.gch *.out
