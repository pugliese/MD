#include "tablas.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float Lennard_Jones(float r){
  float r6 = r*r*r;
  r6 = r6*r6;
  return (1.0/r6-1)*4.0/r6;
}

float* LUT_P(int N){
  float step = 3.0/N;
  int m= floor(2.5/step);
  float r=0;
  float* res=malloc(N*sizeof(float));
  for(int i=0;i<m;i++){
    r = r+step;
    res[i] = Lennard_Jones(r);
  }
  float P2,P1,P0;   // Aca uso un polinomio de Lagrange de grado 2 para
  float c0,c1;      // interpolar 2.5, 2.75 y 3.0 (valiendo 0 en 3.0)
  c0 = 8*Lennard_Jones(2.5);
  c1 = -16*Lennard_Jones(2.75);  // El coeficiente para r=3.0 vale 0 (se anula)
  for(int i=m;i<N;i++){
    r = r+step;
    res[i] = (c0*(r-2.75)+c1*(r-2.5))*(r-3.0);
  }
  return res;
}


float Fuerza_Lennard_Jones(float r){  // Devuelve el módulo de la fuerza
  float r6 = r*r*r;
  r6 = r6*r6;
  return (2.0/r6-1)*24.0/(r*r6);
}

float* LUT_F(int N){    // Tabla con los modulos de la fuerza de Lennard-Jones
  float step = 3.0/N;
  int m= floor(2.5/step);
  float r=0;
  float* res=malloc(N*sizeof(float));
  for(int i=0;i<m;i++){
    r = r+step;
    res[i] = Fuerza_Lennard_Jones(r);
  }
  float P2,P1,P0;   // Aca uso un polinomio de Lagrange de grado 2 para
  float c0,c1;      // interpolar 2.5, 2.75 y 3.0 (valiendo 0 en 3.0)
  c0 = 8*Fuerza_Lennard_Jones(2.5);
  c1 = -16*Fuerza_Lennard_Jones(2.75);  // El coeficiente para r=3.0 vale 0 (se anula)
  for(int i=m;i<N;i++){
    r = r+step;
    res[i] = (c0*(r-2.75)+c1*(r-2.5))*(r-3.0);
  }
  return res;
}

int main(){
  int N=30;
  float *LUT1 = LUT_F(N);
  float *LUT2 = LUT_P(N);
  for(int i=0;i<N;i++){
    printf("%f, ", LUT1[i]);
  }
  printf("\n");
  for(int i=0;i<N;i++){
    printf("%f, ", LUT2[i]);
  }
  printf("\n");
  free(LUT1);
  free(LUT2);
  return 0;
}
