FLAGS = -Wall -c -O3
CC = g++
.PHONY: all clean

all: mandelOMP mandel generate_inputs

mandel: mandel.o
	${CC} mandelbrot.o -o mandelbrot.out -pthread

mandelOMP: mandelOMP.o
	${CC} -fopenmp -Wall mandelbrotOMP.o -o mandelbrotOMP.out

matrix.o: 
	${CC} ${FLAGS} matrix.c matrix.h

mandel.o:
	${CC} ${FLAGS} mandelbrot.cpp
	
mandelOMP.o:
	${CC} ${FLAGS} -fopenmp mandelbrotOMP.cpp

generate_inputs:
	python3 input_generator.py

clean_all: clean_out clean_in clean

clean:
	rm *.o *.gch *.out

clean_out:
	cd outputs/; rm *; cd ..

clean_in:
	cd inputs/; rm *; cd ..