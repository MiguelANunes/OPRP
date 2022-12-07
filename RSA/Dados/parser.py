from statistics import fmean, stdev
from matplotlib import pyplot
import os
import csv

# Sessão Comparável: 2 até 39 bits
# Isto é, tanto paralelo quanto sequencial fizeram até ai

def parse_sequencial():
    
    dirname = os.path.dirname(__file__)
    path    = os.path.join(dirname,"Sequencial/")

    # criando um dict pra cada conjunto de resultados
    # dict é indexado pela qtd de threads que executaram
    teste1 = dict()
    teste2 = dict()
    teste3 = dict()
    teste4 = dict()
    teste5 = dict()

    for i in range(8,34,2):
        teste1[i] = []
        teste2[i] = []
        teste3[i] = []
        teste4[i] = []
        teste5[i] = []

    for i in range(32,40):
        teste1[i] = []
        teste2[i] = []
        teste3[i] = []
        teste4[i] = []
        teste5[i] = []

    teste3[40] = []
    teste4[40] = []
    teste4[41] = []
    
    # extraindo os resultados
    for i in range(8,34,2):
        with open(path + f"teste1/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste1[i].append(float(time))
        with open(path + f"teste2/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste2[i].append(float(time))
        with open(path + f"teste3/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste3[i].append(float(time))
        with open(path + f"teste4/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste4[i].append(float(time))
        with open(path + f"teste5/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste5[i].append(float(time))
    
    for i in range(32,40):
        with open(path + f"teste1/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste1[i].append(float(time))
        with open(path + f"teste2/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste2[i].append(float(time))
        with open(path + f"teste3/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste3[i].append(float(time))
        with open(path + f"teste4/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste4[i].append(float(time))
        with open(path + f"teste5/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste5[i].append(float(time))

    with open(path + f"teste3/tempos-40-bits.txt",'r') as f:
        time = f.readline()
        teste3[40].append(float(time))

    with open(path + f"teste4/tempos-40-bits.txt",'r') as f:
        time = f.readline()
        teste4[40].append(float(time))

    with open(path + f"teste4/tempos-41-bits.txt",'r') as f:
        time = f.readline()
        teste4[41].append(float(time))

    return (teste1,teste2,teste3,teste4,teste5)

def parse_paralelo():
    
    dirname = os.path.dirname(__file__)
    path    = os.path.join(dirname,"Paralelo/")

    # criando um dict pra cada conjunto de resultados
    # dict é indexado pela qtd de threads que executaram
    teste1 = dict()
    teste2 = dict()
    teste3 = dict()
    teste4 = dict()
    teste5 = dict()

    for i in range(8,34,2):
        teste1[i] = []
        teste2[i] = []
        teste3[i] = []
        teste4[i] = []
        teste5[i] = []

    for i in range(32,46):
        teste1[i] = []
        teste2[i] = []
        teste3[i] = []
        teste4[i] = []
        teste5[i] = []

    for i in range(46,51):
        teste1[i] = []
    
    teste2[46] = []
    teste2[47] = []
    teste3[46] = []

    # extraindo os resultados
    for i in range(8,34,2):
        with open(path + f"teste1/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste1[i].append(float(time))
        with open(path + f"teste2/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste2[i].append(float(time))
        with open(path + f"teste3/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste3[i].append(float(time))
        with open(path + f"teste4/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste4[i].append(float(time))
        with open(path + f"teste5/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste5[i].append(float(time))
    
    for i in range(32,46):
        with open(path + f"teste1/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste1[i].append(float(time))
        with open(path + f"teste2/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste2[i].append(float(time))
        with open(path + f"teste3/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste3[i].append(float(time))
        with open(path + f"teste4/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste4[i].append(float(time))
        with open(path + f"teste5/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste5[i].append(float(time))

    for i in range(46,51):
        with open(path + f"teste1/tempos-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste1[i].append(float(time))

    with open(path + f"teste2/tempos-46-bits.txt",'r') as f:
        time = f.readline()
        teste2[46].append(float(time))

    with open(path + f"teste2/tempos-47-bits.txt",'r') as f:
        time = f.readline()
        teste2[47].append(float(time))

    with open(path + f"teste3/tempos-46-bits.txt",'r') as f:
        time = f.readline()
        teste3[46].append(float(time))

    return (teste1,teste2,teste3,teste4,teste5)

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

# def to_csv(OMP, dynamic, guided):
#     """
#     Exporta os dados da execução para um arquivo .csv
#     """

#     campos = ["Execução "+str(n) for n in range(10)]
#     campos.insert(0,"Threads")

#     with open("OMP.csv", 'w') as f:
#         writer = csv.writer(f)
#         thread = 1
#         writer.writerow(campos)
#         for l in OMP:
#             temp = [x for x in l]
#             temp.insert(0, thread)
#             writer.writerow(temp)
#             thread += 1

#     with open("dynamic.csv", 'w') as f:
#         writer = csv.writer(f)
#         thread = 1
#         writer.writerow(campos)
#         for l in dynamic:
#             temp = [x for x in l]
#             temp.insert(0, thread)
#             writer.writerow(temp)
#             thread += 1
    
#     with open("guided.csv", 'w') as f:
#         writer = csv.writer(f)
#         thread = 1
#         writer.writerow(campos)
#         for l in guided:
#             temp = [x for x in l]
#             temp.insert(0, thread)
#             writer.writerow(temp)
#             thread += 1

def flatten(l):
    return [item for sublist in l for item in sublist]

def comparavel(l1, l2, l3, l4, l5):
    # retornando a sessão comparável das listas de tempos
    # 2 - 32 step=2, 32 - 39 step = 1 tem 21 itens
    return (x[:21] for x in (l1,l2,l3,l4,l5))

def comparavel1(data:dict):
    newData = dict()

    limite = 21
    for k in data:
        newData[k] = data[k]
        limite -= 1
        if limite == 0: break
    return newData

def media_desvio(dados:list):
    # fmean é uma função padrão que calcula a média em uma lista de floats
    media  = fmean(dados)
    desvio = stdev(dados)
    return (media, desvio)

def main():

    # obtendo os valores de tempo/thread
    Seq1, Seq2, Seq3, Seq4, Seq5 = parse_sequencial()
    Par1, Par2, Par3, Par4, Par5 = parse_paralelo()

    # Sessões Comparáveis:
    CompS1, CompS2, CompS3, CompS4, CompS5 = comparavel(Seq1, Seq2, Seq3, Seq4, Seq5)
    CompP1, CompP2, CompP3, CompP4, CompP5 = comparavel(Par1, Par2, Par3, Par4, Par5)

    # ERRADO: DEVERIA ESTAR CALCULANDO AS MÉDIAS/DESVIOS DOS CASOS COM MESMO TOTAL DE BITS
    # OU SEJA, MÉDIA DO TESTE1/2/3/4/5 P/ 2 BITS, DAÍ MEDIA DO TESTE1/2/3/4/5 P/ 4 BITS, ...
    # COMPARAR ISSO PARA O CASO PARALELO COM O MESMO TOTAL DE BITS PARA OBTER SPEEDUP E EFICIENCIA

    # Calculando as médias e desvios para SpeedUp/Eficiência
    MediaCompS1, DesvioCompS1 = media_desvio(CompS1.values())
    MediaCompS2, DesvioCompS2 = media_desvio(CompS2.values())
    MediaCompS3, DesvioCompS3 = media_desvio(CompS3.values())
    MediaCompS4, DesvioCompS4 = media_desvio(CompS4.values())
    MediaCompS5, DesvioCompS5 = media_desvio(CompS5.values())

    MediaCompP1, DesvioCompP1 = media_desvio(CompP1.values())
    MediaCompP2, DesvioCompP2 = media_desvio(CompP2.values())
    MediaCompP3, DesvioCompP3 = media_desvio(CompP3.values())
    MediaCompP4, DesvioCompP4 = media_desvio(CompP4.values())
    MediaCompP5, DesvioCompP5 = media_desvio(CompP5.values())

    # Calculando as médias e desvios gerais
    MediaS1, DesvioS1 = media_desvio(Seq1.values())
    MediaS2, DesvioS2 = media_desvio(Seq2.values())
    MediaS3, DesvioS3 = media_desvio(Seq3.values())
    MediaS4, DesvioS4 = media_desvio(Seq4.values())
    MediaS5, DesvioS5 = media_desvio(Seq5.values())

    MediaP1, DesvioP1 = media_desvio(Par1.values())
    MediaP2, DesvioP2 = media_desvio(Par2.values())
    MediaP3, DesvioP3 = media_desvio(Par3.values())
    MediaP4, DesvioP4 = media_desvio(Par4.values())
    MediaP5, DesvioP5 = media_desvio(Par5.values())

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
