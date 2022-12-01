Instruções p/ execução:
	"make" ou "make all" p/ compilar os arquivos
	"make run" ou "./main" p/ executar
		adicionalmente, pode-se passar dois argumentos adicionais p/ este comandos
		"make run BITS=x" ou "./main x" roda o programa com x bits e pula o prompt para
		entrar com o número de bits
		"make run BITS=x ARQ=nome" ou "./main x nome" roda o programa com x bits e com nome de arquivo
		"nome", pulando o prompt para entrar com o número de bits e nome do arquivo.
	"make clean" apaga os aquivos .o o executável "main" e os arquivos criptografados e descriptografados