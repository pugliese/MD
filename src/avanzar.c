#include "avanzar.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int Verlet(double *vector_posvel, double **vector_fuerza, int N,
            double *LUTF, double Ntabla, double m, double h,double L) //pasito a pasito
{
  //necesito unas fuerzas iniciales que vienen de arriba
  double *vector_fuerza_h = malloc(N*3*sizeof(double));

  Verlet_pos(vector_posvel,*vector_fuerza,N,m,h,L) ; //posiciones t+h
  Calcular_Fuerzas(vector_posvel,vector_fuerza_h,N,LUTF,Ntabla,L) ;//fzas t+h
  Verlet_vel(vector_posvel, *vector_fuerza, vector_fuerza_h,N,m,h) ; //vel t+h

  free(*vector_fuerza);      // Elimino las "fuerzas viejas"
  *vector_fuerza = vector_fuerza_h;  // Pongo las nuevas en su lugar

  return 0;
}

///-*--------------------------------------------------------------------------*

int Verlet_pos(double *vector_posvel, double *vector_fuerza, int N,double m, double h, double L){
  //x=x-l*floor(x/l)

  for(int t=0;t<3*N;t++){
    vector_posvel[t] = vector_posvel[t] + vector_posvel[t+3*N]*h + 0.5*vector_fuerza[t]*h*h/m;
    vector_posvel[t] = vector_posvel[t] - L*floor(vector_posvel[t]/L);
  }

  return 0 ;
}
///-*--------------------------------------------------------------------------*

int Verlet_vel(double *vector_posvel, double *vector_fuerza,double *vector_fuerza_h, int N,double m, double h){
  //x=x-l*floor(x/l)

  for(int t=3*N;t<6*N;t++){
    vector_posvel[t] = vector_posvel[t] + 0.5*(vector_fuerza[t-3*N]+vector_fuerza_h[t-3*N])*h/m ;
  }

  return 0 ;
}
///-*--------------------------------------------------------------------------*
//Fij es una matriz antisimetrica que guarda la fza que ejerce la
//particula j sobre la particula i. Proyectando adecuadamente cada termino, la
//suma sobre una fila me da la fuerza total sobre la particula.

//R variable auxiliar que guarda la distancia entre dos particulas i y j.

//F variable auxiliar que guarda la fuerza entre dos particulas i y j.

int Calcular_Fuerzas(double *vector_posvel, double *vector_fuerza, int N, double *LUTF, int Ntabla, double L){

  double R,F,comp_k;
  for(int i=0;i<3*N;i++){
    vector_fuerza[i]=0;
  }
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
