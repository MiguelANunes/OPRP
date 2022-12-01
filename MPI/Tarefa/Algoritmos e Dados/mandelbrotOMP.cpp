#include <complex>
#include <iostream>
#include <omp.h>
#include <sys/time.h>

using namespace std;

double wtime(){
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + t.tv_usec / 1000000.0;
}

int main(){
	int max_row, max_column, max_n, thread_amount=4;
	double start_time, end_time;

	// omp_sched_t kind;
	// int chunk;
	// omp_get_schedule(&kind, &chunk);
	// printf("Estou usando schedule %d\n", kind);
	// cout << "Static: 1, Dynamic: 2, Guided: 3 " << endl;

	cin >> max_row;
	cin >> max_column;
	cin >> max_n;

	char **mat = (char**)malloc(sizeof(char*)*max_row);

	for (int i=0; i<max_row;i++)
		mat[i]=(char*)malloc(sizeof(char)*max_column);
	
	omp_set_num_threads(thread_amount);

	start_time = wtime();
	#pragma omp parallel shared(max_row, max_column, max_n) firstprivate(mat)
	{	
		// auto num = omp_get_num_threads();
		// cout << "Tenho " << num << " Threads" << endl;
		#pragma omp for
		for(int r = 0; r < max_row; ++r){
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

	}
	end_time = wtime();

	printf("%f\n", end_time - start_time);
	fflush(stdout);
	// for(int r = 0; r < max_row; ++r){
	// 	for(int c = 0; c < max_column; ++c)
	// 		std::cout << mat[r][c];
	// 	cout << '\n';
	// }	
}


