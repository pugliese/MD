#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double Delta(double *pos, int N, int comp, int i, int j, double L){
  double d=pos[i+comp*N]-pos[j+comp*N];
  //int beta = ceil(floor(2*d/L)*.5);
  if(d>0.5*L){
    return d-L;
  }else{
    if(d>-0.5*L){
      return d;
    }else{
      return L+d;
    }
  }
// beta devuelve 1 si d>L/2; 0 si -L/2<d<L/2; -1 si d>-L/2
  //return d-beta*L;
}

double Distancia(double *pos, int N, int i, int j, double L){

  double dist = 0, dk;

  for(int k=0; k<3; k++){
    dk = Delta(pos, N, k, i, j, L);
    dist = dist + dk*dk;
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
  else res = Interpol(LUT,R,step); //y sino, interpola linealmente.

  return res;
}

//m y b son la pendiente y ordenada del segmento que une los dos puntos cuyo
//intervalo contiene a R.

//No me pude resistir con el nombre de la funcion.

double Interpol(double *LUT, double R, double step){

  int idx = floor(R/step)-1; // El -1 es porque LUT[i] = Fuerza(step*(i+1)) (sino, LUT[0]=Fuerza(0)=Inf)

  double m = (LUT[idx+1]-LUT[idx])/step;
  return LUT[idx]+(R-step*idx)*m;
}

int Reescalar_Vel(double *posvel,int N,double T_actual, double T_deseado){

  double resca = sqrt(T_deseado/T_actual) ;

  for (int i=3*N;i<6*N;i++){
    posvel[i] = resca * posvel[i];
  }

  return 0;
}
//---------------------------------------------------------------//
double Varianza(double *vector,int N){
  double sigma, mu ;

  mu = esperanza(vector, N);
  sigma = esperanza2(vector,N) - mu*mu;
  
  return sigma;
}

double esperanza2(double *vector, int n) {
   double X=0;

   for(int i=0;i<n;i++) X = X + vector[i]*vector[i];
   X = X/n ;

   return X ;
 }
double esperanza(double *vector, int n) {
  double mu=0;

  for(int i=0;i<n;i++) mu = mu + vector[i];
  mu = mu/n ;

  return mu ;
}
//---------------------------------------------------------------//
