#include"chaves.h"
// geração das chaves publica e privada

int TOTALBITS; // necessário definir aqui tbm pq no header "main_header" a variável esta definida como extern
// isto é, o valor dela é definida em algum lugar e o linker descobre onde é isso
// nesse caso, é definida na main
// para acessar o valor dela em outros arquivos, tenho que declarar essa variável neste arquivo

void chave_publica(mpz_t E, mpz_t N, mpz_t PQ){
    mpz_t PrimeiroPrimo, SegundoPrimo, ProdutoPrimos, PrimoRelativoProduto;

    mpz_init2(PrimeiroPrimo, TOTALBITS); // P
    mpz_init2(SegundoPrimo, TOTALBITS); // Q
    mpz_init2(ProdutoPrimos, TOTALBITS); // N
    mpz_init2(PrimoRelativoProduto,TOTALBITS);

	// segundo argumento garante que gero dois números primos diferentes
	primo_aleatorio(PrimeiroPrimo,SegundoPrimo);
	primo_aleatorio(SegundoPrimo,PrimeiroPrimo);
    
    mpz_mul(ProdutoPrimos, PrimeiroPrimo, SegundoPrimo); // N = P*Q
    
	mpz_sub_ui(PrimeiroPrimo, PrimeiroPrimo, 1); //P-1
	mpz_sub_ui(SegundoPrimo, SegundoPrimo, 1); // Q-1
    primo_relativo(PrimoRelativoProduto, PrimeiroPrimo, SegundoPrimo); // E
    
	mpz_mul(PQ, PrimeiroPrimo, SegundoPrimo); // (P-1)(Q-1)
    mpz_set(E,PrimoRelativoProduto);
    mpz_set(N,ProdutoPrimos);
}

void chave_privada(mpz_t D, mpz_t E, mpz_t PQ){
	inverso_modular(D,E,PQ);
}

void inverso_modular(mpz_t D, mpz_t E, mpz_t PQ){
	// calcula o inverso modular de E no modulo PQ e armazena em D
	// AX + BY = 1 <--> AX cong. 1 (mod B)
	// A == E
	// X == D
	// B == PQ --> PQ = (P-1)(Q-1) onde P e Q são os primos aleatórios
	// Y não importa, mas é necessário para o calculo

	mpz_t Quociente, A, B, X, Y, Auxiliar, Auxiliar2;

	mpz_init2(Quociente,TOTALBITS);
	mpz_init2(A,TOTALBITS);
	mpz_init2(B,TOTALBITS);
	mpz_init2(X,TOTALBITS);
	mpz_init2(Y,TOTALBITS);
	mpz_init2(Auxiliar,TOTALBITS);
	mpz_init2(Auxiliar2,TOTALBITS);

	mpz_set(A,E);  // copiando as entradas para variáveis que posso alterar
	mpz_set(B,PQ);
	mpz_set_ui(X,1);
	mpz_set_ui(Y,0);

	while(mpz_cmp_ui(A,1) > 0){
		mpz_fdiv_q(Quociente,A,B);
		
		mpz_set(Auxiliar,B);
		mpz_fdiv_r(B,A,B);
		mpz_set(A,Auxiliar);
		mpz_set(Auxiliar, Y);
		
		mpz_set(Auxiliar2,X);
		mpz_submul(Auxiliar2, Quociente, Y);
		mpz_set(Y,Auxiliar2);
		mpz_set(X,Auxiliar);
	}
	
	if(mpz_sgn(X) == -1)
		mpz_add(X,X,PQ);

	mpz_set(D,X);
}

void primo_relativo(mpz_t Resultado, mpz_t PrimeiroPrimo, mpz_t SegundoPrimo){
    // calcula um primo relativo de (PrimeiroPrimo-1)(SegundoPrimo-1)
    mpz_t PR, MDC, E;
    gmp_randstate_t Estado;
    gmp_randinit_default(Estado);
	
    mpz_init2(PR, TOTALBITS);
    mpz_init2(MDC, TOTALBITS);
    mpz_init2(E, TOTALBITS);
    gmp_randseed_ui(Estado,time(NULL));
    
    mpz_mul(PR,PrimeiroPrimo,SegundoPrimo); // (P-1)(Q-1)	
    mpz_urandomm(E,Estado,PR); // Gerando um E aleatório
    mpz_gcd(MDC,E,PR); // Calculando o MDC de E com (P-1)(Q-1)

    while(mpz_cmp_ui(MDC,1) != 0){ // enquanto o MDC não for 1, procure por outro E
        mpz_urandomm(E,Estado,PR);
        mpz_gcd(MDC,E,PR);
    }
    
    mpz_set(Resultado,E);
    gmp_randclear(Estado);
}

void primo_aleatorio(mpz_t Resultado, mpz_t Verificador){ 
    // retorna um número primo aleatório com <TOTALBITS> bits
    gmp_randstate_t Estado; 
    mpz_t PrimoGerado;

    mpz_init2(PrimoGerado,TOTALBITS); 
    gmp_randinit_default(Estado); 

    gmp_randseed_ui(Estado,time(NULL)); 
    mpz_urandomb(PrimoGerado,Estado,TOTALBITS); 

	if(mpz_cmp_ui(Verificador, 0) == 0){ // não foi gerado outro numero primo
		while(!(provavelmente_primo(PrimoGerado, Estado)))
        	mpz_urandomb(PrimoGerado,Estado,TOTALBITS);
	}else{ // foi e tenho que garantir que gero dois primos diferentes
		while(!(provavelmente_primo(PrimoGerado, Estado)) || (mpz_cmp(PrimoGerado,Verificador) == 0))
        	mpz_urandomb(PrimoGerado,Estado,TOTALBITS);
	}

    mpz_set(Resultado,PrimoGerado); 
    gmp_randclear(Estado);
}

bool provavelmente_primo(mpz_t PossivelPrimo, gmp_randstate_t EstadoAleatorio){
// verifica a primalidade de um número de maneira probabilistica usando o teste de Fermat

    if(mpz_divisible_ui_p(PossivelPrimo,3) != 0 || mpz_divisible_ui_p(PossivelPrimo,5)  != 0 ||
       mpz_divisible_ui_p(PossivelPrimo,7) != 0 || mpz_divisible_ui_p(PossivelPrimo,11) != 0 || 
       mpz_divisible_ui_p(PossivelPrimo,13)!= 0 || mpz_divisible_ui_p(PossivelPrimo,17) != 0 || 
       mpz_even_p(PossivelPrimo) != 0){
        return false;
    }// verificando se é divisivel por 3, 5, 7, 11, 13, 17 ou se é par

    mpz_t Testemunha, Limite, um;
    mpz_init2(Testemunha,TOTALBITS);
    mpz_init2(Limite,TOTALBITS);
    mpz_init_set_ui(um,1);
    // função de verificar congruência não aceita int's como argumento
    // por causa disso, esse work around é necessário

    for(int i = 0; i < 25000; i++){
        mpz_sub_ui(Limite,PossivelPrimo,1);
        mpz_urandomm(Testemunha, EstadoAleatorio, PossivelPrimo);
        //  gera um número aleatório entre 0 e (PossivelPrimo)-1

        mpz_powm(Testemunha, Testemunha, Limite, PossivelPrimo);
        // se a Testemunha de Fermat não é congruente à 1 (mod PossivelPrimo), então PossivelPrimo não é primo
        if(mpz_congruent_p(Testemunha, um, PossivelPrimo) == 0 && (mpz_cmp_ui(Testemunha, 1) > 0))
            return false; 
    }
    return true; 
}
