import matplotlib.pylab as plt
import numpy as np
import sys

rho = float(sys.argv[1])
name = "2_E_P_%1.3f.txt" %rho
N=125
N_T = 300

data = np.loadtxt(name)
Ecin = data[:,0]
E = data[:,1]
P = data[:,2]
Eo = np.median(E)
DE = (max(E)-min(E))/10
Ecin2 = Ecin.reshape((len(Ecin)/N_T,N_T))
E2 = E.reshape((len(E)/N_T,N_T))
P2 = P.reshape((len(Ecin)/N_T,N_T))
"""
plt.figure(1)
plt.plot(E,Ecin*2/(3*N), "r.")
plt.title("T(E)")
plt.figure(2)
plt.plot(Ecin*2/(3*N),P, "b.")
plt.plot(Ecin*2/(3*N),rho*Ecin*2/(3*N), "r-")
plt.title("P(T)")
plt.figure(3)
A=[]
for i in range(len(E)):
    if(abs(E[i]-Eo)<DE):
        A.append(Ecin[i])
plt.hist(A)
name = "Histograma de T a E="+ str(Eo)
plt.title(name)
plt.figure(4)
plt.plot(np.std(Ecin2,axis=1)*2/(3*N), "ro")
plt.title("Desvio Estandar Temperatura")
plt.figure(5)
plt.plot(np.std(P2,axis=1), "bo")
plt.title("Desvio Estandar Presion")
plt.show()
"""

plt.figure(1)
plt.plot(np.mean(Ecin2,axis=1)*2/(3*N),np.mean(E2,axis=1)/N,"r.--")
plt.xlabel("T")
plt.figure(2)
plt.plot(np.mean(Ecin2,axis=1)*2/(3*N),np.mean(P2,axis=1), "b.--")
plt.plot(np.mean(Ecin2,axis=1)*2/(3*N),rho*np.mean(Ecin2,axis=1)*2/(3*N), "r-")
plt.show()
