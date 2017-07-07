import numpy as np
import matplotlib.pyplot as plt
import sys

#r= np.loadtxt("Histo_gr_0.6.txt",unpack=True)
#r2= np.loadtxt("Histo_gr_0.8.txt",unpack=True)
#r3= np.loadtxt("Histo_gr_1.txt",unpack=True)
nombres=range(len(sys.argv)-1)
i=0;
r=range(len(sys.argv)-1);
x=range(len(sys.argv)-1);
for i in range (len(sys.argv)-1):
	if len(sys.argv)>i:
		x[i],r[i]= np.loadtxt(sys.argv[i+1],unpack=True)
		buff=sys.argv[i+1]
		buff=buff[9:]
		buff=buff[:-4]
		nombres[i]=buff

#x= np.arange(0,len(r[0]),1)
plt.figure(1)
plt.grid ()
plt.title("g(r) para T=adefinir")
for i in range (len(sys.argv)-1):
	plt.plot(x[i],r[i],'.-',label=nombres[i])
plt.legend(loc='best')
#plt.plot(x,r2,'.-r')
#plt.plot(x,r3,'.-g')
#if len(sys.argv)>1:
#	plt.plot(x,r4,'.-c')


#plt.hist(r,x)

plt.show()
