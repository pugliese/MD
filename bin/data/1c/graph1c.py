import matplotlib.pyplot as plt
import sys
import numpy as np
import os

data = np.load("analisis.npy")

Cv = np.array([])
N = np.array([])

plt.figure(1)

for i in range(len(data)):


	T = data[i][0]
	E = data[i][1]
	fit = np.polyfit(T,E,1)
	Cv = np.append(Cv,fit[0])
	N = np.append(N,(i+2)**3)
	#plt.figure(i)
	plt.plot(T,E,'ro')#,label='Experimento (N={i})'.format(i=N))
	plt.plot(T,np.polyval(fit,T),label='Ajuste: $C_v^*(N={l})={i}$'.format(l=int(N[i]),i='%.3f'%fit[0]))

plt.grid()
plt.legend(loc='best')
plt.xlabel("$T^*$")
plt.ylabel("$E^*$")

plt.figure(2)

plt.plot(N,Cv,'ro',label='Experimento')
fit = np.polyfit(N,Cv,1)
plt.plot(N,np.polyval(fit,N),label='Ajuste: $y={i} * x + {j}$'.format(i='%.3f'%fit[0], j='%.3f'%fit[1]))
plt.legend(loc='best')
plt.xlabel("$N$")
plt.ylabel("$C_v$")
plt.grid()


CvTeo = np.array([])
#for i in range(len(N)):
i=3
T = data[i][0]
CvTeo = np.append(CvTeo,N[i]*N[i]*(1-T*(3.0/2*N[i]-1)*data[i][2]))
plt.figure(3)
plt.plot(T,CvTeo,'ro')
plt.title("N = " + str(int(N[i])))

plt.show()