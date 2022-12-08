CC = g++   # compilador 
FLAGS = -O3 -Wall -c

all: link_keys link_teste

run: 
	./main $(BITS) $(ARQ) 
# uso: make run BITS=<total de bits> ARQ=<nome_arquivo_sem_extensão>
# usar estritamente nesta ordem
# ou seja, temos os seguinte comandos validos 
# 	make run BITS=x ARQ=nome_arquivo
# 	make run BITS=x
# 	make run 

run_teste:
	./tester $(BITS)

generate_keys: link_keys
	./keygen $(BITS)

link: main
	${CC} -o main chaves.o cripto.o bruta.o main.o -lgmpxx -lgmp

link_teste: tester
	mpic++ -fopenmp -Wall -o tester chaves.o bruta.o tester.o -lgmpxx -lgmp

link_keys: keygen chaves
	${CC} -o keygen chaves.o keygen.o -lgmpxx -lgmp

main: chaves cripto bruta main.cpp
	${CC} ${FLAGS} main.cpp

tester: chaves bruta tester.cpp
	mpic++ ${FLAGS} -fopenmp tester.cpp

keygen:
	${CC} ${FLAGS} keygen.cpp

chaves:
	${CC} ${FLAGS} chaves.cpp  

cripto:
	${CC} ${FLAGS} cripto.cpp 

bruta:
	mpic++ ${FLAGS} bruta.cpp

clean:
	rm *.o keygen tester keys/*
 
