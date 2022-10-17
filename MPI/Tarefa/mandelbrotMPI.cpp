#include <complex>
#include <iostream>
#include <mpi.h>
#include <sys/time.h>

using namespace std;

double wtime(){
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + t.tv_usec / 1000000.0;
}

int main(int argc, char *argv[]){
	int max_row, max_column, max_n;
	int params[3];
	int size, rank;
	double start_time, end_time;

	cin >> max_row;
	cin >> max_column;
	cin >> max_n;

	MPI_Init(&argc, &argv);	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	params[0] = max_row;
	params[1] = max_column;
	params[2] = max_n;

	MPI_Bcast(&params, 3, MPI_INT, 0, MPI_COMM_WORLD);

	max_row =    params[0];
	max_column = params[1];
	max_n =      params[2];

	char **mat = (char**)malloc(sizeof(char*)*max_row);
	char **final_mat = (char**)malloc(sizeof(char*)*max_row);

	for (int i=0; i<max_row;i++)
		final_mat[i]=(char*)malloc(sizeof(char)*max_column);

	for(int i = (max_row/size)*rank; i < (max_row/size)*(rank+1); i++)
		mat[i] = (char*)malloc(sizeof(char)*max_column);
	
	if(rank == 0)
		start_time = wtime();

	for(int r = (max_row/size)*rank; r < (max_row/size)*(rank+1); ++r){
		for(int c = 0; c < max_column; ++c){
			//para cada celula da matriz
			complex<float> z;
			int n = 0;
			while(abs(z) < 2 && ++n < max_n)
				z = pow(z, 2) + decltype(z)(
					(float)c * 2 / max_column - 1.5,
					(float)r * 2 / max_row - 1
				);
			mat[r][c]=(n == max_n ? '#' : '.');
		}
	}

	MPI_Gather(mat, max_row, MPI_CHAR, final_mat, max_row, MPI_CHAR, 0, MPI_COMM_WORLD);

	if(rank == 0){
		end_time = wtime();
		cout << "Tempo para calcular a matriz " << end_time - start_time << endl;
	}
	MPI_Finalize();
	return 0;
}


