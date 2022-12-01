from statistics import fmean, stdev
from matplotlib import pyplot
import os
import csv

def parse():
    
    dirname = os.path.dirname(__file__)
    path    = os.path.join(dirname,"outputs/")

    # criando um dict pra cada conjunto de resultados
    # dict é indexado pela qtd de threads que executaram
    mandelbrotMPI  = dict()
    mandelbrotOMP1 = dict()
    mandelbrotOMP2 = dict()
    mandelbrotOMP4 = dict()
    for i in range(10):
        mandelbrotMPI[i]  = []
        mandelbrotOMP1[i] = []
        mandelbrotOMP2[i] = []
        mandelbrotOMP4[i] = []

    # extraindo os resultados
    for i in range(10):
        with open(path + "mandelbrotMPI"+str(i)+".txt",'r') as f:
            time = f.readline()
            mandelbrotMPI[i].append(float(time))
        with open(path + "mandelbrotOMP-ens1-"+str(i)+".txt",'r') as f:
            time = f.readline()
            mandelbrotOMP1[i].append(float(time))
        with open(path + "mandelbrotOMP-ens2-"+str(i)+".txt",'r') as f:
            time = f.readline()
            mandelbrotOMP2[i].append(float(time))
        with open(path + "mandelbrotOMP-ens4-"+str(i)+".txt",'r') as f:
            time = f.readline()
            mandelbrotOMP4[i].append(float(time))

    return (mandelbrotMPI, mandelbrotOMP1, mandelbrotOMP2, mandelbrotOMP4)

def plot_times(OMP1:list, OMP2:list, OMP4:list, MPI:list):

    pyplot.plot(list(range(0,10)),OMP1,label="OMP ens1")
    pyplot.plot(list(range(0,10)),OMP2,label="OMP ens2")
    pyplot.plot(list(range(0,10)),OMP4,label="OMP ens4")
    pyplot.plot(list(range(0,10)),MPI,label="MPI")

    pyplot.xlabel("Execução")
    pyplot.ylabel("Tempo (segundos)")

    pyplot.title("Tempo de Execução")
    pyplot.legend()

    pyplot.legend(loc='best')
    pyplot.show()
    pyplot.close()

    return

def plot_aceleracao(speedUpOMP:list, speedUpDynamic:list, speedUpGuided:list, speedUpPThreads:list):
    """
    Função que plota o gráfico da aceleração das execuções dos algoritmos
    """

    pyplot.plot(list(range(1,9)),speedUpOMP,label="OMP OMP")
    pyplot.plot(list(range(1,9)),speedUpGuided,label="OMP Guided")
    pyplot.plot(list(range(1,9)),speedUpDynamic,label="OMP Dynamic")
    pyplot.plot(list(range(1,9)),speedUpPThreads,label="Pthreads")
    pyplot.plot(list(range(1,9)),list(range(1,9)),label="Ideal")

    pyplot.xlabel("Threads")
    pyplot.ylabel("Speed Up")

    pyplot.title("Aceleração")
    pyplot.legend()

    pyplot.legend(loc='best')
    pyplot.show()
    pyplot.close()

    return

def plot_eficiencia(eficienciaOMP:list, eficienciaDynamic:list, eficienciaGuided:list, eficienciaPThreads:list):
    """
    Função que plota o gráfico da eficiência das execuções dos algoritmos
    """

    pyplot.plot(list(range(1,9)),eficienciaOMP,label="OMP OMP")
    pyplot.plot(list(range(1,9)),eficienciaGuided,label="OMP Guided")
    pyplot.plot(list(range(1,9)),eficienciaDynamic,label="OMP Dynamic")
    pyplot.plot(list(range(1,9)),eficienciaPThreads,label="Pthreads")
    pyplot.plot(list(range(1,9)),list(range(1,9)),label="Ideal")

    pyplot.xlabel("Threads")
    pyplot.ylabel("Eficiência")

    pyplot.title("Eficiência")
    pyplot.legend()

    pyplot.legend(loc='best')
    pyplot.show()
    pyplot.close()

def to_csv(OMP, dynamic, guided):
    """
    Exporta os dados da execução para um arquivo .csv
    """

    campos = ["Execução "+str(n) for n in range(10)]
    campos.insert(0,"Threads")

    with open("OMP.csv", 'w') as f:
        writer = csv.writer(f)
        thread = 1
        writer.writerow(campos)
        for l in OMP:
            temp = [x for x in l]
            temp.insert(0, thread)
            writer.writerow(temp)
            thread += 1

    with open("dynamic.csv", 'w') as f:
        writer = csv.writer(f)
        thread = 1
        writer.writerow(campos)
        for l in dynamic:
            temp = [x for x in l]
            temp.insert(0, thread)
            writer.writerow(temp)
            thread += 1
    
    with open("guided.csv", 'w') as f:
        writer = csv.writer(f)
        thread = 1
        writer.writerow(campos)
        for l in guided:
            temp = [x for x in l]
            temp.insert(0, thread)
            writer.writerow(temp)
            thread += 1

def flatten(l):
    return [item for sublist in l for item in sublist]

def main():

    # obtendo os valores de tempo/thread
    MPI, OMP1, OMP2, OMP4 = parse()

    # calculando as médias
    # fmean é uma função padrão que calcula a média em uma lista de floats
    mediaMPI   = fmean(flatten(list(MPI.values())))
    desviosMPI = stdev(flatten(list(MPI.values())))

    mediaOMP1   = fmean(flatten(list(OMP1.values())))
    desviosOMP1 = stdev(flatten(list(OMP1.values())))

    mediaOMP2   = fmean(flatten(list(OMP2.values())))
    desviosOMP2 = stdev(flatten(list(OMP2.values())))

    mediaOMP4   = fmean(flatten(list(OMP4.values())))
    desviosOMP4 = stdev(flatten(list(OMP4.values())))

    print("Tempos OMP na ens1:")
    for v in flatten(list(OMP1.values())):
        print(v, end=" ")
    print()
    print("Média =", mediaOMP1)
    print("Desvio Padrão =", desviosOMP1)

    print()

    print("Tempos OMP na ens2:")
    for v in flatten(list(OMP2.values())):
        print(v, end=" ")
    print()
    print("Média =", mediaOMP2)
    print("Desvio Padrão =", desviosOMP2)

    print()

    print("Tempos OMP na ens4:")
    for v in flatten(list(OMP4.values())):
        print(v, end=" ")
    print()
    print("Média =", mediaOMP4)
    print("Desvio Padrão =", desviosOMP4)

    print()

    print("Tempos MPI:")
    for v in flatten(list(MPI.values())):
        print(v, end=" ")
    print()
    print("Média MPI =", mediaMPI)
    print("Desvio Padrão MPI =", desviosMPI)

    # comente a linha abaixo para gerar os gráficos
    # exit()

    # plotando os gráficos
    plot_times(flatten(list(OMP1.values())), flatten(list(OMP2.values())), flatten(list(OMP4.values())), flatten(list(MPI.values())))

    # exportando para csv
    # descomente a linha abaixo para gerar um .csv com os dados das execuções
    # to_csv(list(OMP.values()), list(MPI.values()))

if __name__ == "__main__":
    main()
