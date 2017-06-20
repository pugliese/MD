#include "avanzar.h"
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

double Distancia(double *pos, int N, int i, int j){

  double dist = 0;

  for(int k=0; k<3; k++){
    dist = dist + (pos[i+k*N]-pos[j+k*N])*(pos[i+k*N]-pos[j+k*N]);
  }

  return sqrt(dist);

}

//step es el paso que se uso para la LUT

//idx es el indice que le corresponde al valor mas cercano (por debajo)
//en la LUT al R usado

double Valor_LUT(double *LUT, int Ntabla, double R){

  double step = 3.0/Ntabla;
  double res = 0;

  if(R>=3) res = 0; //si es >3 devuelve 0, no hay interaccion pues no se ven;
  else if(R<step) res = LUT[0]; //sino, si es menor que step, devuelve la minima posicion;
  else res = Interpol(LUT,R,step); //y sino, interpola linealmente.

  return res;

}

//m y b son la pendiente y ordenada del segmento que une los dos puntos cuyo
//intervalo contiene a R.

//No me pude resistir con el nombre de la funcion.

double Interpol(double *LUT, double R, double step){

  int idx = floor(R/step)-1; // El -1 es porque LUT[i] = Fuerza(step*(i+1)) (sino, LUT[0]=Fuerza(0)=Inf)

  double m = (LUT[idx+1]-LUT[idx])/step;
  double b = LUT[idx]-m*idx*step;

  return b + m * R;
  /* Version sin calcular b; es lo mismo pero... hay una cuenta menos!!!
  return LUT[idx]+(R-step*idx)*m;
  */
}
