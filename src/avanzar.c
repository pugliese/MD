#include "avanzar.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int Verlet(double *vector_posvel, double *vector_fuerza, int N,
            double *LUTF, double Ntabla, double m, double h)
{

  //insert code here

  return 0;
}


//Fij es una matriz antisimetrica que guarda la fza que ejerce la
//particula j sobre la particula i. Proyectando adecuadamente cada termino, la
//suma sobre una fila me da la fuerza total sobre la particula.

//R variable auxiliar que guarda la distancia entre dos particulas i y j.

//F variable auxiliar que guarda la fuerza entre dos particulas i y j.

int Calcular_Fuerzas(double *vector_posvel, double *vector_fuerza, int N, double *LUTF, int Ntabla){

  double *Fij = malloc(N*N*sizeof(double));
  double R,F;

  for(int i=0; i<3*N; i++){
    vector_fuerza[i] = 0;
  }

  for(int i=0; i<N; i++){
    for(int j=i+1; j<N; j++){
      R = Distancia(vector_posvel,N,i,j);
      F = Valor_LUT(LUTF,Ntabla,R);
      Fij[i*N+j] = F/R;
      Fij[j*N+i] = -Fij[i*N+j];
    }
  }

  //el primer termino acumula, el segundo es la proyeccion

  for(int i=0; i<N; i++){
    for(int j=0; j<3; j++){
      for(int k=0; k<N; k++){
        vector_fuerza[i+j*N] = vector_fuerza[i+j*N]+fabs(vector_posvel[k+j*N]-vector_posvel[i+j*N])*Fij[i*N+k];
      }
    }
  }
  /* Version alternativa sin Fij
  for(int i=0;i<N;i++){
  	for(int j=i+1;j<N;j++{
  		R = Distancia(vector_posvel,N,i,j);
  		F = Valor_LUT(LUTF,Ntabla,R);
  		for(int k=0;k<3;k++){
  			comp_k = F*fabs(vector_posvel[i+k*N]-vector_posvel[j+k*N])/R;
  			vector_fuerza[i+k*N] = vector_fuerza[i+k*N]+comp_k;
  			vector_fuerza[j+k*N] = vector_fuerza[j+k*N]-comp_k;
  		}
  	}
  }
  */

  free(Fij);
  return 0;
}
