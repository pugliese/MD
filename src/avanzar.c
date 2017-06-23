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

int Calcular_Fuerzas(double *vector_posvel, double *vector_fuerza, int N, double *LUTF, int Ntabla, double L){

  double R,F,comp_k;
  for(int i=0;i<N;i++){
  	for(int j=i+1;j<N;j++){
  		R = Distancia(vector_posvel,N,i,j, L);
  		F = Valor_LUT(LUTF,Ntabla,R);
  		for(int k=0;k<3;k++){
  			comp_k = F*Delta(vector_posvel, N, k, i, j, L)/R;
  			vector_fuerza[i+k*N] = vector_fuerza[i+k*N]+comp_k;
  			vector_fuerza[j+k*N] = vector_fuerza[j+k*N]-comp_k;
  		}
  	}
  }

  return 0;
}
