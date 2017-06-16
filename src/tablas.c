#include "tablas.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double Lennard_Jones(double r){
  double r6 = r*r*r;
  r6 = r6*r6;
  return (1.0/r6-1)*4.0/r6;
}

double* LUT_P(int N){
  double step = 3.0/N;
  int m= floor(2.5/step);
  double r=0;
  double* res=malloc(N*sizeof(double));
  for(int i=0;i<m;i++){
    r = r+step;
    res[i] = Lennard_Jones(r);
  }
  double Fo = Fuerza_Lennard_Jones(2.5);
  double So = Lennard_Jones(2.5);
  for(int i=m;i<N;i++){
    r = r+step;
    res[i] = -Fo*(r-3.0)*(r-3.0)+So-Fo/4;
  }
  return res;
}


double Fuerza_Lennard_Jones(double r){  // Devuelve el módulo de la fuerza
  double r6 = r*r*r;
  r6 = r6*r6;
  return (2.0/r6-1)*24.0/(r*r6);
}

double* LUT_F(int N){    // Tabla con los modulos de la fuerza de Lennard-Jones
  double step = 3.0/N;
  int m= floor(2.5/step);
  double r=0;
  double* res=malloc(N*sizeof(double));
  for(int i=0;i<m;i++){
    r = r+step;
    res[i] = Fuerza_Lennard_Jones(r);
  }
  double Fo = Fuerza_Lennard_Jones(2.5);
  for(int i=m;i<N;i++){
    r = r+step;
    res[i] = 2*Fo*(3-r);
  }
  return res;
}

int guardar_tablas(double *LUTF, double *LUTP, int N){
  FILE* fp = fopen("tablas.txt", "w");
  fprintf(fp, "%d\n", N);   // Guardo la longitud de la tabla en el primer renglon
  for(int i=0;i<N;i++){
    fprintf(fp, "%f ", LUTP[i]);  // Guardo la tabla con potenciales separadas por espacios
  }
  fprintf(fp, "\n"); // Salto de linea para que sepa que termino una tabla
  for(int i=0;i<N;i++){
    fprintf(fp, "%f ", LUTF[i]); // Guardo la tabla con fuerzas separadas por espacios
  }
  fclose(fp);
  return 0;
}

int leer_tablas(double *LUTF, double *LUTP){
  FILE* fp = fopen("tablas.txt","r");
  int N,k;
  k=fscanf(fp,"%d\n",&N); // Leo la longitud de mi tabla
  double* tabP = malloc(N*sizeof(double));
  double* tabF = malloc(N*sizeof(double));
  for(int i=0;i<N;i++){
    k=fscanf(fp,"%lg",tabP+i);
  }
  for(int i=0;i<N;i++){
    k=fscanf(fp,"%lg",tabF+i);
  }
  LUTF = tabF;
  LUTP = tabP;
  return N;
}

int main(int argc, char **argv){
  if (argc==2){
    int N;
    sscanf(argv[1],"%d\n", &N);
    double* LUT1 = LUT_P(N);
    double* LUT2 = LUT_F(N);
    guardar_tablas(LUT1,LUT2,N);
    free(LUT1);
    free(LUT2);
    leer_tablas(LUT1, LUT2);
    for(int i=0;i<N;i++){
      printf("%lg %lf\n", LUT1[i], LUT2[i]);
    }
    free(LUT1);
    free(LUT2);
  }else{
    printf("Error: Introduzca cantidad de puntos\n");
  }
  return 0;
}
