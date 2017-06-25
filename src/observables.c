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
    Ecin = Ecin + 0.5*m*(pos_vel[i+3*N]*pos_vel[i+3*N]+pos_vel[i+4*N]*pos_vel[i+4*N]+pos_vel[i+5*N]*pos_vel[i+5*N]);
  }
  return Ecin;
}
