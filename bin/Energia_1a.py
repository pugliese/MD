import numpy as np
import matplotlib.pyplot as plt
import sys

ecin,epot= np.loadtxt(sys.argv[1])

x= np.arange(0,len(ecin),1)
plt.figure(1)

#plt.plot(x,ecin,'.-')
#plt.plot(x,epot,'.-')
plt.plot(x,ecin+epot,'m')

plt.show()
