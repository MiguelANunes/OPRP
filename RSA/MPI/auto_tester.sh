#!/bin/bash
make clean

make
echo "Começou"

for i in $(seq 8 2 64); do # Gerando chaves
    ./keygen $i
done

for i in $(seq 8 2 32); do # Teste Sequencial
    echo "$i Bits"
    ./tester $i 
done

make clean