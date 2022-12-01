FLAGS=-O3 -fopenmp
EXEC=novoKNN
CC=gcc

ALL: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) -fopenmp $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) -fopenmp $(EXEC).o  -o $(EXEC)

clean:
	rm -rf $(EXEC) *.o
