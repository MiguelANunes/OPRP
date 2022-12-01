#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void swap(int* a, int* b){
  int t = *a;
  *a = *b;
  *b = t;
}

int particiona(int vetor[], int low, int high){
  int pivot = vetor[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++){
    if (vetor[j] < pivot){
      i++;
      swap(&vetor[i], &vetor[j]);
    }
  }
  swap(&vetor[i + 1], &vetor[high]);
  return (i + 1);
}

void quicksort(int vetor[], int low, int high) {
  if (low < high) {
    int pivot = particiona(vetor, low, high);

    #pragma omp task
    {
      quicksort(vetor, low, pivot - 1);
    }

    #pragma omp task
    {
      quicksort(vetor, pivot + 1, high);
    }
  }
}

int main(int argc, char** argv) {
  int nt = atoi(argv[1]);
  int n = atoi(argv[2]);
  int* vetor = (int*) malloc(sizeof(int) * n);

  srand(time(NULL));

  for(int i = 0; i < n; i++)
    vetor[i] = rand() % n + 1;

  double start_time = omp_get_wtime();

  #pragma omp parallel num_threads(nt)
  {
    #pragma omp single
    {
      quicksort(vetor, 0, n - 1);
    }
  }
  
  double end_time = omp_get_wtime();

  printf("%lf\n", end_time - start_time);

  // for (int i = 0; i < n; i++)
  //   printf("%d ", vetor[i]);
  // printf("\n");

  return 0;
}
