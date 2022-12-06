// header "geral" p/ ser incluso em todos os outros arquivos
#pragma once
#include<stdio.h> // necessário p/ IO de números da GMP
#include<gmp.h>
#include<iostream>
#include<string>

extern int TOTALBITS; 
// "constante" que determina o tamanho de bits para serem usados durante a execução
// não é do tipo const pq é necessário definir esse valor dentro da main
extern std::string FILENAME; // definindo o nome do arquivo como uma constante global
// pra facilitar a vida

typedef struct
{
	std::string lower;
	std::string upper;
	std::string valorP;
	std::string valorQ;
}block;