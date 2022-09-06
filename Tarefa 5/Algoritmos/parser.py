from statistics import fmean, stdev
from matplotlib import pyplot
import os
import csv

def parse():
    
    dirname = os.path.dirname(__file__)
    path    = os.path.join(dirname,"outputs/")

    # criando um dict pra cada conjunto de resultados
    # dict é indexado pela qtd de threads que executaram
    mandelResults     = dict()
    matrixResults     = dict()
    mandelFreeResults = dict()
    for i in range(1,9):
        mandelResults[i] = []
        mandelFreeResults[i] = []
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
            with open(path + "mandelbrotFree"+str(i)+str(j)+".txt",'r') as f:
                thread, time = f.readline().split(" ")
                time = time[:-2]
                mandelFreeResults[int(thread)].append(float(time))

    return (mandelResults, matrixResults, mandelFreeResults)

def plot_aceleracao(speedUpMandel:list, speedUpMatrix:list, speedUpMandelFree:list):
    """
    Função que plota o gráfico da aceleração das execuções dos algoritmos
    """

    pyplot.plot(list(range(1,9)),speedUpMandel,label="Mandelbrot 1")
    pyplot.plot(list(range(1,9)),speedUpMandelFree,label="Mandelbrot 2")
    pyplot.plot(list(range(1,9)),speedUpMatrix,label="Matrix")

    pyplot.xlabel("Threads")
    pyplot.ylabel("Speed Up")

    pyplot.title("Aceleração")
    pyplot.legend()

    pyplot.legend(loc='best')
    pyplot.show()
    pyplot.close()

    return (speedUpMandel, speedUpMatrix)

def plot_eficiencia(eficienciaMandel:list, eficienciaMatrix:list, eficienciaMandelFree:list):
    """
    Função que plota o gráfico da eficiência das execuções dos algoritmos
    """

    pyplot.plot(list(range(1,9)),eficienciaMandel,label="Mandelbrot 1")
    pyplot.plot(list(range(1,9)),eficienciaMandel,label="Mandelbrot 2")
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

def to_csv(mandel, matrix, mandelFree):
    """
    Exporta os dados da execução para um arquivo .csv
    """

    campos = ["Execução "+str(n) for n in range(10)]
    campos.insert(0,"Threads")

    with open("mandelbrot.csv", 'w') as f:
        writer = csv.writer(f)
        thread = 1
        writer.writerow(campos)
        for l in mandel:
            temp = [x for x in l]
            temp.insert(0, thread)
            writer.writerow(temp)
            thread += 1

    with open("matrix.csv", 'w') as f:
        writer = csv.writer(f)
        thread = 1
        writer.writerow(campos)
        for l in matrix:
            temp = [x for x in l]
            temp.insert(0, thread)
            writer.writerow(temp)
            thread += 1
    
    with open("mandelFree.csv", 'w') as f:
        writer = csv.writer(f)
        thread = 1
        writer.writerow(campos)
        for l in mandelFree:
            temp = [x for x in l]
            temp.insert(0, thread)
            writer.writerow(temp)
            thread += 1


def main():

    # obtendo os valores de tempo/thread
    mandel, matrix, mandelFree = parse()

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

    mediaSeqMandelFree   = fmean(mandelFree[1])
    mediaMandelFree      = [fmean(mandelFree[k]) for k in mandelFree]
    desviosMandelFree    = [stdev(mandelFree[k]) for k in mandelFree]
    speedUpMandelFree    = [mediaSeqMandelFree/paralelo for paralelo in mediaMandelFree]
    eficienciaMandelFree = [speedUpMandelFree[i]/(i+1) for i in range(8)]

    print("Média Mandelbrot Paralelo =", mediaMandel)
    print("Desvio Padrão Mandelbrot =", desviosMandel)
    print("SpeedUp Mandelbrot =",speedUpMandel)
    print("Eficiência Mandelbrot =",eficienciaMandel)

    print()

    print("Média Mandelbrot c/ Free Paralelo =", mediaMandelFree)
    print("Desvio Padrão Mandelbrot c/ Free =", desviosMandelFree)
    print("SpeedUp Mandelbrot c/ Free =",speedUpMandelFree)
    print("Eficiência Mandelbrot c/ Free =",eficienciaMandelFree)

    print()

    print("Média Matriz Paralelo =", mediaMatrix)
    print("Desvio Padrão Matriz =", desviosMatrix)
    print("SpeedUp Matrix =",speedUpMatrix)
    print("Eficiência Matrix =",eficienciaMatrix)

    # comente a linha abaixo para gerar os gráficos
    # exit()

    # plotando os gráficos
    plot_aceleracao(speedUpMandel, speedUpMatrix, speedUpMandelFree)
    plot_eficiencia(eficienciaMandel, eficienciaMatrix, eficienciaMandelFree)

    # exportando para csv
    # descomente a linha abaixo para gerar um .csv com os dados das execuções
    to_csv(list(mandel.values()), list(matrix.values()), list(mandelFree.values()))

if __name__ == "__main__":
    main()
