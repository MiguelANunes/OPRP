// criptografa e descriptografa dados em um arquivo
#include"cripto.h"
#include"chaves.h"

string FILENAME;

void criptografar_arquivo(mpz_t E, mpz_t N){
	// cifra o arquivo FILENAME.txt
	// o arquivo cifrado terá o nome 
	// CRIPTO-FILENAME.txt
	string SourceFILENAME, OutFILENAME, TextoLido;
	fstream ArquivoCifrar;
	ofstream ArquivoCifrado;

	char Letra;
	mpz_t LetraCifrada, Aux;
	mpz_init2(LetraCifrada,TOTALBITS);
	mpz_init2(Aux,TOTALBITS); // auxiliar p/ a função de codificação

	vector<int> LinhaASCII; // cada termo desse vector é o código ascii de uma letra de uma palavra da linha lida
	vector<vector<int>> TextoASCII; // códigos ascii de todo o texto lido

	vector<string> LinhaCifrada; // linha do texto depois de ser cifrada
	vector<vector<string>> TextoCifrado; // texto inteiro cifrado
	// não da pra fazer vector de mpz_t, mas da pra converter um mpz_t pra char*
	// este que por sua vez pode ser convertido em string e colocado num vector

	SourceFILENAME = FILENAME;
	OutFILENAME = "CRIPTO-"+FILENAME;
	ArquivoCifrar.open(SourceFILENAME);

	if(!ArquivoCifrar.is_open()){
		cerr << "Não conseguiu abrir arquivo: " << SourceFILENAME << endl;
		return;
	}

	while(getline(ArquivoCifrar,TextoLido)){
		// convertendo o texto lido em ASCII
		for(unsigned int j = 0; j < TextoLido.length(); j++){
			Letra = TextoLido[j];
			if(Letra != ' ')
				LinhaASCII.push_back(int(Letra));
			else
				LinhaASCII.push_back(-1);
		}
		TextoASCII.push_back(LinhaASCII);
		LinhaASCII.clear();
	}

	for(unsigned int j = 0; j < TextoASCII.size(); j++){
		for(unsigned int k = 0; k < TextoASCII[j].size(); k++){
			// cifrando o texto lido
			if(TextoASCII[j][k] == -1){
				LinhaCifrada.push_back("-");
				continue;
			}
			mpz_set_ui(Aux, TextoASCII[j][k]);
			mpz_powm(LetraCifrada,Aux,E,N);

			string AuxString(mpz_get_str(NULL,10,LetraCifrada));
			LinhaCifrada.push_back(AuxString);
		}
		TextoCifrado.push_back(LinhaCifrada);
		LinhaCifrada.clear();
	}

	TextoASCII.clear();
	ArquivoCifrar.close();

	ArquivoCifrado.open(OutFILENAME);
	for(unsigned int j = 0; j < TextoCifrado.size(); j++){
		for(unsigned int k = 0; k < TextoCifrado[j].size(); k++){
			// escrevendo o texto cifrado no arquivo
			if(TextoCifrado[j][k] == "-"){
				ArquivoCifrado << endl; // uma palavra criptografada por linha
				continue;
			}
			ArquivoCifrado << TextoCifrado[j][k] << " ";
		}
		ArquivoCifrado << endl << "x" << endl; // indicador de nova linha
	}

	TextoCifrado.clear();
	ArquivoCifrado.close();
	cout << "Arquivo Criptografado salvo em " << OutFILENAME << endl;
}

void descriptografar_arquivo(mpz_t D, mpz_t N){
	// decifra o texto em um arquivo cifrado chamado CRIPTO-FILENAME.txt
	// o arquivo resultante tera nome DECRIPTO-FILENAME.txt

	mpz_t LetraDecifrada;
	mpz_init2(LetraDecifrada, TOTALBITS);

	string SourceFILENAME, OutFILENAME, TextoLido, TextoDecifrado, StringAuxiliar;
	vector<int> LinhaASCII;
	vector<vector<int>> TextoASCII;

	fstream ArquivoCifrado; 
	ofstream ArquivoDecifrado; 

	SourceFILENAME = "CRIPTO-"+FILENAME;
	OutFILENAME = "DECRIPTO-"+FILENAME;
	ArquivoCifrado.open(SourceFILENAME);
	TextoDecifrado = "";

	if(!ArquivoCifrado.is_open()){
		cerr << "Não conseguiu abrir arquivo: " << SourceFILENAME << endl;
		return;
	}

	while(getline(ArquivoCifrado,TextoLido)){ 
		stringstream Stream(TextoLido); 

		while(getline(Stream,StringAuxiliar,' ')){ 
			
			if(StringAuxiliar == "x"){
				LinhaASCII.pop_back(); // tirando o último espaço desnecessário
				TextoASCII.push_back(LinhaASCII);
				LinhaASCII.clear();
				continue;
			}

			mpz_set_str(LetraDecifrada,StringAuxiliar.c_str(),10);
			mpz_powm(LetraDecifrada,LetraDecifrada,D,N);
			LinhaASCII.push_back(mpz_get_ui(LetraDecifrada));
		}
		if(LinhaASCII.front() == -1) 
			LinhaASCII.erase(LinhaASCII.begin());
		// por algum motivo que não estou a fim de descobrir
		//toda linha depois da primeira começava com um espaço, isso garante que isso não acontece
		LinhaASCII.push_back(-1);
	}

	ArquivoCifrado.close();
	ArquivoDecifrado.open(OutFILENAME);

	for(unsigned int j = 0; j < TextoASCII.size(); j++){
		for(unsigned int k = 0; k < TextoASCII[j].size(); k++){
			// convertendo de ASCII pra char
			if(TextoASCII[j][k] == -1){
				TextoDecifrado.push_back(' ');
				continue;
			}
			TextoDecifrado.push_back(static_cast<char>(TextoASCII[j][k]));
		}
		TextoDecifrado += "\n";
	}

	// escrevendo no arquivo decifrado
	ArquivoDecifrado << TextoDecifrado;
	ArquivoDecifrado.close();
	cout << "Arquivo Descriptografado salvo em " << OutFILENAME << endl;
}