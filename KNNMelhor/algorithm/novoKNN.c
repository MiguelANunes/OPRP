#include "knn.h"
#include <omp.h>

void swap(Point* a, Point* b){
	Point t = *a;
	*a = *b;
	*b = t;
}

int particiona(Point *vetor, int low, int high, int f(const void *, const void *)){
	Point pivot = vetor[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++){
		if (f(&vetor[j], &pivot) < 0){
			i++;
			swap(&vetor[i], &vetor[j]);
		}
	}
	swap(&vetor[i + 1], &vetor[high]);
	return (i + 1);
}

void quicksort(Point *vetor, int low, int high, int f(const void *, const void *)) {
	if (low < high) {
		int pivot = particiona(vetor, low, high, f);
		#pragma omp task
		{
			quicksort(vetor, low, pivot - 1, f);
		}
		#pragma omp task
		{
			quicksort(vetor, pivot + 1, high, f);
		}
	}
}

char knn(int n_groups, Group * groups, int k, Point to_evaluate, int n_points){

	int i, j;

	// Calculando a distancia entre os pontos e a chave
	#pragma omp parallel for schedule(dynamic, 1)// shared(groups)
	for (i = 0; i < n_groups; i++) {
        Group g = groups[i];
        for (j = 0; j < g.length; j++) {
			g.points[j].distance = euclidean_distance_no_sqrt(to_evaluate, g.points[j]);
		}
	}

	// ordenar && selecionar os K menores
	Point *pontos = (Point *) malloc(sizeof(Point) * n_points);
	int idxPonto = 0;

	for(i=0; i<n_groups; i++){
		Group g = groups[i];
		for (j = 0; j < g.length; j++){
			pontos[idxPonto] = g.points[j];
			idxPonto++;
		}
	}

	#pragma omp parallel
	{
		#pragma omp single
			quicksort(pontos, 0, n_points-1, compare_for_sort);
	}
	// qsort(pontos, n_points, sizeof(Point), compare_for_sort); // ordenando todo vetor

	#pragma omp parallel
	{
		#pragma omp single
			quicksort(pontos, 0, k-1, compare_for_sort_label);
	}
	// qsort(pontos, k, sizeof(Point), compare_for_sort_label); // ordenando os k primeiros

	// selecionar o grupo final

    char most_frequent = pontos[0].label;
    int most_frequent_count = 1;
    int current_frequency = 1;

    for (i = 1; i < k; i++) {
        if (pontos[i].label != pontos[i-1].label) {
            if (current_frequency > most_frequent_count) {
                most_frequent = pontos[i-1].label;
                most_frequent_count = current_frequency;
            }

            current_frequency = 1;
        } else {
            current_frequency++;
        }

        if (i == k - 1 && current_frequency > most_frequent_count) {
            most_frequent = pontos[i-1].label;
            most_frequent_count = current_frequency;
        }
    }

    return most_frequent;
}

int main() {
    int n_groups = parse_number_of_groups();
    int n_points = 0;

    Group * groups = (Group *) malloc(sizeof(Group) * n_groups);

    for (int i = 0; i < n_groups; i++) {
        groups[i] = parse_next_group();
		n_points += groups[i].length;
    }

    int k = parse_k();

    Point to_evaluate = parse_point();

	double start = omp_get_wtime();
	char res = knn(n_groups, groups, k, to_evaluate, n_points);
	double end = omp_get_wtime();
    printf("%c\n", res);
	printf("runtime: %.5lf\n", end-start);


}