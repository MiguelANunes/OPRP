LDFLAGS = -pthread
FLAGS = -Wall -c
.PHONY: all clean

all: pthreads_matrix_mult mandel generate_inputs

pthreads_matrix_mult: matrix.o
	gcc matrix.o pthreads_matrix_mult.c -o pthreads_matrix_mult.out ${LDFLAGS}

mandel: mandel.o
	g++ mandelbrot.o -o mandelbrot.out ${LDFLAGS}

matrix.o: 
	gcc ${FLAGS} matrix.c matrix.h

mandel.o:
	g++ ${FLAGS} mandelbrot.cpp

generate_inputs:
	python3 input_generator.py

clean_all: clean_out clean_in clean

clean:
	rm *.o *.gch *.out

clean_out:
	cd outputs/; rm *; cd ..

clean_in:
	cd inputs/; rm *; cd ..

# https://opensource.com/article/18/8/what-how-makefile
# https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html#Overall-Options
# https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf
# http://story-of-a-programmer.blogspot.com/2015/04/makefile-tutorial.html <- Melhor
# https://stackoverflow.com/questions/15440183/makefile-include-header

# https://github.com/MiguelANunes/Trabalho-Final-CAL/blob/master/makefile
# https://github.com/MiguelANunes/Trabalho-Final-REC/blob/master/Algoritmos/makefile
# https://github.com/MiguelANunes/Trabalhos-CGR/blob/master/Complementar%202/makefile