#include "avanzar.h"
#include "inicializar.h"
#include "tablas.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char const *argv[]) {
// Mi idea es tener la variable opcion que es un caracter que puede hacer referencia a las distintas opciones
// Por ahora, la unica opcion es t para generar una nueva tabla
  char opcion;
  if(argc>1){
    sscanf(argv[1], "%c", &opcion);
  }else{
    opcion ='s';
  }
  if(opcion=='t'){  // Para generar la tabla, luego del .e escribimos t para que sepa que
    int N;        // debe generar la tabla seguido de la cantidad de puntos que queremos
    sscanf(argv[2],"%d", &N);
    double* LUT1 = LUT_P(N);
    double* LUT2 = LUT_F(N);
    guardar_tablas(LUT1,LUT2,N);
    free(LUT1);
    free(LUT2);
  }else{

    int N=13*13*13;
    double rho=0.8442;
    double m=1;
    double T=0.728;
    double L = pow(N/rho,1./3);
    double h = 1E-4;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));
    double* LUTF ;
    double* LUTP ;

    int Ntable = leer_tablas(&LUTP, &LUTF);

    srand(time(NULL));

    Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);
/*
    for (int i=0;i<N;i++) {
      printf("particula %d \n",i);
      printf("r : %f %f %f \n",vector[i],vector[i+N],vector[i+2*N]);
      printf("v : %f %f %f \n",vector[i+3*N],vector[i+4*N],vector[i+5*N]);
    }
*/

    double PromVel = 0;
    for(int i = 0;i<3*N;i++) PromVel = PromVel + vector[3*N+i]*vector[3*N+i]/(3*N);
    printf("promedio velocidad = %f\n",PromVel);
    Verlet(vector,&vector_fuerza,N,LUTF,Ntable,m,h,L);

    free(vector);
    free(vector_fuerza);
    free(LUTP);
    free(LUTF);
    /*
    double *vector = malloc(6*2*sizeof(double));
    double L = 10;
    vector[0] = 0.5;
    vector[2] = 0.5;
    vector[4] = 8;
    vector[1] = 1.5;
    vector[3] = 9;
    vector[5] = 0.3;
    double dx = Delta(vector,2,0,0,1,L);
    double dy = Delta(vector,2,1,0,1,L);
    double dz = Delta(vector,2,2,0,1,L);
    printf("%lg %lg %lg\n", dx,dy,dz);
    double* F = malloc(3*2*sizeof(double));
    Calcular_Fuerzas(vector,F,2,LUTF,Ntable,L);
    printf("%lg %lg %lg\n", F[0],F[2],F[4]);
    printf("%lg %lg %lg\n", F[1],F[3],F[5]);
    free(vector);
    free(LUTP);
    free(LUTF);*/
  }
  return 0;
}
