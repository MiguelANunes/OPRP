from statistics import fmean, stdev
from matplotlib import pyplot
import os

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

    for i in range(8,32,2):
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
    
    # extraindo os resultados
    for i in range(8,32,2):
        with open(path + f"teste1/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste1[i] = float(time)
        with open(path + f"teste2/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste2[i] = float(time)
        with open(path + f"teste3/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste3[i] = float(time)
        with open(path + f"teste4/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste4[i] = float(time)
        with open(path + f"teste5/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste5[i] = float(time)
    
    for i in range(32,40):
        with open(path + f"teste1/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste1[i] = float(time)
        with open(path + f"teste2/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste2[i] = float(time)
        with open(path + f"teste3/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste3[i] = float(time)
        with open(path + f"teste4/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste4[i] = float(time)
        with open(path + f"teste5/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste5[i] = float(time)

    with open(path + f"teste3/tempo-40-bits.txt",'r') as f:
        time = f.readline()
        teste3[40] = float(time)

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

    for i in range(8,32,2):
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
    for i in range(8,32,2):
        with open(path + f"teste1/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste1[i] = float(time)
        with open(path + f"teste2/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste2[i] = float(time)
        with open(path + f"teste3/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste3[i] = float(time)
        with open(path + f"teste4/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste4[i] = float(time)
        with open(path + f"teste5/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste5[i] = float(time)
    
    for i in range(32,46):
        with open(path + f"teste1/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste1[i] = float(time)
        with open(path + f"teste2/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste2[i] = float(time)
        with open(path + f"teste3/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste3[i] = float(time)
        with open(path + f"teste4/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste4[i] = float(time)
        with open(path + f"teste5/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste5[i] = float(time)

    for i in range(46,51):
        with open(path + f"teste1/tempo-{i}-bits.txt",'r') as f:
            time = f.readline()
            teste1[i] = float(time)

    with open(path + f"teste2/tempo-46-bits.txt",'r') as f:
        time = f.readline()
        teste2[46] = float(time)

    with open(path + f"teste2/tempo-47-bits.txt",'r') as f:
        time = f.readline()
        teste2[47] = float(time)

    with open(path + f"teste3/tempo-46-bits.txt",'r') as f:
        time = f.readline()
        teste3[46] = float(time)

    return (teste1,teste2,teste3,teste4,teste5)

def plot_times(tempos:list, bits:list, nome:str, cor:str=None):

    pyplot.plot(bits,tempos,label=nome,color=cor)

    return

def flatten(l):
    return [item for sublist in l for item in sublist]

def comparavel(data:dict):
    newData = dict()

    limite = 20
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

def medias_desvios(dados:dict):
    medias  = dict()
    desvios = dict()

    for bits in dados:
        medias[bits]  = fmean(dados[bits])
        desvios[bits] = stdev(dados[bits])

    return (medias, desvios)

def juntar(l1:dict, l2:dict, l3:dict, l4:dict, l5:dict):
    tempo = dict()

    for i in range(8,32,2):
        tempo[i] = []
        tempo[i].append(l1[i])
        tempo[i].append(l2[i])
        tempo[i].append(l3[i])
        tempo[i].append(l4[i])
        tempo[i].append(l5[i])

    for i in range(32,40):
        tempo[i] = []
        tempo[i].append(l1[i])
        tempo[i].append(l2[i])
        tempo[i].append(l3[i])
        tempo[i].append(l4[i])
        tempo[i].append(l5[i])

    return tempo

def speed_up(mediaSeq:dict, mediaPar:dict):
    SpeedUp = dict()

    for bits in mediaSeq:
        SpeedUp[bits] = mediaSeq[bits]/mediaPar[bits]

    return SpeedUp

def eficiencia(speedup:dict):
    eficiencia = dict()

    for bits in speedup:
        eficiencia[bits] = speedup[bits]/64 # 8 processos com 8 threads
    return eficiencia

def main():

    # obtendo os valores de tempo/thread
    Seq1, Seq2, Seq3, Seq4, Seq5 = parse_sequencial()
    Par1, Par2, Par3, Par4, Par5 = parse_paralelo()

    # Sessões Comparáveis:
    CompS1 = comparavel(Seq1) 
    CompS2 = comparavel(Seq2)
    CompS3 = comparavel(Seq3)
    CompS4 = comparavel(Seq4) 
    CompS5 = comparavel(Seq5)
    CompP1 = comparavel(Par1) 
    CompP2 = comparavel(Par2)
    CompP3 = comparavel(Par3)
    CompP4 = comparavel(Par4) 
    CompP5 = comparavel(Par5)

    # Unindo os dados num único dict para facilitar processamento
    # UniaoSeq[i] = [Lista de tempo das execuções com i bits]
    UniaoSeq = juntar(CompS1, CompS2, CompS3, CompS4, CompS5)
    UniaoPar = juntar(CompP1, CompP2, CompP3, CompP4, CompP5)

    # Calculando as médias para Speed Up e Eficiência
    MediasSeq, DesvioSeq = medias_desvios(UniaoSeq)
    MediasPar, DesvioPar = medias_desvios(UniaoPar)

    SpeedUp    = speed_up(MediasSeq, MediasPar)
    Eficiencia = eficiencia(SpeedUp)

    for bits in SpeedUp:
        print(f"Execução com {bits} bits")

        print(f"\tTempo médio de 5 testes Sequenciais: {MediasSeq[bits]:.5f}")
        print(f"\t\tDesvio Padrão: {DesvioSeq[bits]:.5f}")

        print(f"\tTempo médio de 5 testes Paralelos: {MediasPar[bits]:.5f}")
        print(f"\t\tDesvio Padrão: {DesvioPar[bits]:.5f}")

        print(f"\tSpeed Up de: {SpeedUp[bits]:.5f}")
        print(f"\tEficiência de: {Eficiencia[bits]*100:.5f}%")
        # print(f"bits={bits}")
        # print(f"{MediasSeq[bits]}")
        # print(f"{DesvioSeq[bits]}")
        # print(f"{MediasPar[bits]}")
        # print(f"{DesvioPar[bits]}")
        # print(f"{SpeedUp[bits]}")
        # print(f"{Eficiencia[bits]}")
        # print()


    # plot_times(list(Seq1.values()), list(Seq1.keys()), "Sequencial Teste 1")
    # plot_times(list(Seq2.values()), list(Seq2.keys()), "Sequencial Teste 2")
    # plot_times(list(Seq3.values()), list(Seq3.keys()), "Sequencial Teste 3")
    # plot_times(list(Seq4.values()), list(Seq4.keys()), "Sequencial Teste 4")
    # plot_times(list(Seq5.values()), list(Seq5.keys()), "Sequencial Teste 5")

    # pyplot.xlabel("Qtd de Bits da Chave")
    # pyplot.ylabel("Tempo (segundos)")

    # pyplot.title("Tempo de Execução Sequencial")
    # pyplot.legend()

    # pyplot.legend(loc='best')
    # pyplot.show()
    # pyplot.close()

    # times1 = list(Par1.values())[:len(list(Par1.values()))-5]
    # times2 = list(Par2.values())[:len(list(Par2.values()))-2]
    # times3 = list(Par3.values())[:len(list(Par3.values()))-1]

    # len1 = list(Par1.keys())[:len(list(Par1.keys()))-5]
    # len2 = list(Par2.keys())[:len(list(Par2.keys()))-2]
    # len3 = list(Par3.keys())[:len(list(Par3.keys()))-1]

    # plot_times(list(Par1.values()), list(Par1.keys()), "Paralelo Teste 1")
    # plot_times(list(Par2.values()), list(Par2.keys()), "Paralelo Teste 2")
    # plot_times(list(Par3.values()), list(Par3.keys()), "Paralelo Teste 3")
    # plot_times(list(Par4.values()), list(Par4.keys()), "Paralelo Teste 4")
    # plot_times(list(Par5.values()), list(Par5.keys()), "Paralelo Teste 5")

    # pyplot.xlabel("Qtd de Bits da Chave")
    # pyplot.ylabel("Tempo (segundos)")

    # pyplot.title("Tempo de Execução Paralelo")
    # pyplot.legend()

    # pyplot.legend(loc='best')
    # pyplot.show()
    # pyplot.close()

if __name__ == "__main__":
    main()
