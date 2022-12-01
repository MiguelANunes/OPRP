CC = g++   # compilador 
FLAGS = -Wall -c

all: link link_keys link_seq

run: 
	./main $(BITS) $(ARQ) 
# uso: make run BITS=<total de bits> ARQ=<nome_arquivo_sem_extensão>
# usar estritamente nesta ordem
# ou seja, temos os seguinte comandos validos 
# 	make run BITS=x ARQ=nome_arquivo
# 	make run BITS=x
# 	make run 

run_seq:
	./tester $(BITS)

generate_keys: link_keys
	./keygen $(BITS)

link: main
	${CC} -o main chaves.o cripto.o bruta.o main.o -lgmpxx -lgmp

link_seq: sequencial
	${CC} -o tester chaves.o bruta.o tester.o -lgmpxx -lgmp

link_keys: keygen chaves
	${CC} -o keygen chaves.o keygen.o -lgmpxx -lgmp

main: chaves cripto bruta main.cpp
	${CC} ${FLAGS} main.cpp

sequencial: chaves bruta tester.cpp
	${CC} ${FLAGS} tester.cpp

keygen:
	${CC} ${FLAGS} keygen.cpp

chaves:
	${CC} ${FLAGS} chaves.cpp  

cripto:
	${CC} ${FLAGS} cripto.cpp 

bruta:
	${CC} ${FLAGS} bruta.cpp

clean:
	rm *.o main keygen tester CRIPTO* DECRIPTO*
 
