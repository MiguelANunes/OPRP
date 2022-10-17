#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){

	MPI_Status status;
	int size, rank;
	int tag = 0, a = 0;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	printf("Olá Mundo!\nSou %d de %d\n\n", rank, size);

	if(rank == 0){
		a = 1000;
	}

	MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("Sou %d, terminei com a = %d\n", rank, a);

	MPI_Finalize();

	return 0;
}

