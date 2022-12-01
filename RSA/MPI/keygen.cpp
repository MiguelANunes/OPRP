#include"main_header.h"
#include"chaves.h"
#include"cripto.h"
#include"bruta.h"
#include<chrono>
#include<fstream>

using namespace std;

int main(int argc, char const *argv[]){

	mpz_t E,N,D,PQ,P1,Q1;
	TOTALBITS = -1;

	TOTALBITS = atoi(argv[1]);

	mpz_init2(E,TOTALBITS);
	mpz_init2(N,TOTALBITS);
	mpz_init2(D,TOTALBITS);

	mpz_init2(PQ,TOTALBITS);
	mpz_init2(P1,TOTALBITS);
	mpz_init2(Q1,TOTALBITS);
	
	//auto inicio = chrono::high_resolution_clock::now();
	//auto termino = chrono::high_resolution_clock::now();
	//chrono::duration<double> decorrido = termino - inicio;

	// Criando e abrindo arquivos de resultado
	ofstream publica("keys/Publica-"+to_string(TOTALBITS)+"-bits.txt");
	ofstream privada("keys/Privada-"+to_string(TOTALBITS)+"-bits.txt");
	ofstream valorN("keys/N-"+to_string(TOTALBITS)+"-bits.txt");
	
	// Gerando a chave publica e escrevendo ela num arquivo
	chave_publica(E,N,PQ);
	string Aux1(mpz_get_str(NULL,10,E));
	string Aux2(mpz_get_str(NULL,10,N));
	publica << Aux1 << endl;
	publica.close();

	// Gerando a chave privada e escrevendo ela num arquivo
	chave_privada(D,E,PQ);
	string Aux3(mpz_get_str(NULL,10,D));
	privada << Aux3 << endl;
	privada.close();

	valorN << Aux2 << endl;
	valorN.close();

	// cout << "fatorando" << endl;
	// auto inicio = chrono::high_resolution_clock::now();
	// forcabruta_quadrado(P1,Q1,N);
	// auto termino = chrono::high_resolution_clock::now();
	// chrono::duration<double> decorrido = termino - inicio;
	// output << decorrido.count() << endl;

    return 0;
}
