#include "avanzar.h"
#include "inicializar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// vector es el vector con las posiciones y velocidades de las bolitas
// N es la cantidad de particulas =512 en el 1
//rho es la densidad = 0.8442 en en punto 1
//m es la masa
//T es el frio

int Inicializar (double* vector_posvel,double* vector_fuerza,int N,double* LUTF,int Ntable,double rho, double m, double T){
//  double V = N/rho ;
//  double a = V/N ;

  Llenar_Pos(vector_posvel,N,rho);
  Llenar_Vel(vector_posvel,N,rho,m,T);
  Calcular_Fuerzas(vector_posvel,vector_fuerza,N,LUTF,Ntable);

  return 0 ;
}

int Llenar_Pos (double* vector,int N,double rho){
  double Vol = N/rho;  // Volumen del recinto
  int L = pow(N,1./3); // Cantidad de puntos por "fila" asumiendo que hay L³ particulas, con N<=L³
  double a = pow(Vol,1./3)/L; // Espaciado entre las L³ particulas imaginarias, algunas posiciones quedaran vacias
  int i; // Indice de particula, se mueve entre 0 y N-1 y busco escribirlo en base L como i=x+y*L+z*L*L
  int x,y,z;
  //Lo nuevo es igual a lo de abajo, pero al reves para que sea posible tener un N no cubico
  for (int x=0;x<N;x++){
    for (int y=0;y<N;y++){
      for (int z=0;z<N;z++){
        i = x+y*L+L*L*z;
        vector[i] = (a/2) + x*a;
        vector[i+N] = (a/2) + y*a;
        vector[i+2*N] = (a/2) + z*a;
      }
    }
  }
  return 0 ;
}


int Llenar_Vel (double* vector,int N,double rho,double m, double T){

  for (int j=3*N;j<6*N;j++){
      vector[j] = Rand_Gauss(m,T) ;
  }

  double vmean[3]={0,0,0};

  for (int j=3;j<6;j++){
    for (int i=0;i<N;i++){
      vmean[j-3] = vmean[j-3] + vector[i+j*N]/N ;
    }
  }

  for (int j=3;j<6;j++){
    for (int i=0;i<N;i++){
      vector[i+j*N] = vector[i+j*N] - vmean[j-3];
    }
  }
  return 0 ;
}

double Rand_Gauss (double m, double T){
  double norm=0 ;
  int repe=24;
  double L=sqrt(12*T/(m*repe));  //L es la normalizacion EPS = 1

  for(int i=0;i<repe;i++) {
    norm=norm + (((float)rand() / (float)RAND_MAX)-0.5)*L;
  }

  return norm ;
}
