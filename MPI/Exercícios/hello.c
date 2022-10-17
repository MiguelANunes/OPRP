#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){

	MPI_Status status;
	int size, rank;
	int tag = 0;
	int token = 0;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	printf("Olá Mundo!\nSou %d de %d\n\n", rank, size);

	if(rank == 0){
		printf("Sou o 0, mandei token = 0\n");
		MPI_Send(&token, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
		MPI_Recv(&token, 1, MPI_INT, size-1, tag, MPI_COMM_WORLD, &status);
		printf("Sou o 0, recebi token = %d\n",token);
	}else{
		MPI_Recv(&token, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &status);
		printf("Sou o %d, recebi token = %d\n", rank, token);
		token += 1;
		if(rank == size-1){
			printf("Sou o %d, mandei de volta para o 0\n", rank);
			MPI_Send(&token, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
		}else{
			printf("Sou o %d, mandei token = %d para %d\n", rank, token, rank+1);
			MPI_Send(&token, 1, MPI_INT, rank+1, tag, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();

	return 0;
}

