# https://opensource.com/article/18/8/what-how-makefile
# https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html#Overall-Options
# https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf
# http://story-of-a-programmer.blogspot.com/2015/04/makefile-tutorial.html <- Melhor


CC = g++   # compilador 
FLAGS = -Wall -c

all: link # mudar

run: 
	./main $(BITS) $(ARQ) 
# https://stackoverflow.com/questions/2214575/passing-arguments-to-make-run
# uso: make run BITS=<total de bits> ARQ=<nome_arquivo_sem_extensão>
# usar estritamente nesta ordem
# ou seja, temos os seguinte comandos validos 
# 	make run BITS=x ARQ=nome_arquivo
# 	make run BITS=x
# 	make run 

link: main
	${CC} -o main chaves.o cripto.o bruta.o main.o -lgmpxx -lgmp

main: chaves cripto bruta  main.cpp
	${CC} ${FLAGS} main.cpp

chaves:
	${CC} ${FLAGS} chaves.cpp  

cripto:
	${CC} ${FLAGS} cripto.cpp 

bruta:
	${CC} ${FLAGS} bruta.cpp

clean:
	rm *.o main CRIPTO* DECRIPTO*
 
