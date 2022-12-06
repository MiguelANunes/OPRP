#include"main_header.h"
#include"chaves.h"
#include"cripto.h"
#include"bruta.h"
#include<time.h>
#include<fstream>
#include<omp.h>
#include<string>

using namespace std;

vector<block> generate_input(int TOTALBITS, mpz_t N){
	// função que gera um array de blocos para serem fatorados

	int threads = omp_get_num_threads();
	int total_blocos = threads * 8;
	block bloco;
	vector<block> blocos;

	mpz_t lower, upper, sqrt, total_blocos_mpz;
	mpz_init2(lower, TOTALBITS);
	mpz_init2(upper, TOTALBITS);

	mpz_init2(sqrt, TOTALBITS);
	mpz_init(total_blocos_mpz);

	mpz_set_si(lower, 3);
	mpz_set_si(total_blocos_mpz, total_blocos);
	mpz_sqrt(sqrt,N);

	mpz_fdiv_q(upper, sqrt, total_blocos_mpz); // upper = sqrt(N)/total_blocos

	bloco.lower  = string(mpz_get_str(NULL, 10, lower));
	bloco.upper  = string(mpz_get_str(NULL, 10, upper));
	bloco.valorP = "0";
	bloco.valorQ = "0";
	blocos.push_back(bloco);
	// colocando o primeiro bloco no vector fora do loop
	// pois da problema tentar colocar isso dentro do loop

	// primeiro bloco tem lower = 3, upper = sqrt(N)/total_blocos
	// segundo bloco tem lower = (sqrt(N)/total_blocos) + 1, upper = 2*(sqrt(N)/total_blocos)
	for(int i = 1; i < total_blocos; i++){
		mpz_cdiv_q(lower, sqrt, total_blocos_mpz); // o limite inferior é o último limite superior arredondado para cima
		mpz_sub_ui(total_blocos_mpz, total_blocos_mpz, 1);
		mpz_fdiv_q(upper, sqrt, total_blocos_mpz); // o limite superior é a divisão da raiz de N pelo total de blocos restante

		bloco.lower  = string(mpz_get_str(NULL, 10, lower)); // mpz_get_str retorna um array de char
		bloco.upper  = string(mpz_get_str(NULL, 10, upper)); // string() converte isso para strings de C++
		bloco.valorP = "0";									 // ^ construtor de strings de C++
		bloco.valorQ = "0";
		blocos.push_back(bloco);
	}

	mpz_clears(lower, upper, sqrt, total_blocos_mpz, NULL);

	return blocos;
}

int main(int argc, char const *argv[]){

	mpz_t E,N,D,P1,Q1;
	TOTALBITS = -1;

	TOTALBITS = atoi(argv[1]);

	// Chaves
	mpz_init2(E,TOTALBITS);
	mpz_init2(N,TOTALBITS);
	mpz_init2(D,TOTALBITS);

	// Fatores de N
	mpz_init2(P1,TOTALBITS); // P
	mpz_init2(Q1,TOTALBITS); // Q

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
	mpz_set_str(D,aux.c_str(),10); // opcional

	vector<block> dados = generate_input(TOTALBITS, N);

	// int count = 0;
	// for(auto & bloco: dados){
	// 	cout << "Bloco " << count << endl;
	// 	cout << "\tLower:" << bloco.lower << endl;
	// 	cout << "\tUpper:" << bloco.upper << endl;
	// 	cout << "\tP:" << bloco.valorP << endl;
	// 	cout << "\tQ:" << bloco.valorQ << endl;
	// 	count++;
	// }

	int count = 0;
	clock_t inicio, termino;
	for(auto & bloco: dados){
		cout << "Testando bloco " << count << endl;
		
		inicio = clock();
		forcabruta_paralelo(&bloco,N); // pasando o endereço do bloco para poder editar ele dentro da função
		termino = clock();

		double decorrido = ((double) (termino - inicio))/CLOCKS_PER_SEC;
		cout << "Tempo Decorrido:" << endl;
		cout << decorrido << endl;

		cout << "Divisores estavam nesse bloco?" << endl;
		if(bloco.valorP != "0"){
			cout << "\tSim!" << endl << "\tDivisores de N:" << endl;
			cout << "\t\tP = " << bloco.valorP << "\n\t\tQ = " << bloco.valorQ << endl;
		}else{
			cout << "\tNão!" << endl;
		}
	}

	// tempos << decorrido << endl;
	// tempos.close();

	publica.close();
	privada.close();
	valorN.close();

    return 0;
}
