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
positives = [0 for i in range(sujetos)]
#negatives = [0 for i in range(sujetos)]

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
    positives[obtenido]+=1
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

def gBars(sujetos,xlabel="Sujetos",ylabel="Resultados",title="Resultados"):
    g = Gnuplot.Gnuplot()
    g.title(title)
    g.xlabel(xlabel)
    g.ylabel(ylabel)
    g("set terminal png size 1000, 500")
    g("set key below")
    g("set grid y")
    g("set style data histograms")
    g("set style histogram rowstacked")
    g("set boxwidth 1")
    g("set style fill solid 1.0 border -1")
    g("set ytics 10 nomirror")
    #g("set yrange [0:100]")
    g("set ytics 10")
    g("set xtics 1")
    xtics=", ".join(["'"+str(i+1)+"' "+str(i) for i in range(sujetos)])
    g("set xtics("+xtics+")")
    g("set xrange [-1:"+str(sujetos)+"]")
    g("xequiv=100")
    return g


def plotRecall(sujetos,cantidades):
    g = gBars(sujetos,title="Recall")
    x=range(sujetos)
    y1=[ (float(datos(i,tipo=TP))/cantidades[i])*100 for i in x]
    #y2=[ (float(datos(i,tipo=FN))/cantidades[i])*100 for i in x]
    d1 = Gnuplot.Data(x,y1,using="2",title="Recall(tp/tp+fn)")
    #d2 = Gnuplot.Data(x,y2,using="2",title="Resto(fn/tp+fn)")
    g("set output 'recall.png'")
    #g.plot(d1,d2)
    g.plot(d1)
    del g

def plotPresicion(sujetos,cantidades):
    g = gBars(sujetos,title="Presicion")
    x=range(sujetos)
    y1=[ (float(datos(i,tipo=TP))/cantidades[i])*100 for i in x]
    #y4=[ (float(datos(i,tipo=FN))/x_sujetos[i])*100 for i in x]
    d1 = Gnuplot.Data(x,y1,using="2",title="Presicion(tp/tp+fp)")
    #d2 = Gnuplot.Data(x,y2,using="2",title="Resto(fn/tp+fn)")
    g("set output 'presicion.png'")
    g.plot(d1)
    del g

def mediaArmonica():
    print 1

plotRecall(sujetos,cantidades=x_sujetos)
plotPresicion(sujetos,cantidades=positives)

"""y1=[ (float(datos(i,tipo=TP))/x_sujetos[i])*100 for i in x]
y2=[ (float(datos(i,tipo=FP))/(total- x_sujetos[i]))*100 for i in x]
y3=[ (float(datos(i,tipo=TN))/(total- x_sujetos[i]))*100 for i in x]
y4=[ (float(datos(i,tipo=FN))/x_sujetos[i])*100 for i in x]"""

"""d1 = Gnuplot.Data(x,y1,using="2",title="Positivos correctos")
d2 = Gnuplot.Data(x,y2,using="2",title="Positivos incorrectos")
d3 = Gnuplot.Data(x,y3,using="2",title="Negativos correctos")
d4 = Gnuplot.Data(x,y4,using="2",title="Negativos incorrectos")"""

#g("set output 'resultados_TP_FN.png'")
#g.plot(d1,d4)
#g("set output 'resultados_TN_FP.png'")
#g.plot(d3,d2)
#del g
