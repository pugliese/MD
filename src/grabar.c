#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grabar.h"

int Grabar_PDB(double *vector_posvel, int N, double L, FILE *fs){

  for(int i=0; i<N; i++){
    Grabar_Particula_PDB(vector_posvel,N,L,fs,i);
  }
  fprintf(fs,"END\n");

  return 0;

}

int Grabar_Particula_PDB(double *vector_posvel, int N, double L, FILE *fs, int j){

  char atom[7]= "ATOM  \0";
  char blank[19] = "N                 \0";
  double s = 5; //s es un factor de escala y tiene que estar entre 0 y 9.9999 para que no se vaya de lugar las ubicaciones

  fprintf(fs,"%s%06d%s%.5f %.5f %.5f\n",atom,j+1,blank,vector_posvel[j]*s/L,vector_posvel[j+N]*s/L,vector_posvel[j+2*N]*s/L);

  return 0;

}
