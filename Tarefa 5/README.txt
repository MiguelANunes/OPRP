Instruções de Execução:
	Para Executar os testes, execute o comando
		chmod +x auto_tester.sh
	Então:
		./auto_tester.sh
	Isso iniciará uma leva de 10 testes, com as duas versões do algoritmo de mandelbrot e o algoritmo de
	multiplicação de matrizes, de 1 até 8 threads
	Para alterar os inputs ou número de threads, edite o arquivo input_generator.py
	Ao final da execução dos testes, execute o comando
		python3 parser.py
	Isso irá analisar os dados e gerará os gráficos que estão presentes no relatório
