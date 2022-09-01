/*
 *  Exemplo de programa para multiplicação de matrizes em paralelo, usando POSIX threads.
 *  Obs.: Somente para matrizes quadradas.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "matrix.h"

/*
 * Estrutura que contem parâmetros para as threads
 */
typedef struct {
		int tid;
		int ntasks;
		matrix_t *A;
		matrix_t *B;
		matrix_t *C;
} param_t;


/*
 * Calcula linhas da matriz resultante C
 */
void matrix_mult(int tid, int ntasks, matrix_t* A, matrix_t* B, matrix_t* C){
	// número de linhas calculadas por uma dada thread depende de seu id
	// isso evita problema de conflito de threads
	int i, j, k;
	double sum;
	int n = A->rows;
	i = tid;
	// Calcula algumas linhas da matriz resultante
	while (i < n) {
		for (j = 0; j < n; j++) {
			sum = 0.0;
			for (k = 0; k < n; k++) {
				sum += A->data[i][k] * B->data[k][j];
			}
			C->data[i][j] = sum;
		}
		i += ntasks;
	}
}

/*
 * Função executada por uma thread
 */
void *matrix_mult_worker(void *arg){
	// abre os argumentos e chama a função de multiplicação
	param_t *p = (param_t *) arg;
	matrix_mult(p->tid, p->ntasks, p->A, p->B, p->C);
}

/* 
 * Calcula C = A * B, distribuindo o trabalho entre ntasks threads
 */
void matrix_mult_threads(matrix_t *A, matrix_t *B, matrix_t* C, int ntasks){
	int i;
	pthread_t *threads;
	param_t *args;
	
	// alocando array de threads e array de argumentos
	threads = (pthread_t *) malloc(ntasks * sizeof(pthread_t));
	args = (param_t *) malloc(ntasks * sizeof(param_t));

	// carregando argumentos e criando as threads
	for (i = 0; i < ntasks; i++){
		args[i].tid = i;
		args[i].ntasks = ntasks;
		args[i].A = A;
		args[i].B = B;
		args[i].C = C;
		//													  Castando o vetor de argumentos pra void* e deslocando no
		//													  vetor usando a sintaxe +i pois não posso fazer [i] em void
		pthread_create(&threads[i], NULL, matrix_mult_worker, (void *) (args+i));
		printf("Criei a thread %d\n", i);
	}
	
	// juntando as threads
	for (i = 0; i < ntasks; i++){
		pthread_join(threads[i], NULL);
		printf("Terminei a thread %d\n", i);
	}

	free(args);
	free(threads);
}

/*
 * Tempo (wallclock) em segundos
 */ 
double wtime(){
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + t.tv_usec / 1000000.0;
}

int main(int argc, char **argv){
	int n;
	int rc;
	int taskid, ntasks;
	double start_time, end_time;

	scanf("%d %d", &ntasks, &n);

	// Cria matrizes
	matrix_t *A = matrix_create(n, n);
	matrix_randfill(A); // A é preenchida com números aleatórios
	matrix_t *B = matrix_create(n, n);
	matrix_fill(B, 1.); // B é preenchida com 1 (double)
	matrix_t *C = matrix_create(n, n); // C não é preenchida

	// Calcula C = A * B em ntasks, medindo o tempo
	start_time = wtime();
	matrix_mult_threads(A, B, C, ntasks);
	end_time = wtime();

	// Mostra estatísticas da execução
	printf("%d %f\n", ntasks, end_time - start_time);
	fflush(stdout);

	matrix_destroy(A);
	matrix_destroy(B);
	matrix_destroy(C);

	return EXIT_SUCCESS;
}
