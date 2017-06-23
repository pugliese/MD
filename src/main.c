#include "avanzar.h"
#include "inicializar.h"
#include "tablas.h"
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
    int N=30;
    double rho=0.8442;
    double m=1;
    double T=0.728;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));
    double* LUTF ;
    double* LUTP ;

    int Ntable = leer_tablas(&LUTP, &LUTF);

    srand(time(NULL));
    Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);

    for (int i=0;i<N;i++) {
      printf("particula %d \n",i);
      printf("r : %f %f %f \n",vector[i],vector[i+N],vector[i+2*N]);
      printf("v : %f %f %f \n",vector[i+3*N],vector[i+4*N],vector[i+5*N]);
    }

    double PromVel = 0;
    for(int i = 0;i<3*N;i++) PromVel = PromVel + vector[3*N+i]*vector[3*N+i]/(3*N);
    printf("promedio velocidad = %f\n",PromVel);

    free(vector);
  }
  return 0;
}
