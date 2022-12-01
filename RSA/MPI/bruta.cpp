#include"bruta.h"
#include"chaves.h"
// fatora por força bruta as chaves

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

void forcabruta_aleatoria(mpz_t Fator1, mpz_t Fator2, mpz_t NFatorar){
	// aleatoriamente gera numeros primos e verifica se dividem NFatorar

	mpz_t PrimoAleatorio, zero;
	mpz_init2(PrimoAleatorio,TOTALBITS);
	mpz_init2(zero,TOTALBITS);
	// devido a maneira que fizemos a função de gerar primos aleatórios
	// é necessário esse workaround
	// não tem efeito no tempo de computação da função

	while(true){
		primo_aleatorio(PrimoAleatorio, zero);
		if(mpz_divisible_p(NFatorar, PrimoAleatorio)){
			mpz_set(Fator1, PrimoAleatorio);
			mpz_divexact(Fator2, NFatorar, PrimoAleatorio);
			return;
		}
	}
}