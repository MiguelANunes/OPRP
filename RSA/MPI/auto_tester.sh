#!/bin/bash
make clean

make

clear
echo "Começou"

for i in $(seq 8 2 32); do # Gerando chaves
    echo "Gerando chave de $i Bits"
    ./keygen $i
done

for i in $(seq 33 128); do # Gerando chaves
    echo "Gerando chave de $i Bits"
    ./keygen $i
done

export OMP_NUM_THREADS=8
THREADS=`echo $OMP_NUM_THREADS`

for i in $(seq 8 2 32); do
    printf "\n"
    echo "$i Bits"
    mpirun -np 8 --hostfile hosts.txt tester $i $THREADS
done

for i in $(seq 33 128); do
    printf "\n"
    echo "$i Bits"
    mpirun -np 8 --hostfile hosts.txt tester $i $THREADS
done

make clean
