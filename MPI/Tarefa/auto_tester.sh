#!/bin/bash
make clean

INPUTS="./inputs"
OUTPUTS="./outputs"
make
echo "Começou"
for i in $(seq 0 9); do
    ./mandelbrotOMP.out < "$INPUTS"/"input.in" > "$OUTPUTS"/"mandelbrotOMP$i.txt"
	mpirun -np 6 --hostfile hosts.txt ../exec/mandelbrotMPI.out < "$INPUTS"/"input.in" > "$OUTPUTS"/"mandelbrotMPI$i.txt"
make clean
