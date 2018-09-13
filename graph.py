import matplotlib.pyplot as plt
import csv

T=[]
Ls=[]
Rs=[]
xg=[]

col=0
readCSV=csv.reader(open("result.csv","r"), delimiter=';')
for row in readCSV:
    if(col==0):
        col=col+1
    else:
        T.append(float(row[0]))
        Ls.append(float(row[1]))
        Rs.append(float(row[2]))
        xg.append(float(row[3]))
plt.plot(T,xg)
plt.show()
