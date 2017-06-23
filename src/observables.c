#include "observables.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float Energia_Potencial(double* pos_vel, int N, float* LUT_P, int Ntabla){
  double rij = 0;
  double V = 0;
  for(int i=1;i<N;i++){
    for(int j=i+1;j<N;j++){
      rij = Distancia(pos_vel,N,i,j);
      V = V + Valor_LUT(LUT_P,Ntabla,R);
    }
  }
  return V;
}

float Energia_Cinetica(double* pos_vel, int N, double m){
  double Ecin = 0;
  for(int i=0;i<N;i++){
    Ecin = Ecin + 0.5*m*(pos_vel[i+3*N]*pos_vel[i+3*N]+pos_vel[i+4*N]*pos_vel[i+4*N]+pos_vel[i+5*N]*pos_vel[i+5*N])
  }
  return Ecin;
}
