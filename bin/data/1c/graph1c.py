import matplotlib.pyplot as plt
import sys
import numpy as np
import os

data = np.load("analisis.npy")

fz=15

Cv = np.array([])
N = np.array([])

plt.figure(1)

for i in range(len(data)):


	T = data[i][0]
	E = data[i][1]
	N = np.append(N,512)
	fit = np.polyfit(T,E/N[i],1)
	#N = np.append(N,(i+2)**3)
	Cv = np.append(Cv,fit[0])
	#plt.figure(i)
	plt.plot(T,E/N[i],'ro')#,label='Experimento (N={i})'.format(i=N))
	plt.plot(T,np.polyval(fit,T),label='Ajuste: $c_v^*={i}$'.format(i='%.3f'%fit[0]))

plt.grid()
plt.legend(loc='best')
plt.xlabel("$T^*$",fontsize=fz)
plt.ylabel("$e^*$",fontsize=fz)
#plt.title("$e^*$ vs $T^*$ para N = 512")
plt.savefig("e_vs_T.png")

"""
plt.figure(2)

plt.plot(N,Cv,'ro',label='Experimento')
fit = np.polyfit(N,Cv,1)
plt.plot(N,np.polyval(fit,N),label='Ajuste: $y={i} * x + {j}$'.format(i='%.3f'%fit[0], j='%.3f'%fit[1]))
plt.legend(loc='best')
plt.xlabel("$N$")
plt.ylabel("$C_v$")
plt.grid()
"""

i=0
T = data[i][0]
EcInv = data[i][2]
CvTeo = np.array(N[i]*(1-T*(3.0/2*N[i]-1)*EcInv))
CvTeo = np.power(CvTeo,-1.0)
plt.figure(3)
plt.plot(T,CvTeo,'ro',label="$c_v$ Teorico $\mu$canonico")
plt.plot([np.min(T),np.max(T)],[Cv[i],Cv[i]],'b',label="$c_v$ Experimento")
plt.xlabel("$T^*$",fontsize=fz)
plt.ylabel("$c_v$",fontsize=fz)
#plt.title("$c_v^*$ vs $T^*$ para N = 512")
#plt.title("N = " + str(int(N[i])))
plt.grid()
plt.legend(loc='best')
plt.savefig("cv_vs_T.png")

plt.show()
