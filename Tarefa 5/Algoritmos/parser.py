from statistics import fmean, stdev
from matplotlib import pyplot
import os
import csv

def parse():
    
    dirname = os.path.dirname(__file__)
    path    = os.path.join(dirname,"outputs/")

    # criando um dict pra cada conjunto de resultados
    # dict é indexado pela qtd de threads que executaram
    mandelResults = dict()
    matrixResults = dict()
    for i in range(1,9):
        mandelResults[i] = []
        matrixResults[i] = []

    # extraindo os resultados
    for i in range(10):
        for j in range(1,9):
            # nos arquivos de resultado há dois dados, qtd de threads e tempo de execução
            with open(path + "mandelbrot"+str(i)+str(j)+".txt",'r') as f:
                thread, time = f.readline().split(" ")
                time = time[:-2]
                mandelResults[int(thread)].append(float(time))
            with open(path + "matrix"+str(i)+str(j)+".txt",'r') as f:
                thread, time = f.readline().split(" ")
                time = time[:-2]
                matrixResults[int(thread)].append(float(time))

    return (mandelResults, matrixResults)

def plot_aceleracao(speedUpMandel:list, speedUpMatrix:list):
    """
    Função que plota o gráfico da aceleração das execuções dos algoritmos
    """

    pyplot.plot(list(range(1,9)),speedUpMandel,label="Mandelbrot")
    pyplot.plot(list(range(1,9)),speedUpMatrix,label="Matrix")

    pyplot.xlabel("Threads")
    pyplot.ylabel("Speed Up")

    pyplot.title("Aceleração")
    pyplot.legend()

    pyplot.legend(loc='best')
    pyplot.show()
    pyplot.close()

    return (speedUpMandel, speedUpMatrix)

def plot_eficiencia(eficienciaMandel:list, eficienciaMatrix:list):
    """
    Função que plota o gráfico da eficiência das execuções dos algoritmos
    """

    pyplot.plot(list(range(1,9)),eficienciaMandel,label="Mandelbrot")
    pyplot.plot(list(range(1,9)),eficienciaMatrix,label="Matrix")

    pyplot.xlabel("Threads")
    pyplot.ylabel("Eficiência")

    pyplot.title("Eficiência")
    pyplot.legend()

    pyplot.legend(loc='best')
    pyplot.show()
    pyplot.close()

def box_plot(valores, nome):

    pyplot.boxplot(valores)
    pyplot.title(f"Boxplot do Algoritmo {nome}")

    pyplot.xlabel("Qtd de Threads")
    pyplot.ylabel("Tempo de Execução")

    pyplot.show()

def to_csv(mandel:dict, matrix:dict):
    """
    Exporta os dados da execução para um arquivo .csv
    """

    campos = ["Execução "+str(n) for n in range(10)]
    campos.insert(0,"Threads")

    with open("mandelbrot.csv", 'w') as f:
        thread = 1
        writer.writerow(campos)
        for l in mandel:
            writer = csv.writer(f)
            temp = [x for x in l]
            temp.insert(0, thread)
            print(temp)
            writer.writerow(temp)
            thread += 1

    with open("matrix.csv", 'w') as f:
        thread = 1
        writer.writerow(campos)
        for l in matrix:
            writer = csv.writer(f)
            temp = [x for x in l]
            temp.insert(0, thread)
            writer.writerow(temp)
            thread += 1


def main():

    # obtendo os valores de tempo/thread
    mandel, matrix = parse()

    # calculando as médias
    # fmean é uma função padrão que calcula a média em uma lista de floats
    mediaSeqMandel   = fmean(mandel[1])
    mediaMandel      = [fmean(mandel[k]) for k in mandel]
    desviosMandel    = [stdev(mandel[k]) for k in mandel]
    speedUpMandel    = [mediaSeqMandel/paralelo for paralelo in mediaMandel]
    eficienciaMandel = [speedUpMandel[i]/(i+1) for i in range(8)]


    mediaSeqMatrix   = fmean(matrix[1])
    mediaMatrix      = [fmean(matrix[k]) for k in matrix]
    desviosMatrix    = [stdev(matrix[k]) for k in matrix]
    speedUpMatrix    = [mediaSeqMatrix/paralelo for paralelo in mediaMatrix]
    eficienciaMatrix = [speedUpMatrix[i]/(i+1) for i in range(8)]

    print("Média Mandelbrot Paralelo =", mediaMandel)
    print("Desvio Padrão Mandelbrot =", desviosMandel)
    print("SpeedUp Mandelbrot =",speedUpMandel)
    print("Eficiência Mandelbrot =",eficienciaMandel)

    print()

    print("Média Matriz Paralelo =", mediaMatrix)
    print("Desvio Padrão Matriz =", desviosMatrix)
    print("SpeedUp Matrix =",speedUpMatrix)
    print("Eficiência Matrix =",eficienciaMatrix)

    # comente a linha abaixo para gerar os gráficos
    exit()

    # plotando os gráficos
    plot_aceleracao(speedUpMandel, speedUpMatrix)
    plot_eficiencia(eficienciaMandel, eficienciaMatrix)

    # exportando para csv
    # descomente a linha abaixo para gerar um .csv com os dados das execuções
    # to_csv(list(mandel.values()), list(matrix.values()))

if __name__ == "__main__":
    main()
