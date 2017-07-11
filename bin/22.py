import matplotlib.pylab as plt
import numpy as np
import scipy as sc
from scipy.optimize import curve_fit
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
        R[i]=(sc.stats.linregress(T[:i],E[:i]))[2]
    return R

def recta2(T,E):
    R = np.zeros(20)
    for i in range(1,19):
        R[i]=sc.stats.linregress(T[i-1:i+2],E[i-1:i+2])[2]
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
    rhos = np.array([float(sys.argv[i]) for i in range(3,len(sys.argv))])
    Tcs = Quiebres(rhos,N)

    i = np.where(rhos==0.2)[0]
    T,E,P = cargar(N,0.2)
    Tcs[i,0] = T[14]
    """
    i = np.where(rhos==0.3)[0]
    T,E,P = cargar(N,0.3)
    Tcs[i,0] = (T[14]+T[15])/2
    """
    Tcs[0,1] = 0.05
    i = np.where(rhos==0.5)[0]
    T,E,P = cargar(N,0.5)
    Tcs[i,0] = (T[12]+T[13])/2
    Tcs[i,1] = (T[12]-T[13])/2
    i = np.where(rhos==0.35)[0]
    T,E,P = cargar(N,0.35)
    Tcs[i,0] = (T[12]+T[13])/2
    Tcs[i,1] = (T[12]-T[13])/2
    i = np.where(rhos==0.25)[0]
    T,E,P = cargar(N,0.25)
    Tcs[i,0] = (T[12]+T[13])/2
    Tcs[i,1] = (T[12]-T[13])/2
    i = np.where(rhos==0.6)[0]
    T,E,P = cargar(N,0.6)
    Tcs[i,0] = (T[15]+T[14])/2
    Tcs[i,1] = (T[14]-T[15])/2
    """
    i = len(rhos)-1
    T,E,P = cargar(N,0.8)
    Tcs[i,0] = min(T)
    """
    plt.errorbar(rhos,Tcs[:,0],yerr=Tcs[:,1], fmt="ro")
    plt.xlabel(r'$\rho^*$',fontsize=15)
    plt.ylabel(r'$T_c^*$',fontsize=15)
    plt.axis([0, 0.8, 0, 1.1])
    plt.grid()
    plt.savefig('Cambio_de_fase.png')
    plt.show()

if(sys.argv[1]=="E"):
    N=int(sys.argv[2])
    rhos = [float(sys.argv[i]) for i in range(3,len(sys.argv))]
    colores = ["ro","bv","gs","yp", "kd","c^","mh","rx","k*"]
    i=0
    for r in rhos:
        T,E,P = cargar(N,r)
        if(r==0.8):
            T=T[1:]
            E=E[1:]
        plt.plot(T,E/N,colores[i]+"--")
        i=i+1
    plt.legend([r'$\rho=%1.3f$' %r for r in rhos],loc=4,fontsize=15)
    plt.axis([0.25, 2.5,-6,3])
    plt.xlabel(r'$T^*$',fontsize=15)
    plt.ylabel(r'$E^*/N$',fontsize=15)
    tita = np.linspace(0,np.pi,50)
    r = 0.1
    #plt.plot(r*np.cos(tita)+1.05,4*r*np.sin(tita), "k--")
    #plt.plot(np.linspace(0.7+r,1.05+r,50),np.linspace(-3.25,0,50), "k--")
    #plt.plot(np.linspace(0.7+r,1.05+r,50)-2*r,np.linspace(-3.25,0,50), "k--")
    #plt.plot(r*np.cos(tita+np.pi)+0.7,4*r*np.sin(tita+np.pi)-3.25, "k--")
    plt.plot(np.linspace(0.7,1.25,50),np.linspace(-4,2,50), "k--")
    #plt.text(0.1,0,"Cambio \nde fase",fontsize=17)
    plt.text(1.1,2,"Cambio \nde fase",fontsize=16)
    plt.grid()
    plt.savefig("Energia_T_2.png")
    plt.show()

if(sys.argv[1]=="P"):
    N=int(sys.argv[2])
    rhos = [float(sys.argv[i]) for i in range(3,len(sys.argv))]
    colores = ["ro","bv","ks","yp", "gd","c^","mh","rx","k*"]
    i=0
    for r in rhos:
        T,E,P = cargar(N,r)
        if (r==0.1):
            T=T[1:]
            P=P[1:]
        if (r==0.55):
            T=T[1:]
            P=P[1:]
        if (r==0.7):
            T=T[:-3]
            P=P[:-3]
        plt.figure(1)
        plt.plot(T,P/r,colores[i]+"--")
        plt.figure(2)
        plt.plot(T,(P/(r*T)-1)/r,colores[i]+"--")
        i = i+1
    plt.figure(1)
    plt.grid()
    T = np.linspace(0.1,2.5,25)
    plt.plot(T,T, "r-")
    plt.legend([r'$\rho^* =%1.3f$' %r for r in rhos]+["Gas ideal"],loc=4,fontsize=15)
    plt.xlabel(r'$T^*$',fontsize=15)
    plt.ylabel(r'$P^*/\rho^*$',fontsize=15)
    plt.savefig("Presiones_T.png")
    plt.figure(2)
    plt.grid()
    plt.legend([r'$\rho^* =%1.3f$' %r for r in rhos],loc=4,fontsize=15)
    plt.xlabel(r'$T^*$',fontsize=15)
    plt.ylabel(r'$P_{ex}^*/T^*(\rho^*)^2$',fontsize=15)
    plt.savefig("Exceso_T.png")
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

if(sys.argv[1]=="V2"):
    N = int(sys.argv[2])
    To = [1, 1.1,1.2, 1.3,1.4, 1.5,1.6,1.7]#float(sys.argv[3])
    ##To=[1,1.7]
    rhos = [float(sys.argv[i]) for i in range(3,len(sys.argv))]
    pol = lambda x,B2,B3,B4: B2+B3*x+B4*x**2
    ##pol = lambda x,B2,B3: B2+B3*x
    B2 = []
    B3 = []
    B4 = []
    colores = ["ro","bv","ks","yp", "gd","c^","mh","rx","k*"]
    i=0
    for t in To:
        Pex = []
        for r in rhos:
            T,E,P = cargar(N,r)
            Pex.append(Interpol(T,P,t))
        Pex = np.array(Pex)
        rhos = np.array(rhos)
        Pex = (Pex/(t*rhos)-1)/rhos
        Bs,coso = curve_fit(pol,rhos,Pex)
        B2.append(Bs[0])
        B3.append(Bs[1])
        B4.append(Bs[2])
        plt.plot(rhos, Pex, colores[i]+"--")
        ##plt.plot(rhos,[pol(rho,Bs[0],Bs[1],Bs[2]) for rho in rhos],"g-")
        ##plt.plot(rhos,[pol(rho,Bs[0],Bs[1]) for rho in rhos],"g-")
        i=i+1
    plt.axis([0, 0.7, -4, 2])
    plt.xlabel(r'$\rho^*$',fontsize=15)
    plt.ylabel(r'$P_{ex}^*/T^*(\rho^*)^2$',fontsize=15)
    plt.legend(["T^*=%1.2f" %T for T in To],loc=2, borderaxespad=0.,fontsize=15)
    plt.grid()
    plt.savefig("Exceso_rho.png")
    plt.figure(2)
    plt.plot(To,B2,"ro--")
    plt.plot(To,B3,"bo--")
    plt.plot(To,B4,"go--")
    plt.legend([r'$B_2(T)$',r'$B_3(T)$',r'$B_4(T)$'],loc=4,fontsize=15)
    #plt.legend([r'$A(T)$',r'$B(T)$',r'$C(T)$'],loc=4,fontsize=15)
    plt.xlabel(r'$T^*$',fontsize=15)
    plt.ylabel('Coeficientes',fontsize=15)
    plt.grid()
    plt.savefig("Coef_Virial.png")
    plt.show()
"""
for i in range(len(rhos)):
    T,E,P = cargar(N,rhos[i])
    plt.plot(T,P,"o")
    #print T
plt.grid()
plt.show()
"""
