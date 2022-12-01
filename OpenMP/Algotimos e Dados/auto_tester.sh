#!/bin/bash
make clean_all

INPUTS="./inputs"
OUTPUTS="./outputs"
make
echo "Começou"
for i in $(seq 0 9); do
    for j in $(seq 1 8); do
        export OMP_SCHEDULE="static"
        ./mandelbrotOMP.out < "$INPUTS"/"mandelbrot$j.in" > "$OUTPUTS"/"mandelbrotOMPStatic$i$j.txt"
        export OMP_SCHEDULE="dynamic"
        ./mandelbrotOMP.out < "$INPUTS"/"mandelbrot$j.in" > "$OUTPUTS"/"mandelbrotOMPDynamic$i$j.txt"
        export OMP_SCHEDULE="guided"
        ./mandelbrotOMP.out < "$INPUTS"/"mandelbrot$j.in" > "$OUTPUTS"/"mandelbrotOMPGuided$i$j.txt"
    done
done
make clean