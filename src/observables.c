#include "observables.h"
#include "funciones.h"
#include "avanzar.h"
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
    Ecin = Ecin + m*0.5*(pos_vel[i+3*N]*pos_vel[i+3*N]+pos_vel[i+4*N]*pos_vel[i+4*N]+pos_vel[i+5*N]*pos_vel[i+5*N]);
  }
  return Ecin;
}

//------------------------------------------------------//


double Presion (double Pex, double Ecin, double Vol){

  return (1/(3*Vol))*(Pex+2*Ecin); // es la presion de exceso + la P ideal
}

double* Gr(double* pos,int N,double rho, double dr, double L,int nhist) {
  //int nhist= ceil (L/(2*dr));
  double rij;
  int k;

  double *hist_gr = malloc(sizeof(double)*nhist) ;
  for (int i=0; i<nhist;i++) hist_gr[i] = 0 ;

  for(int i=0;i<N;i++){
    for(int j=0;j<i;j++){
      rij = Distancia(pos, N, i, j, L);
      k = floor(rij/dr);
      hist_gr[k]++;
    }
  }
  for (int i=1; i<nhist;i++){
    hist_gr[i]=hist_gr[i]*2/(4*M_PI*dr*dr*dr*i*i*rho*N);
  }
  return hist_gr;
}

//------------------------------------------------------//

double Orden_verlet (double* pos, int N, double a) {
//  a=L/pow(N,1.0/3);
  double lamb = 0 ;

  for(int j=0;j<3;j++) lamb = lamb + lambda(pos,j,N,a);

  return lamb/3 ;
}

double lambda (double* pos,int comp,int N,double a){
  double lamx =0;
  for (int i=0;i<N;i++){
    lamx = lamx + (1.0/N)*cos(2* (M_PI/a) *(pos[i+comp*N]-a*0.5));
  }
  return lamx;
}

//------------------------------------------------------//

double Lindemann(double *vector, double **vector_fuerza, int N, double *LUTF, double Ntabla, double m, double h,double L, int N_prom, double* T){
  double* rij2 = malloc(N*(N-1)*sizeof(double)/2);
  double* rij = malloc(N*(N-1)*sizeof(double)/2);
  int index;
  double r;
  *T = 0;
  int norm = N*(N-1)/2;
  for(int i=0;i<norm;i++){
    rij2[i] = 0;
    rij[i] = 0;
  }
  for(int k=0;k<N_prom;k++){
    Verlet(vector, vector_fuerza, N,LUTF, Ntabla, m, h, L);
    *T = *T+Energia_Cinetica(vector,N,m)*2/(3*N*N_prom);
    for(int i=1;i<N;i++){
      index = i*(i-1)/2;
      for(int j=0;j<i;j++){
        r = Distancia(vector,N,i,j,L);
        rij[j+index] = rij[j+index] + r/N_prom;
        rij2[j+index] = rij2[j+index] + r*r/N_prom;
      }
    }
  }
  double res=0;
  for(int i=0;i<N;i++){
    index = i*(i-1)/2;
    for(int j=0;j<i;j++){
      res = res+(rij2[j+index]/(rij[j+index]*rij[j+index])-1)/norm;
    }
  }
  free(rij2);
  free(rij);
  return sqrt(res);
}
