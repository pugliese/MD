import numpy as np
import matplotlib.pyplot as plt
import sys

r= np.loadtxt(sys.argv[1],unpack=True)

x= np.arange(0,len(r),1)
plt.figure(1)

plt.plot(x,r,'.-')
#plt.hist(r,x)

plt.show()
