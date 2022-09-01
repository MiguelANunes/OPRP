#include <complex>
#include <iostream>
#include <pthread.h>
#include <sys/time.h>

typedef struct{
	int    tid;
	int    row_start;
	int    row_end; 
	int    max_row;
	int    max_column; 
	int    max_n;
	char **mat;
}thread_param;


using namespace std;

// void mandelbrot(int row_start, int row_end, int max_column, int max_n, char** mat){
void *mandelbrot(void *arg){
	thread_param *p = (thread_param *)arg;

	for(int r = p->row_start; r < p->row_end; ++r){
        for(int c = 0; c < p->max_column; ++c){
            //para cada celula da matriz
            complex<float> z;
			int n = 0;
			while(abs(z) < 2 && ++n < p->max_n)
				z = pow(z, 2) + decltype(z)(
					(float)c * 2 / p->max_column - 1.5,
					(float)r * 2 / p->max_row - 1
				);
			p->mat[r][c]=(n == p->max_n ? '#' : '.');
		}
	}
	pthread_exit(NULL);
}

double wtime(){
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + t.tv_usec / 1000000.0;
}

int main(){
	
	int max_row, max_column, max_n, thread_amount;
	double start_time, end_time;

	cin >> max_row;
	cin >> max_column;
	cin >> max_n;
	cin >> thread_amount;

	pthread_t *threads  = (pthread_t*)malloc(sizeof(pthread_t)*thread_amount);
	thread_param *param = (thread_param*)malloc(sizeof(thread_param)*thread_amount);


	char **mat = (char**)malloc(sizeof(char*)*max_row);
	char *data = (char*)malloc(sizeof(char)*max_row*max_column);

	for (int i=0; i<max_row;i++){
		// inicializando a matriz como um grande "bloco"
		// ao invés de várias linhas
		mat[i] = &data[i*max_column];
	}

	int slice = max_row / thread_amount;

	for(int i = 0; i < thread_amount; i++){
		// config de thread
		param[i].tid 		= i;
		param[i].row_start 	= i * slice;
		param[i].row_end 	= (i == thread_amount-1) ? max_row : (i * slice) + slice;
		param[i].max_row    = max_row;
		param[i].max_column = max_column;
		param[i].max_n 		= max_n;
		param[i].mat 		= mat;
	}

	for(int tid = 0; tid < thread_amount; tid++){
		// criando as threads
		pthread_create(&threads[tid], NULL, mandelbrot, (void*) &param[tid]);
	}

	start_time = wtime();
	for (int tid = 0; tid < thread_amount; tid++){
		// esperando as threads terminarem
		pthread_join(threads[tid], NULL);
	}
	end_time = wtime();

	printf("%f\n", end_time - start_time);
	fflush(stdout);

	// for(int r = 0; r < max_row; ++r){
	// 	for(int c = 0; c < max_column; ++c)
	// 		std::cout << mat[r][c];
	// 	cout << '\n';
	// }
	pthread_exit(NULL);
}


