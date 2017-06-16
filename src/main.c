#include "avanzar.h"
#include "inicializar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char const *argv[]) {
  int N=512;
  double rho=0.8442;
  double m=1;
  double T=0.728;
  double* vector = malloc(6*N*sizeof(double));

  srand(time(NULL));

  Inicializar(vector, N, rho, m,T);

  for (int i=0;i<N;i++) {
    printf("particula %d \n",i);
    printf("r : %f %f %f \n",vector[i],vector[i+N],vector[i+2*N]);
    printf("v : %f %f %f \n",vector[i+3*N],vector[i+4*N],vector[i+5*N]);
  }

  double PromVel = 0;
  for(int i = 0;i<3*N;i++) PromVel = PromVel + vector[3*N+i]*vector[3*N+i]/(3*N);
  printf("promedio velocidad = %f\n",PromVel);

  free(vector);

  return 0;
}
