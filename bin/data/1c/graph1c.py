import matplotlib.pyplot as plt
import sys
import numpy as np
import os

T,E = np.loadtxt("analisis.out")
plt.plot(T,E,'ro',label='Experimento')
fit = np.polyfit(T,E,1)
plt.plot(T,np.polyval(fit,T),label='Ajuste: $C_v^* = {i}$'.format(i='%.3f'%fit[0]))
plt.grid()
plt.legend(loc='best')
plt.xlabel("$T^*$")
plt.ylabel("$E^*$")
plt.show()