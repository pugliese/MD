import matplotlib.pylab as plt
import numpy as np
import scipy.stats as sc
import sys
"""
N = float(sys.argv[1])
rho = float(sys.argv[2])
name = "22_E_P_%d_%1.3f.txt" %(N,rho)


data = np.loadtxt(name)
Ecin = data[:,0]
E = data[:,1]
P = data[:,2]
T = 2*Ecin/(3*N)
N_T = len(T)

plt.figure(1)
plt.plot(T,E/N,"r.")
plt.grid()
plt.figure(2)
plt.plot(T,P,"b.")
plt.plot(T,rho*T,"r-")
plt.plot(T,P-rho*T,"g.")
plt.grid()
plt.show()

plt.plot(T,E/N,"rv--")
N = 125
name = "22_E_P_%d_%1.3f.txt" %(N,rho)
data = np.loadtxt(name)
Ecin = data[:,0]
E = data[:,1]
P = data[:,2]
T = 2*Ecin/(3*N)
plt.plot(T,E/N,"bo--")
plt.show()


N=512
rhos=[0.2,0.3, 0.4, 0.5, 0.6, 0.7, 0.75]
"""
def cargar(N,rho):
    name = "22_E_P_%d_%1.3f.txt" %(N,rho)
    data = np.loadtxt(name)
    Ecin = data[:,0]
    E = data[:,1]
    P = data[:,2]
    T = 2*Ecin/(3*N)
    return T,E,P

def recta(T,E):
    R = np.zeros(20)
    for i in range(2,20):
        R[i]=(sc.linregress(T[:i],E[:i]))[2]
    return R

def recta2(T,E):
    R = np.zeros(20)
    for i in range(1,19):
        R[i]=sc.linregress(T[i-1:i+2],E[i-1:i+2])[2]
    return R

def quiebre(T,E):
    R = recta2(T,E)
    i = np.where(np.min(R[2:19])==R)[0]
    #return (T[i-1]+T[i+1])/2, (T[i-1]-T[i+1])/2
    return T[i], (T[i-1]-T[i+1])/2

def Quiebres(rhos,N=125):
    Tcs=np.zeros((len(rhos),2))
    for i in range(len(rhos)):
        T,E,P = cargar(N,rhos[i])
        Tcs[i,:] = quiebre(T,E)
    Tcs = np.array(Tcs)
    return Tcs

def Restar(T1,P1,T2,P2):
    P = np.zeros(len(P1))
    for i in range(len(T1)):
        P[i] = P1[i]-Interpol(T2,P2,T1[i])
    return P

def Interpol(X,Y,x):
    # X decreciente X[i]>X[i+1]
    if(x>=X[0]):
        return (x-X[0])*(Y[1]-Y[0])/(X[1]-X[0])+Y[0]
    else:
        if(x<=X[-1]):
            return (x-X[-1])*(Y[-2]-Y[-1])/(X[-2]-X[-1])+Y[-1]
        else:
            i = 0;
            while(x<X[i]):
                i=i+1
            return (x-X[i])*(Y[i-1]-Y[i])/(X[i-1]-X[i])+Y[i]


if(sys.argv[1]=="Tc"):
    N=int(sys.argv[2])
    rhos = [float(sys.argv[i]) for i in range(3,len(sys.argv))]
    Tcs = Quiebres(rhos,N)

    T,E,P = cargar(N,0.2)
    Tcs[0,0] = T[14]
    T,E,P = cargar(N,0.3)
    Tcs[1,0] = (T[14]+T[15])/2
    T,E,P = cargar(N,0.5)
    Tcs[3,0] = (T[12]+T[13])/2

    plt.plot(rhos,Tcs[:,0],"o")
    plt.xlabel("rho")
    plt.ylabel("T")
    plt.show()
if(sys.argv[1]=="P"):
    N=int(sys.argv[2])
    rhos = [float(sys.argv[i]) for i in range(3,len(sys.argv))]
    for r in rhos:
        T,E,P = cargar(N,r)
        plt.figure(1)
        plt.plot(T,P,"o")
        plt.figure(2)
        plt.plot(T,(P/(r*T)-1)/r,"o")
    plt.grid()
    plt.show()
if(sys.argv[1]=="V"):
    N=int(sys.argv[2])
    rho1 = float(sys.argv[3])
    rho2 = float(sys.argv[4])
    dr = rho2 - rho1;
    T1,E,P1 = cargar(N,rho1)
    T2,E,P2 = cargar(N,rho2)
    G1 = (P1/(rho1*T1)-1)/rho1;
    G2 = (P2/(rho2*T2)-1)/rho2;
    plt.plot(T1,Restar(T1,G1,T2,G2)/dr,"ro")
    plt.plot(T1,Restar(T1,G1*rho2,T2,G2*rho1)/dr,"bo")
    plt.grid()
    plt.figure(2)
    plt.plot(T1,G1, "ro")
    plt.plot(T2,G2, "bo")
    plt.show()
"""
for i in range(len(rhos)):
    T,E,P = cargar(N,rhos[i])
    plt.plot(T,P,"o")
    #print T
plt.grid()
plt.show()
"""
