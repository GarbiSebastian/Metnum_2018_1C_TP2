import fileinput
import numpy
import Gnuplot

sujetos = 41
casos = 4

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
g.xlabel("Sujetos")
g.ylabel("Resultados")

#g("set terminal png giant font 'Helvetica' 16")
g("set terminal png size 1000, 500")
g("set key below")

g("set grid y")

g("set style data histograms")
g("set style histogram rowstacked")
g("set boxwidth 0.5")
g("set style fill solid 1.0 border -1")

g("set ytics 10 nomirror")
g("set yrange [0:100]")
g("set ytics 10")

g("set xtics 1")
#g("set xtic 1")
xtics=", ".join(["'"+str(i+1)+"' "+str(i) for i in range(sujetos)])
#print xtics

g("set xtics("+xtics+")")


g("set xrange [-1:41]")
#g("xspan = GPVAL_DATA_X_MAX - GPVAL_DATA_X_MIN")
g("xequiv=100")


x1=range(sujetos)
xlabels=[i+1 for i in x1]
y1=[ (float(datos(i,tipo=TP))/x_sujetos[i])*100 for i in x1]
y2=[ (float(datos(i,tipo=FP))/(total- x_sujetos[i]))*100 for i in x1]
y3=[ (float(datos(i,tipo=TN))/(total- x_sujetos[i]))*100 for i in x1]
y4=[ (float(datos(i,tipo=FN))/x_sujetos[i])*100 for i in x1]

"""print x1
print x_sujetos
print y1
print y2
print y3
print y4"""

d1 = Gnuplot.Data(xlabels,y1,using="2",title="Positivos correctos")
d2 = Gnuplot.Data(xlabels,y2,using="2",title="Positivos incorrectos")
d3 = Gnuplot.Data(xlabels,y3,using="2",title="Negativos correctos")
d4 = Gnuplot.Data(xlabels,y4,using="2",title="Negativos incorrectos")

g("set output 'resultados_TP_FN.png'")
g.plot(d1,d4)
g("set output 'resultados_FP_TN.png'")
g.plot(d2,d3)
del g
