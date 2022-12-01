LDFLAGS = -pthread
FLAGS = -Wall -c
.PHONY: all clean

all: pthreads_matrix_mult mandel mandelFree generate_inputs

pthreads_matrix_mult: matrix.o
	gcc matrix.o pthreads_matrix_mult.c -o pthreads_matrix_mult.out ${LDFLAGS}

mandel: mandel.o
	g++ mandelbrot.o -o mandelbrot.out ${LDFLAGS}

mandelFree: mandelFree.o
	g++ mandelbrotFree.o -o mandelbrotFree.out ${LDFLAGS}

matrix.o: 
	gcc ${FLAGS} matrix.c matrix.h

mandel.o:
	g++ ${FLAGS} mandelbrot.cpp
	
mandelFree.o:
	g++ ${FLAGS} mandelbrotFree.cpp

generate_inputs:
	python3 input_generator.py

clean_all: clean_out clean_in clean

clean:
	rm *.o *.gch *.out

clean_out:
	cd outputs/; rm *; cd ..

clean_in:
	cd inputs/; rm *; cd ..