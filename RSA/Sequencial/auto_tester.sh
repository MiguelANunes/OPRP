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

for i in $(seq 8 2 32); do # Teste Sequencial
    printf "\n"
    echo "$i Bits"
    ./tester $i 
done

for i in $(seq 33 128); do # Teste Sequencial
    printf "\n"
    echo "$i Bits"
    ./tester $i 
done

make clean