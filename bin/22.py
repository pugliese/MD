import matplotlib.pylab as plt
import numpy as np
import sys

rho = float(sys.argv[1])
name = "22_E_P_%1.3f.txt" %rho
N=125

data = np.loadtxt(name)
Ecin = data[:,0]
E = data[:,1]
P = data[:,2]
T = 2*Ecin/(3*N)
N_T = len(T)

plt.figure(1)
plt.plot(T,E/N,"r.")
plt.grid()
plt.figure(2)
plt.plot(T,P,"b.")
plt.plot(T,rho*T,"r-")
plt.grid()
plt.show()
