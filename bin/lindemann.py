import matplotlib.pylab as plt
import numpy as np
import scipy as sc
from scipy.optimize import curve_fit
import sys

N = int(sys.argv[1])
rho = float(sys.argv[2])

def cargar(N,rho):
    name = "Lindemann_%d_%1.3f.txt" %(N,rho)
    data = np.loadtxt(name)
    E = data[:,0]
    T = data[:,1]
    D = data[:,2]
    return E,T,D

E,T,D = cargar(N,rho);

plt.figure(1)
plt.plot(T,D, "ro--")
plt.xlabel("Temperatura")
plt.ylabel("Lindemann")
plt.grid()

plt.figure(2)
plt.plot(E,D, "ro--")
plt.xlabel("Energia")
plt.ylabel("Lindemann")
plt.grid()

plt.figure(3)
plt.plot(T,E, "ro--")
plt.xlabel("Temperatura")
plt.ylabel("Energia")
plt.grid()

plt.show()
