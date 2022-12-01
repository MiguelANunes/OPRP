#include "knn.h"
#include <omp.h>

char knn(int n_groups, Group * groups, int k, Point to_evaluate) {
    char * labels = (char *) malloc(sizeof(char) * k);
    char ** labelsFinais = (char **) malloc(sizeof(char) * n_groups);
    float * distances = (float *) malloc(sizeof(float) * k);
    float ** distancesFinais = (float **) malloc(sizeof(float) * n_groups);

    int i, j, x, y;

    for (i = 0; i < k; i++) {
        labels[i] = -1;
        distances[i] = -1;
        labelsFinais[i] = (char *) malloc(sizeof(char) * k);
        distancesFinais[i] = (float *) malloc(sizeof(float) * k);
    }

    int ii = 0;
    for (i = 0; i < n_groups; i++){
        for (ii = 0; ii < k; ii++){
            labelsFinais[i][ii] = -1;
            distancesFinais[i][ii] = -1;
        }
    }

    char most_frequent;
    int most_frequent_count = 1;
    int current_frequency = 1;

    int set = 0;

    #pragma omp parallel shared(labelsFinais, distancesFinais) firstprivate(labels,distances) private(i,j,x,y,set)
    {
        int tid = omp_get_thread_num();
        #pragma omp for 
        for (i = 0; i < n_groups; i++) {
            // printf("Sou a thread %d, estou com %d\n", tid, i);
            Group g = groups[i];

            for (j = 0; j < g.length; j++) {
                // cada loop calcula a distância do ponto até outro ponto de algum grupo
                float d = euclidean_distance_no_sqrt(to_evaluate, g.points[j]);

                set = 0;
                for (x = 0; x < k; x++) {
                    if ((d < distancesFinais[i][x] || distancesFinais[i][x] == -1) && set != 1) {
                        for (y = k - 1; y > x; y--) {
                            distancesFinais[i][y] = distancesFinais[i][y - 1];
                            labelsFinais[i][y] = labelsFinais[i][y - 1];
                        }
                        set = 1;
                        labelsFinais[i][x] = g.label;
                        distancesFinais[i][x] = d;
                    }
                }
            }
        }
    }

    int zz, xx;
    for(zz=0; zz<n_groups;zz++){
        for(xx=0;xx<k;xx++)
            printf("%d ", labelsFinais[zz][xx]);
        printf("\n");
    }

    printf("\n\n");

    for(zz=0; zz<n_groups;zz++){
        for(xx=0;xx<k;xx++)
            printf("%.2lf ", distancesFinais[zz][xx]);
        printf("\n");
    }

    int menor, idx;
    char * newlabels = (char *) malloc(sizeof(char) * k);
    for(zz=0; zz<n_groups;zz++){
        menor = 1000000;
        idx = 0;
        for(xx=0;xx<k;xx++){
            if(distancesFinais[zz][xx] < menor && distancesFinais[zz][xx] > 0){
                menor = distancesFinais[zz][xx];
                idx = xx;
            }
        }
        if(menor != 1000000){
            printf("idx=%d, distancesFinais[zz][idx]=%lf\n",idx,distancesFinais[zz][idx]);
            printf("idx=%d, labelsFinais[zz][idx]=%d\n",idx,labelsFinais[zz][idx]);
            newlabels[zz] = labelsFinais[zz][idx];
        }
    }

    int yy = 0;
    for(yy=0;yy<k;yy++){
        printf("%d ", newlabels[yy]);
        printf("%c \n", newlabels[yy]);
    }

    // qsort(labelsFinais, k, sizeof(char), compare_for_sort);
    // printf("\n");
    // for(zz=0; zz<n_groups;zz++){
    //     printf("%d \n", labelsFinais[zz]);
    // }
    return 32;
    most_frequent = labelsFinais[0];
    printf("most_frequent = %d \n", most_frequent);

    #pragma omp parallel shared(labelsFinais) private(most_frequent, most_frequent_count, current_frequency)
    {
        #pragma omp for
        for (i = 1; i < k; i++) {
            if (labelsFinais[i] != labelsFinais[i - 1]) {
                if (current_frequency > most_frequent_count) {
                    most_frequent = labelsFinais[i - 1];
                    most_frequent_count = current_frequency;
                }

                current_frequency = 1;
            } else {
                current_frequency++;
            }

            if (i == k - 1 && current_frequency > most_frequent_count) {
                most_frequent = labelsFinais[i - 1];
                most_frequent_count = current_frequency;
            }
        }
    }


    printf("%d \n", most_frequent);
    return most_frequent;
}

int main() {
    int n_groups = parse_number_of_groups();
    
    Group * groups = (Group *) malloc(sizeof(Group) * n_groups);

    for (int i = 0; i < n_groups; i++) {
        groups[i] = parse_next_group();
    }

    int k = parse_k();

    Point to_evaluate = parse_point();

    printf("%c\n", knn(n_groups, groups, k, to_evaluate));
}