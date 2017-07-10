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

cwd = os.getcwd()
ls = os.listdir(cwd)
Term = 2000
LCorr = 1500
#LCorr=Term
NPasos = 100000
#data[ N**1/3-2 ] = [ [T], [E] , [EcInv] ]
data = [ [ [] , [] , [] ] for i in range(1)]

idxMean = []

for i in range(NPasos/Term):
	idxMean = idxMean + range(i*Term,i*Term+LCorr)
"""
idxMean = range(0,NPasos,Term)
"""

for files in ls:

	if files.endswith(".txt") and files!='tablas.txt':

		f = open(files,"r")
		f.readline()
		N = f.readline()
		N = N.split(" ")
		N = int(N[-1])
		#idx = int(np.ceil(N**(1.0/3)))-2
		idx=0
		if N==512:
			EcVect, EpVect = np.loadtxt(files)
			Etot = EcVect + EpVect
			
			"""
			#Comun
			E = np.mean(Etot[idxMean])
			T = np.mean(EcVect[idxMean]*2/(3.0*N))
			EcInv = np.mean(np.power(EcVect[idxMean],-1.0))
			"""
			#Super Canchera
			Etot = Etot[idxMean]
			EcVect = EcVect[idxMean]
			Etot = Etot.reshape((len(idxMean)/LCorr,LCorr))
			E = np.mean(np.mean(Etot,axis=1))
			EcVect = EcVect.reshape((len(idxMean)/LCorr,LCorr))
			T = np.mean(np.mean(EcVect*2/(3.0*N),axis=1))
			EcInv = np.mean(np.power(np.mean(EcVect,axis=1),-1.0))
			

			data[idx][0].append(T)
			data[idx][1].append(E)
			data[idx][2].append(EcInv)

data = np.array(data)

np.save("analisis.npy",data)
