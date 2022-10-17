from statistics import fmean, stdev
from matplotlib import pyplot
import os
import csv

def parse():
    
    dirname = os.path.dirname(__file__)
    path    = os.path.join(dirname,"outputs/")

    # criando um dict pra cada conjunto de resultados
    # dict é indexado pela qtd de threads que executaram
    mandelbrotOMP  = dict()
    mandelbrotMPI = dict()
    for i in range(10):
        mandelbrotOMP[i] = []
        mandelbrotMPI[i] = []

    # extraindo os resultados
    for i in range(10):
        with open(path + "mandelbrotOMP"+str(i)+".txt",'r') as f:
            time = f.readline()
            time = time[:-2]
            mandelbrotOMP[i].append(float(time))
        with open(path + "mandelbrotMPI"+str(i)+".txt",'r') as f:
            time = f.readline()
            mandelbrotMPI[i].append(float(time))

    return (mandelbrotOMP, mandelbrotMPI)

def plot_times(OMP:list, MPI:list):

    pyplot.plot(list(range(0,10)),OMP,label="OMP")
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
    OMP, MPI = parse()

    # calculando as médias
    # fmean é uma função padrão que calcula a média em uma lista de floats
    mediaOMP   = fmean(flatten(list(OMP.values())))
    desviosOMP = stdev(flatten(list(OMP.values())))

    mediaMPI   = fmean(flatten(list(MPI.values())))
    desviosMPI = stdev(flatten(list(MPI.values())))

    print("Tempos OMP:")
    for v in flatten(list(OMP.values())):
        print(v, end=" ")
    print()
    print("Média OMP =", mediaOMP)
    print("Desvio Padrão OMP =", desviosOMP)

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
    plot_times(flatten(list(OMP.values())), flatten(list(MPI.values())))

    # exportando para csv
    # descomente a linha abaixo para gerar um .csv com os dados das execuções
    # to_csv(list(OMP.values()), list(MPI.values()))

if __name__ == "__main__":
    main()
