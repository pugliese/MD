import matplotlib.pylab as plt
import numpy as np
import sys

rho = float(sys.argv[1])

name = "2_E_P_%1.3f.txt" %rho;

data = np.loadtxt(name)
Ecin = data[:,0]
E = data[:,1]
P = data[:,2]
N = 125
print max(E), min(E)

#print np.mean(Ecin[0:100])*2/(3*N), np.std(Ecin[0:100])*2/(3*N), max(Ecin[0:100])*2/(3*N), min(Ecin[0:100])*2/(3*N)

plt.figure(1)
plt.plot(E/N,2*Ecin/(3*N), "r.")
plt.title("T(E)")
plt.grid()
plt.figure(2)
plt.plot(2*Ecin/(3*N),P, "b.")
plt.plot(2*Ecin/(3*N),2*rho*Ecin/(3*N), "r-")   ## Presion ideal
plt.grid()
plt.show()
"""
A=[]
for i in range(len(E)):
    if(abs(E[i]-.2*125)<.05*125):
        A.append(Ecin[i]*2/(3*N))
plt.hist(A)
plt.show()
"""
