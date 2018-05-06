import fileinput
import numpy
import Gnuplot

sujetos, casos = 41, 4;

TP=0
FP=1
TN=2
FN=3

resultados = [[0 for i in range(casos)] for y in range(sujetos)]
confusion = [[0 for i in range(sujetos)] for y in range(sujetos)]
total = 0
x_sujetos = [0 for i in range(sujetos)]

def datos(i,tipo=TP):
    return resultados[i][tipo]
#print resultados

for line in fileinput.input():
    total+=1
    item = line.split()
    real = int(item[0])-1
    obtenido = int(item[1])-1
    confusion[real][obtenido]+=1
    x_sujetos[real]+=1
    if real==obtenido:
        resultados[real][TP]+=1
    else:
        resultados[real][FN]+=1
        resultados[obtenido][FP]+=1

for i in range(sujetos):
    #print(i+1,end=' ',flush=True)
    resultados[i][TN]=total- int(total/sujetos) - resultados[i][FP]
    """for j in range(casos):
        print(resultados[i][j], end=' ', flush=True)
    print('',flush=True)"""

"""for i in range(sujetos):
    for j in range(sujetos):
        print(confusion[i][j], end=' ', flush=True)
    print('',flush=True)"""
"""x = numpy.arange (start=2, stop=120, step=8)
print(x,flush=True)"""

g = Gnuplot.Gnuplot()
g.title("Resultados")
g("set xtics 1")
g("set xrange [1:41]")

g.xlabel("Sujetos")
g.ylabel("Resultados")

x1=range(sujetos)
y1=[datos(i,tipo=TP) for i in x1]
y2=[datos(i,tipo=FP) for i in x1]
y3=[datos(i,tipo=TN)/(total- x_sujetos[i]) for i in x1]
y4=[datos(i,tipo=FN) for i in x1]
print y1
print y2
print y3
print y4
d1 = Gnuplot.Data(x1,y1,with_="boxes fill pattern 1 lc 1",title="True Positives")
d2 = Gnuplot.Data(x1,y3,with_="boxes fill pattern 2 lc 2",title="False Positives")


g.plot(d1,d2)
g.hardcopy(filename='algo.png',terminal='png')
del g
