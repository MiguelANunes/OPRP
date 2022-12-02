#include"main_header.h"
#include"chaves.h"
#include"cripto.h"
#include"bruta.h"
#include<time.h>
#include<fstream>

using namespace std;

int main(int argc, char const *argv[]){

	mpz_t E,N,D,PQ,P1,Q1,AUX;
	TOTALBITS = -1;

	TOTALBITS = atoi(argv[1]);

	// Chaves
	mpz_init2(E,TOTALBITS);
	mpz_init2(N,TOTALBITS);
	mpz_init2(D,TOTALBITS);

	// Auxiliares
	mpz_init2(PQ,TOTALBITS); // (P-1)(Q-1)
	mpz_init2(P1,TOTALBITS); // P
	mpz_init2(Q1,TOTALBITS); // Q

	mpz_init2(AUX,TOTALBITS); // Q

	ifstream valorN("keys/N-"+to_string(TOTALBITS)+"-bits.txt");
	ifstream publica("keys/Publica-"+to_string(TOTALBITS)+"-bits.txt");
	ifstream privada("keys/Privada-"+to_string(TOTALBITS)+"-bits.txt");

	ofstream tempos("tempos/tempo-"+to_string(TOTALBITS)+"-bits.txt");

	string aux;

	// primeiro, leio o N
	valorN >> aux;
	mpz_set_str(N,aux.c_str(),10);

	// depois, leio o E
	publica >> aux;
	mpz_set_str(E,aux.c_str(),10);

	// por fim, o D, para comparar com a chave fatorada
	privada >> aux;
	mpz_set_str(D,aux.c_str(),10);

	clock_t inicio = clock();
	forcabruta_quadrado(P1,Q1,N);
	clock_t termino = clock();
	double decorrido = ((double) (termino - inicio))/CLOCKS_PER_SEC;

	cout << "Divisores de N:" << endl;
	gmp_printf("\tP = %Zd \n\tQ = %Zd \n",P1,Q1);
	cout << "Tempo Decorrido:" << endl;
	cout << decorrido << endl;
	tempos << decorrido << endl;
	tempos.close();

	publica.close();
	privada.close();
	valorN.close();

    return 0;
}
