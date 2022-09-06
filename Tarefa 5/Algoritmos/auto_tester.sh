#!/bin/bash
make clean_all

INPUTS="./inputs"
OUTPUTS="./outputs"
make
echo "Começou"
for i in $(seq 0 9); do
    for j in $(seq 1 8); do
        ./mandelbrot.out < "$INPUTS"/"mandelbrot$j.in" > "$OUTPUTS"/"mandelbrot$i$j.txt"
        ./pthreads_matrix_mult.out < "$INPUTS"/"matrix$j.in" > "$OUTPUTS"/"matrix$i$j.txt"
        ./mandelbrotFree.out < "$INPUTS"/"mandelbrot$j.in" > "$OUTPUTS"/"mandelbrotFree$i$j.txt"
    done
done
make clean
