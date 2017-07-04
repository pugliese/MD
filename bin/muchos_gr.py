import numpy as np
import matplotlib.pyplot as plt
import sys

r= np.loadtxt("Histo_gr_0.6.txt",unpack=True)
r2= np.loadtxt("Histo_gr_0.8.txt",unpack=True)
r3= np.loadtxt("Histo_gr_1.txt",unpack=True)
r4= np.loadtxt(sys.argv[1],unpack=True)

x= np.arange(0,len(r),1)
plt.figure(1)

plt.plot(x,r,'.-b')
plt.plot(x,r2,'.-r')
plt.plot(x,r3,'.-m')
plt.plot(x,r4,'.-c')
#plt.hist(r,x)

plt.show()
