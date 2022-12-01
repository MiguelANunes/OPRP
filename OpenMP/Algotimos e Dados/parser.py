from statistics import fmean, stdev
from matplotlib import pyplot
import os
import csv

def parseOld():
    
    dirname = os.path.dirname(__file__)
    path    = os.path.join(dirname,"oldOutputs/")

    # criando um dict pra cada conjunto de resultados
    # dict é indexado pela qtd de threads que executaram
    mandelResults     = dict()
    for i in range(1,9):
        mandelResults[i] = []

    # extraindo os resultados
    for i in range(10):
        for j in range(1,9):
            # nos arquivos de resultado há dois dados, qtd de threads e tempo de execução
            with open(path + "mandelbrot"+str(i)+str(j)+".txt",'r') as f:
                thread, time = f.readline().split(" ")
                time = time[:-2]
                mandelResults[int(thread)].append(float(time))

    return mandelResults

def parse():
    
    dirname = os.path.dirname(__file__)
    path    = os.path.join(dirname,"outputs/")

    # criando um dict pra cada conjunto de resultados
    # dict é indexado pela qtd de threads que executaram
    mandelbrotOMPStatic  = dict()
    mandelbrotOMPDynamic = dict()
    mandelbrotOMPGuided  = dict()
    for i in range(1,9):
        mandelbrotOMPGuided[i]  = []
        mandelbrotOMPStatic[i]  = []
        mandelbrotOMPDynamic[i] = []

    # extraindo os resultados
    for i in range(10):
        for j in range(1,9):
            # nos arquivos de resultado há dois dados, qtd de threads e tempo de execução
            with open(path + "mandelbrotOMPGuided"+str(i)+str(j)+".txt",'r') as f:
                thread, time = f.readline().split(" ")
                time = time[:-2]
                mandelbrotOMPGuided[int(thread)].append(float(time))
            with open(path + "mandelbrotOMPStatic"+str(i)+str(j)+".txt",'r') as f:
                thread, time = f.readline().split(" ")
                time = time[:-2]
                mandelbrotOMPStatic[int(thread)].append(float(time))
            with open(path + "mandelbrotOMPDynamic"+str(i)+str(j)+".txt",'r') as f:
                thread, time = f.readline().split(" ")
                time = time[:-2]
                mandelbrotOMPDynamic[int(thread)].append(float(time))

    return (mandelbrotOMPStatic, mandelbrotOMPDynamic, mandelbrotOMPGuided)

def plot_times(Static:list, Dynamic:list, Guided:list, Threads:list):

    pyplot.plot(list(range(0,80)),Static,label="OMP Static")
    pyplot.plot(list(range(0,80)),Guided,label="OMP Guided")
    pyplot.plot(list(range(0,80)),Dynamic,label="OMP Dynamic")
    pyplot.plot(list(range(0,80)),Threads,label="Pthreads")

    pyplot.xlabel("Execução")
    pyplot.ylabel("Tempo (segundos)")

    pyplot.title("Tempo de Execução")
    pyplot.legend()

    pyplot.legend(loc='best')
    pyplot.show()
    pyplot.close()

    return

def plot_aceleracao(speedUpStatic:list, speedUpDynamic:list, speedUpGuided:list, speedUpPThreads:list):
    """
    Função que plota o gráfico da aceleração das execuções dos algoritmos
    """

    pyplot.plot(list(range(1,9)),speedUpStatic,label="OMP Static")
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

def plot_eficiencia(eficienciaStatic:list, eficienciaDynamic:list, eficienciaGuided:list, eficienciaPThreads:list):
    """
    Função que plota o gráfico da eficiência das execuções dos algoritmos
    """

    pyplot.plot(list(range(1,9)),eficienciaStatic,label="OMP Static")
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

def to_csv(static, dynamic, guided):
    """
    Exporta os dados da execução para um arquivo .csv
    """

    campos = ["Execução "+str(n) for n in range(10)]
    campos.insert(0,"Threads")

    with open("static.csv", 'w') as f:
        writer = csv.writer(f)
        thread = 1
        writer.writerow(campos)
        for l in static:
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
    static, guided, dynamic = parse()
    threads = parseOld()

    # calculando as médias
    # fmean é uma função padrão que calcula a média em uma lista de floats
    mediaSeqStatic   = fmean(static[1])
    mediaStatic      = [fmean(static[k]) for k in static]
    desviosStatic    = [stdev(static[k]) for k in static]
    speedUpStatic    = [mediaSeqStatic/paralelo for paralelo in mediaStatic]
    eficienciaStatic = [speedUpStatic[i]/(i+1) for i in range(8)]

    mediaSeqGuided   = fmean(guided[1])
    mediaGuided      = [fmean(guided[k]) for k in guided]
    desviosGuided    = [stdev(guided[k]) for k in guided]
    speedUpGuided    = [mediaSeqGuided/paralelo for paralelo in mediaGuided]
    eficienciaGuided = [speedUpGuided[i]/(i+1) for i in range(8)]

    mediaSeqDynamic   = fmean(dynamic[1])
    mediaDynamic      = [fmean(dynamic[k]) for k in dynamic]
    desviosDynamic    = [stdev(dynamic[k]) for k in dynamic]
    speedUpDynamic    = [mediaSeqDynamic/paralelo for paralelo in mediaDynamic]
    eficienciaDynamic = [speedUpDynamic[i]/(i+1) for i in range(8)]

    mediaSeqThreads   = fmean(threads[1])
    mediaThreads      = [fmean(threads[k]) for k in threads]
    desviosThreads    = [stdev(threads[k]) for k in threads]
    speedUpThreads    = [mediaSeqThreads/paralelo for paralelo in mediaThreads]
    eficienciaThreads = [speedUpThreads[i]/(i+1) for i in range(8)]

    print("Média OMP Static =", mediaStatic)
    print("Desvio Padrão OMP Static =", desviosStatic)
    print("SpeedUp OMP Static =",speedUpStatic)
    print("Eficiência OMP Static =",eficienciaStatic)

    print()

    print("Média OMP Dynamic =", mediaDynamic)
    print("Desvio Padrão OMP Dynamic =", desviosDynamic)
    print("SpeedUp OMP Dynamic =",speedUpDynamic)
    print("Eficiência OMP Dynamic =",eficienciaDynamic)

    print()

    print("Média OMP Guided =", mediaGuided)
    print("Desvio Padrão OMP Guided =", desviosGuided)
    print("SpeedUp OMP Guided =",speedUpGuided)
    print("Eficiência OMP Guided =",eficienciaGuided)

    print()

    print("Média Threads =", mediaThreads)
    print("Desvio Padrão Threads =", desviosThreads)
    print("SpeedUp Threads =",speedUpThreads)
    print("Eficiência Threads =",eficienciaThreads)

    # comente a linha abaixo para gerar os gráficos
    # exit()

    # plotando os gráficos
    plot_times(flatten(list(static.values())), flatten(list(dynamic.values())), flatten(list(guided.values())), flatten(list(threads.values())))
    plot_aceleracao(speedUpStatic, speedUpDynamic, speedUpGuided, speedUpThreads)
    plot_eficiencia(eficienciaStatic, eficienciaDynamic, eficienciaGuided, eficienciaThreads)

    # exportando para csv
    # descomente a linha abaixo para gerar um .csv com os dados das execuções
    # to_csv(list(static.values()), list(dynamic.values()), list(guided.values()))

if __name__ == "__main__":
    main()
