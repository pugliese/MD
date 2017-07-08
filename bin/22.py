import matplotlib.pylab as plt
import numpy as np
import scipy.stats as sc
import sys

N = float(sys.argv[1])
rho = float(sys.argv[2])
name = "22_E_P_%d_%1.3f.txt" %(N,rho)


data = np.loadtxt(name)
Ecin = data[:,0]
E = data[:,1]
P = data[:,2]
T = 2*Ecin/(3*N)
N_T = len(T)
"""
plt.figure(1)
plt.plot(T,E/N,"r.")
plt.grid()
plt.figure(2)
plt.plot(T,P,"b.")
plt.plot(T,rho*T,"r-")
plt.plot(T,P-rho*T,"g.")
plt.grid()
plt.show()
"""
plt.plot(T,E/N,"rv--")
N = 125
name = "22_E_P_%d_%1.3f.txt" %(N,rho)
data = np.loadtxt(name)
Ecin = data[:,0]
E = data[:,1]
P = data[:,2]
T = 2*Ecin/(3*N)
plt.plot(T,E/N,"bo--")
plt.show()


def cargar(N,rho):
    name = "22_E_P_%d_%1.3f.txt" %(N,rho)
    data = np.loadtxt(name)
    Ecin = data[:,0]
    E = data[:,1]
    P = data[:,2]
    T = 2*Ecin/(3*N)
    return T,E,P

def recta(T,E):
    R = np.zeros(20)
    for i in range(2,20):
        R[i]=sc.linregress(T[:i],E[:i]).rvalue
    return R

def recta2(T,E):
    R = np.zeros(20)
    for i in range(1,19):
        R[i]=sc.linregress(T[i-1:i+2],E[i-1:i+2]).rvalue
    return R

def quiebre(T,E):
    R = recta2(T,E)
    i = np.where(np.min(R[2:19])==R)[0]
    return (T[i]+T[i+1])/2, (T[i]-T[i+1])/2

def Quiebres(rhos,N=125):
    Tcs=np.zeros((len(rhos),2))
    for i in range(len(rhos)):
        T,E,P = cargar(N,rhos[i])
        Tcs[i,:] = quiebre(T,E)
    Tcs = np.array(Tcs)
    return Tcs
        