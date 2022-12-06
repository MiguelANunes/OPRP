#include"bruta.h"
#include"chaves.h"
#include<omp.h>
#include<mpi.h>
// fatora por força bruta as chaves

int DONE = 0;

void forcabruta_quadrado(mpz_t Fator1, mpz_t Fator2, mpz_t NFatorar){ 
	// recebendo o N da chave pública, fatora ele nos seus fatores primos P e Q
	// pelo método bobinho de verificar os divisores de 3 até sqrt(NFatorar)

    mpz_t Raiz, FatorTestado;
    mpz_init2(Raiz, TOTALBITS); 
    mpz_init2(FatorTestado, TOTALBITS);
    mpz_set_si(FatorTestado, 3);
    mpz_sqrt(Raiz,NFatorar);

    for( ; mpz_cmp (FatorTestado, Raiz) < 0; mpz_add_ui(FatorTestado, FatorTestado, 1)){
		if(mpz_divisible_p(NFatorar, FatorTestado) != 0){
			mpz_set(Fator1, FatorTestado);
			mpz_divexact(Fator2, NFatorar, FatorTestado);
			return;
		}
    }
}

int forcabruta_paralelo(block * bloco, mpz_t N, int rank){ 
	// recebendo o N da chave pública, fatora ele nos seus fatores primos P e Q
	// pelo método bobinho de verificar os divisores de bloco->lower até bloco->upper

	// cout << "Sou a thread" << omp_get_thread_num() << endl;

    mpz_t FatorTestado, Upper, aux;
	mpz_inits(FatorTestado, Upper, aux, NULL);
    mpz_set_str(FatorTestado, bloco->lower.c_str(), 10);
	mpz_set_str(Upper, bloco->upper.c_str(), 10);

    for( ; mpz_cmp (FatorTestado, Upper) < 0; mpz_add_ui(FatorTestado, FatorTestado, 1)){
		if(mpz_divisible_p(N, FatorTestado) != 0){
			bloco->valorP = string(mpz_get_str(NULL, 10, FatorTestado));
			mpz_divexact(aux, N, FatorTestado);
			bloco->valorQ = string(mpz_get_str(NULL, 10, aux));
			DONE = 1;
			MPI_Bcast(&DONE, 1, MPI_INT, rank, MPI_COMM_WORLD);
			// comunica todos os processos que terminou
			return 1;
		}
		if(DONE){
			MPI_Bcast(&DONE, 1, MPI_INT, rank, MPI_COMM_WORLD);
			// comunica todos os processos que terminou
			return 1;
		}
    }
	return 0;
}