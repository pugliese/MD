#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grabar.h"

int Grabar_PDB(double *vector_posvel, int N, double L, FILE *fs){

  double s = 9; //s es un factor de escala y tiene que estar entre 0 y 9.9999 para que no se vaya de lugar las ubicaciones

  fprintf(fs, "CRYST1%08.4f %08.4f %08.4f %06.2f %06.2f %06.2f\n",s,s,s,90.0,90.0,90.0);

  for(int i=0; i<N; i++){
    Grabar_Particula_PDB(vector_posvel,N,L,fs,i,s);
  }
  fprintf(fs,"END\n");

  return 0;

}

int Grabar_Particula_PDB(double *vector_posvel, int N, double L, FILE *fs, int j, double s){

  char atom[7]= "ATOM  \0";
  char blank[19] = "N                 \0";

  fprintf(fs,"%s%06d%s%.5f %.5f %.5f\n",atom,j+1,blank,vector_posvel[j]*s/L,vector_posvel[j+N]*s/L,vector_posvel[j+2*N]*s/L);

  return 0;

}
