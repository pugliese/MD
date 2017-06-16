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

int Inicializar (double* vector,int N,double rho, double m, double T){
//  double V = N/rho ;
//  double a = V/N ;

  Llenar_Pos(vector,N,rho);
  Llenar_Vel(vector,N,rho,m,T);


  return 0 ;
}

int Llenar_Pos (double* vector,int N,double rho){

  double a = pow((1/rho),1./3);
  int L = ceil(pow(N,1./3));
  int i;
  for (int x=0;x<L;x++){
    for (int y=0;y<L;y++){
      for (int z=0;z<L;z++){
        i = x+L*y+L*L*z ;
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
    for (int i=j*N;i<(j+1)*N;i++){
      vmean[j-3] = vmean[j-3] + vector[i+j*N]/N ;
    }
  }

  for (int j=3;j<6;j++){
    for (int i=j*N;i<(j+1)*N;i++){
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
