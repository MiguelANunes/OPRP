FLAGS = -Wall -c -O3
CC = g++
.PHONY: all clean

all: mandelMPI mandelOMP

mandelOMP: mandelOMP.o
	${CC} -fopenmp -Wall mandelbrotOMP.o -o mandelbrotOMP.out

mandelOMP.o:
	${CC} ${FLAGS} -fopenmp mandelbrotOMP.cpp

mandelMPI: mandelMPI.o
	mpic++ -Wall mandelbrotMPI.o -o mandelbrotMPI.out

mandelMPI.o:
	mpic++ ${FLAGS} mandelbrotMPI.cpp

clean:
	rm *.o *.gch *.out
