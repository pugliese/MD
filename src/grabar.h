#ifndef GRABAR_H
#define GRABAR_H

int Grabar_PDB(double* vector_posvel, int N, double L, FILE *fs);
int Grabar_Particula_PDB(double *vector_posvel, int N, double L, FILE *fs, int j, double s);

#endif
