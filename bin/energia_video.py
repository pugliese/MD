import numpy as np
import matplotlib.pyplot as plt

t, Ec, Ep = np.loadtxt("energia.txt",unpack=True)
paso=10
for i in range(0,len(t)/paso):
	print str((i+1.0)/(len(t)/paso)*100) + "%"
	color='yo'
	fig, (ax0,ax1) = plt.subplots(2, figsize=(8, 8), dpi=80, facecolor='w', edgecolor='k')
	ax0.plot(t,Ec,'r',label='Cinetica')
	ax0.plot(t,Ep,'b',label='Potencial')
	p=i*paso
	ax0.plot(t[p],Ec[p],color,t[p],Ep[p],color)
	ax0.set_ylabel('Energias')
	ax0.legend(loc='best')
	ax0.set_xlim([-0.05,10.05])
	#ax0.set_ylim([-1.1,0.5])
	#ax0.set_title("t = "+str(i*0.0005))

	ax1.plot(t,Ec+Ep,'g')
	ax1.set_ylabel('Energia total')
	ax1.plot(t[p],Ec[p]+Ep[p],color)
	ax1.set_xlim([-0.05,10.05])
	#ax1.set_ylim([-0.597,-0.5905])

	plt.savefig("graph"+str(i)+".png")
	plt.close(fig)

