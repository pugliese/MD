#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



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
