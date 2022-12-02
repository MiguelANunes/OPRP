#include"main_header.h"
#include"chaves.h"
#include"cripto.h"
#include"bruta.h"
#include<chrono>

using namespace std;

int main(int argc, char const *argv[]){

	mpz_t E, N, D, PQ;
	TOTALBITS = -1;
	FILENAME = "-";

	if(argc == 3){
		TOTALBITS = atoi(argv[1]);
		FILENAME.assign(argv[2]);
		mpz_init2(E,TOTALBITS);
		mpz_init2(N,TOTALBITS);
		mpz_init2(D,TOTALBITS);
		mpz_init2(PQ, TOTALBITS);
	}else if(argc == 2){
		TOTALBITS = atoi(argv[1]);
		mpz_init2(E,TOTALBITS);
		mpz_init2(N,TOTALBITS);
		mpz_init2(D,TOTALBITS);
		mpz_init2(PQ, TOTALBITS);
	}

	int opcao = 0;


	while(true){
		cout << "Selecione a operação: " << endl;
		cout << "\t[1] Gerar Chave Pública " << endl;
		cout << "\t[2] Gerar Chave Privada " << endl;
		cout << "\t[3] Criptografar um Arquivo " << endl;
		cout << "\t[4] Descriptografar um Arquivo " << endl;
		cout << "\t[5] Quebra de Chave por Força Bruta " << endl;
		cout << "\t[6] Sair " << endl;
		cin >> opcao;

		switch(opcao){
			case 1:{
				if(TOTALBITS == -1){
					cout << "Digite o número de bits:" << endl;
					cin >> TOTALBITS;
					mpz_init2(E,TOTALBITS);
					mpz_init2(N,TOTALBITS);
					mpz_init2(D,TOTALBITS);
					mpz_init2(PQ, TOTALBITS);
				}
				cout << "Gerando a chave pública..." << endl;
				chave_publica(E,N,PQ);
				gmp_printf("Chave Pública <E,N>: <%Zd, %Zd>\n",E,N);
			}
			break;

			case 2:{
				if(TOTALBITS == -1){
					cout << "Digite o número de bits:" << endl;
					cin >> TOTALBITS;
					mpz_init2(E,TOTALBITS);
					mpz_init2(N,TOTALBITS);
					mpz_init2(D,TOTALBITS);
					mpz_init2(PQ, TOTALBITS);
				}
				if(mpz_cmp_ui(E,0) == 0){
					cout << "Gerando a chave pública..." << endl;
					chave_publica(E,N,PQ); // chave publica = <E,N>
					gmp_printf("Chave Pública <E,N>: <%Zd, %Zd>\n",E,N);
				}
				cout << "Gerando a chave privada..." << endl;
				chave_privada(D,E,PQ); // chave privada = <D,N>
				gmp_printf("Chave Privada <D,N>: <%Zd, %Zd>\n",D,N);
			}
			break;

			case 3:{
				if(FILENAME == "-"){
					cout << "Digite o nome do arquivo sem a extensão .txt:" << endl;
					cin >> FILENAME;
				}
				FILENAME += ".txt";
				cout << "Criptografando arquivo " << FILENAME << " ..." << endl;
				criptografar_arquivo(E,N);
			}
			break;

			case 4:{
				cout << "Descriptografando arquivo CRIPTO-" << FILENAME << " ..." << endl;
				descriptografar_arquivo(D,N);
			}
			break;

			case 5:{
				int SubEscolha=0;
				mpz_t P1, Q1;

				mpz_init2(P1,TOTALBITS);
				mpz_init2(Q1,TOTALBITS);

				cout << "Foram Implementados dois métodos de fatoração por Força Bruta" << endl;
				cout << "O primeiro verifica todos os possiveis divisores de N somando de 1 em 1 até a raiz quadrada de N" << endl;
				cout << "O segundo gera números primos aleatóriamente e verifica se dividem N" << endl;
				cout << "Qual quer executar ?" << endl;
				cout << "\t[1] Raiz Quadrada" << endl;
				cout << "\t[2] Aleatórios" << endl;
				cout << "\t[3] Ambos, Raiz Quadrada Primeiro" << endl;
				cout << "\t[4] Ambos, Aleatórios Primeiro" << endl;
				cout << "\t[5] Voltar" << endl;
				cin >> SubEscolha;

				switch(SubEscolha){
					case 1:{
						cout << "Executando método da Raiz Quadrda..." << endl;

						auto inicio = chrono::high_resolution_clock::now();
						forcabruta_quadrado(P1,Q1,N);
						auto termino = chrono::high_resolution_clock::now();

						cout << "Terminou de Fatorar pelo método da Raiz Quadrada." << endl;
						cout << "Encontrou os seguintes divisores de N:" << endl;
						gmp_printf("\tP = %Zd \n\tQ = %Zd \n",P1,Q1);

						chrono::duration<double> decorrido = termino - inicio;
						cout << "Tempo Decorrido: " << decorrido.count() << endl;
					}
					break;

					case 2:{
						cout << "Executando método dos Primos Aleatórios..." << endl;

						auto inicio = chrono::high_resolution_clock::now();
						forcabruta_aleatoria(P1,Q1,N);
						auto termino = chrono::high_resolution_clock::now();

						cout << "Terminou de Fatorar pelo método dos Primos Aleatórios." << endl;
						cout << "Encontrou os seguintes divisores de N:" << endl;
						gmp_printf("\tP = %Zd \n\tQ = %Zd \n",P1,Q1);
						chrono::duration<double> decorrido = termino - inicio;
						cout << "Tempo Decorrido: " << decorrido.count() << endl;
					}
					break;

					case 3:{
						cout << "Executando ambos, começando pela Raiz Quadrda..." << endl;

						auto inicio = chrono::high_resolution_clock::now();
						forcabruta_quadrado(P1,Q1,N);
						auto termino = chrono::high_resolution_clock::now();

						cout << "Terminou de Fatorar pelo método da Raiz Quadrada." << endl;
						cout << "Encontrou os seguintes divisores de N:" << endl;
						gmp_printf("\tP = %Zd \n\tQ = %Zd \n",P1,Q1);
						chrono::duration<double> decorrido = termino - inicio;
						cout << "Tempo Decorrido: " << decorrido.count() << endl;

						cout << "Executando método dos Primos Aleatórios..." << endl;

						inicio = chrono::high_resolution_clock::now();
						forcabruta_aleatoria(P1,Q1,N);
						termino = chrono::high_resolution_clock::now();

						cout << "Terminou de Fatorar pelo método dos Primos Aleatórios" << endl;
						cout << "Encontrou os seguintes divisores de N:" << endl;
						gmp_printf("\tP = %Zd \n\tQ = %Zd \n",P1,Q1);
						decorrido = termino - inicio;
						cout << "Tempo Decorrido: " << decorrido.count() << endl;
					}
					break;

					case 4:{
						cout << "Executando ambos, começando pelo Primos Aleatórios..." << endl;

						auto inicio = chrono::high_resolution_clock::now();
						forcabruta_aleatoria(P1,Q1,N);
						auto termino = chrono::high_resolution_clock::now();

						cout << "Terminou de Fatorar pelo método dos Primos Aleatórios." << endl;
						cout << "Encontrou os seguintes divisores de N:" << endl;
						gmp_printf("\tP = %Zd \n\tQ = %Zd \n",P1,Q1);
						chrono::duration<double> decorrido = termino - inicio;
						cout << "Tempo Decorrido: " << decorrido.count() << endl;

						cout << "Executando método da Raiz Quadrda..." << endl;
						inicio = chrono::high_resolution_clock::now();
						forcabruta_quadrado(P1,Q1,N);
						termino = chrono::high_resolution_clock::now();

						cout << "Terminou de Fatorar pelo método da Raiz Quadrada." << endl;
						cout << "Encontrou os seguintes divisores de N:" << endl;
						gmp_printf("\tP = %Zd \n\tQ = %Zd \n",P1,Q1);
						decorrido = termino - inicio;
						cout << "Tempo Decorrido: " << decorrido.count() << endl;
					}
					break;

					case 5:
					break;
				}
			}
			break;

			case 6:
				return 0;
			break;
		}
	}

    return 0;
}
