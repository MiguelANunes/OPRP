#pragma once
#include"main_header.h"
#include<time.h>
#include<utility>
#include<vector>

using namespace std;

void chave_publica(mpz_t E, mpz_t N, mpz_t PQ);
void chave_privada(mpz_t D, mpz_t E, mpz_t PQ);
void primo_aleatorio(mpz_t Resultado, mpz_t Verificador);
bool provavelmente_primo(mpz_t PossivelPrimo, gmp_randstate_t EstadoAleatorio);
void primo_relativo(mpz_t Resultado, mpz_t PrimeiroPrimo, mpz_t SegundoPrimo);
void inverso_modular(mpz_t D, mpz_t E, mpz_t PQ);