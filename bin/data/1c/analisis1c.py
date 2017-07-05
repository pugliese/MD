import matplotlib.pyplot as plt
import sys
import numpy as np
import os

def swap(x,i,j):

	aux=x[i]
	x[i]=x[j]
	x[j]=aux

def sort(x,y):

	for i in range(0,len(x)):

		for j in range(0,len(x)):

			if(x[i]<x[j]):
		
				swap(x,i,j)
				swap(y,i,j)

cwd=os.getcwd()
ls=os.listdir(cwd)
N=512
Term = 2000
T=np.array([])
E=np.array([])

for files in ls:

	if files.endswith(".txt"):
		
		EcVect, EpVect = np.loadtxt(files)
		Etot = EcVect + EpVect
		Etot = Etot.reshape((len(Etot)/Term,Term))
		E = np.append(E, np.mean(np.mean(Etot,axis=1)))
		EcVect = EcVect.reshape((len(EcVect)/Term,Term))
		T = np.append(T,np.mean(np.mean(EcVect*2/(3.0*N),axis=1)))

sort(T,E)
np.savetxt("analisis.out", [T,E], header = "<T> <E>, Term = "+ str(Term) + " y Npasos = "+ str(len(EpVect)))
		
		
		
