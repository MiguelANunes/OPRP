#!/bin/bash
make clean

INPUTS="./inputs"
OUTPUTS="./outputs"
make
mv *.out ../exec
scp /home/miguel/Documents/Matérias/OPRP/MPI/Tarefa/exec/* Curry:/home/miguel/Documents/Matérias/OPRP/MPI/Tarefa/exec/
scp /home/miguel/Documents/Matérias/OPRP/MPI/Tarefa/exec/* Lambek:/home/miguel/Documents/Matérias/OPRP/MPI/Tarefa/exec/
echo "Começou"
for i in $(seq 0 9); do
#    ./../exec/mandelbrotOMP.out < "$INPUTS"/"input.in" > "$OUTPUTS"/"mandelbrotOMP$i.txt"
	mpirun -np 1 --hostfile hosts.txt /home/miguel/Documents/Matérias/OPRP/MPI/Tarefa/exec/mandelbrotMPI.out < "$INPUTS"/"input.in" > "$OUTPUTS"/"mandelbrotMPI$i.txt"
done
make clean
