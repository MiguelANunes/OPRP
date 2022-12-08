#pragma once
#include"main_header.h"
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

void criptografar_arquivo(mpz_t E, mpz_t N);
void descriptografar_arquivo(mpz_t D, mpz_t N);