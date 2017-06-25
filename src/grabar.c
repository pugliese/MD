#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grabar.h"

int Grabar_Pos(double *vector_posvel, int N, FILE *fs){

  for(int i=0; i<N; i++){
    Grabar_Particula(vector_posvel,N,fs,i);
  }
  fprintf(fs,"END\n");

  return 0;

}

int Grabar_Particula(double *vector_posvel, int N, FILE *fs, int j){

  char atom[6]="ATOM  ";
  char number[7];
  char blank[19];
  char x[9];
  char y[9];
  char z[9];
  char aux[50];

  sprintf(number,"%d",j+1);
  if(strlen(number)<6) for(int i = strlen(number);i<6;i++) number[i] = ' ';
  number[6] = '\0';

  for(int i=0;i<18;i++) blank[i] = ' ';
  blank[18] = '\0';

  sprintf(aux,"%f",vector_posvel[j]);
  if(strlen(aux)<7) for(int i = strlen(aux);i<7;i++) aux[i] = ' ';
  else for(int i=0;i<7;i++) x[i]=aux[i];
  x[7] = ' ';
  x[8] = '\0';


  sprintf(aux,"%f",vector_posvel[j+N]);
  if(strlen(aux)<7) for(int i = strlen(aux);i<7;i++) aux[i] = ' ';
  else for(int i=0;i<7;i++) y[i]=aux[i];
  y[7] = ' ';
  y[8] = '\0';

  sprintf(aux,"%f",vector_posvel[j+2*N]);
  if(strlen(aux)<7) for(int i = strlen(aux);i<7;i++) aux[i] = 'a';
  else for(int i=0;i<7;i++) z[i]=aux[i];
  z[7] = ' ';
  z[8] = '\0';

  fprintf(fs,"%s%s%s%s%s%s\n",atom,number,blank,x,y,z);

  return 0;

}
