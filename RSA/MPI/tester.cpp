#include"main_header.h"
#include"chaves.h"
#include"cripto.h"
#include"bruta.h"
#include<time.h>
#include<fstream>
#include<omp.h>
#include<mpi.h>
#include<string>

using namespace std;
int THREADS;
int PROCS;
// int DONE;

vector<block> generate_input(int TOTALBITS, mpz_t N, int rank){
	// função que gera um array de blocos para serem fatorados

	int total_blocos = THREADS * PROCS * 8;
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

	int turn = 0;
	// variável que define qual processo vai carregar um dado na memória
	// começa igual para todos, reseta para 0 quando chega no limite de processos

	if(turn == rank){
		bloco.lower  = string(mpz_get_str(NULL, 10, lower));
		bloco.upper  = string(mpz_get_str(NULL, 10, upper));
		bloco.valorP = "0";
		bloco.valorQ = "0";
		blocos.push_back(bloco);
		turn++;
	}
	// colocando o primeiro bloco no vector fora do loop
	// pois da problema tentar colocar isso dentro do loop

	// primeiro bloco tem lower = 3, upper = sqrt(N)/total_blocos
	// segundo bloco tem lower = (sqrt(N)/total_blocos) + 1, upper = 2*(sqrt(N)/total_blocos)

	for(int i = 1; i < total_blocos; i++){
		if(turn == PROCS)
			turn = 0;// volta pro começo quando deu o máximo

		if(rank != turn){// só calcula se for a vez de calcular
			turn++; // se não, passa
			continue;
		}

		mpz_cdiv_q(lower, sqrt, total_blocos_mpz); // o limite inferior é o último limite superior arredondado para cima
		mpz_sub_ui(total_blocos_mpz, total_blocos_mpz, 1);
		mpz_fdiv_q(upper, sqrt, total_blocos_mpz); // o limite superior é a divisão da raiz de N pelo total de blocos restante

		bloco.lower  = string(mpz_get_str(NULL, 10, lower)); // mpz_get_str retorna um array de char
		bloco.upper  = string(mpz_get_str(NULL, 10, upper)); // string() converte isso para strings de C++
		bloco.valorP = "0";									 // ^ construtor de strings de C++
		bloco.valorQ = "0";
		blocos.push_back(bloco);
		turn++; // depois que calcula, passa a vez

	}

	mpz_clears(lower, upper, sqrt, total_blocos_mpz, NULL);

	return blocos;
}

int main(int argc, char *argv[]){

	mpz_t E,N,D,P1,Q1;
	int size, rank;
	TOTALBITS = -1;
	THREADS = -1;

	TOTALBITS = atoi(argv[1]);
	THREADS   = atoi(argv[2]);
	PROCS     = atoi(argv[3]);
	omp_set_num_threads(THREADS); // definindo o número de threads a serem usadas
	omp_set_dynamic(0); // desabilitando scheduling dinâmico, garantindo que usaram somente tantas threads quanto eu falei

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

	// Inicializando o MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	vector<block> dados = generate_input(TOTALBITS, N, rank);


	// cout << "Total de dados " << dados.size() << endl;

	// int count = 0;
	// for(auto & bloco: dados){
	// 	cout << "Bloco " << count << " Processo " << rank << endl;
	// 	cout << "\tLower:" << bloco.lower << endl;
	// 	cout << "\tUpper:" << bloco.upper << endl;
	// 	cout << "\tP:" << bloco.valorP << endl;
	// 	cout << "\tQ:" << bloco.valorQ << endl;
	// 	count++;
	// }
	
	clock_t inicio, termino;

	if(rank == 0)
		inicio = clock();
	#pragma omp parallel
	{// REGIÃO PARALELA
		#pragma omp single
		{// criando tasks
			for(auto & bloco: dados){
				#pragma omp task
				{// cada execução da função é uma task
					forcabruta_paralelo(&bloco,N, rank);
				}
			}
		}// fim do single, executando as tasks
	}// FIM DA REGIÃO PARALELA

	if(rank == 0){
		termino = clock();

		double decorrido = ((double) (termino - inicio))/CLOCKS_PER_SEC;

		cout << "Terminei de executar" << endl;
		cout << "Tempo Decorrido:" << endl;
		cout << decorrido << endl;
		tempos << decorrido << endl;

		tempos.close();
		publica.close();
		privada.close();
		valorN.close();
	}

	MPI_Finalize();

    return 0;
}
