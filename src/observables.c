#include "observables.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double Energia_Potencial(double* pos_vel, int N, double* LUT_P, int Ntabla, double L){
  double rij = 0;
  double V = 0;
  for(int i=0;i<N;i++){
    for(int j=i+1;j<N;j++){
      rij = Distancia(pos_vel,N,i,j, L);
      V = V + Valor_LUT(LUT_P,Ntabla,rij);
    }
  }
  return V;
}

double Energia_Cinetica(double* pos_vel, int N, double m){
  double Ecin = 0;
  for(int i=0;i<N;i++){
    Ecin = Ecin + (1/m)*0.5*(pos_vel[i+3*N]*pos_vel[i+3*N]+pos_vel[i+4*N]*pos_vel[i+4*N]+pos_vel[i+5*N]*pos_vel[i+5*N]);
  }
  return Ecin;
}

double Presion (double P, double Ecin,int N, double rho){
  double Vol = N/rho;

  Pres = (1/(3*Vol))*(P*0.5 + Ecin) ; // es la presion de exceso + la P ideal

  return Pres;
}

double* Gr(double* pos,int N, double dr, double L) {
  int nhist= ceil (L/(2*dr));
  double rij;
  int k;

  double *Hist_Gr = malloc(sizeof(double)*nhist) ;
  for (int i=0; i<nhist;i++) Hist_Gr[i] = 0 ;

  for(int i=0;i<N;i++){
    for(int j=0;j<i;j++){
      rij = Distancia(pos, N, i, j, L);
      k = floor(rij/dr);
      Hist_Gr[k]++;
    }
  }
  return Hist_Gr;
}
