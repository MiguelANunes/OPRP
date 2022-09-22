#include<stdio.h>
#include<omp.h>

int main(void){
    
    int a, b; // variáveis que não pertencem as threads
    int tid;

    a = 100;
    b = 100;

    //              privada de cada thread  começa privada compartilhada entre as threads
    //                                   \/            \/             \/
    #pragma omp parallel num_threads(4) private(tid) firstprivate(a) shared(b)
    {
        tid = omp_get_thread_num();
        a += tid;

        #pragma omp critical // declara que está é uma região crítica
        {
            b += tid;
            printf("Hello %d %d %d\n", tid, a, b);
        }
    }
    return 0;
}