#!/bin/bash
make clean

INPUTS="./inputs"
OUTPUTS="./outputs"
make
mv *.out exec
echo "Começou"
for i in $(seq 0 9); do
#    ./../exec/mandelbrotOMP.out < "$INPUTS"/"input.in" > "$OUTPUTS"/"mandelbrotOMP$i.txt"
	mpirun -np 1 --hostfile test.txt exec/mandelbrotMPI.out < "$INPUTS"/"input.in" > "$OUTPUTS"/"mandelbrotMPI$i.txt"
done
make clean
