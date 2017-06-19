#ifndef TABLAS_H
#define TABLAS_H
double Lennard_Jones(double r);
double* LUT_P(int N);
double Fuerza_Lennard_Jones(double r);
double* LUT_F(int N);

int guardar_tablas(double *LUTP, double *LUTF, int N);
int leer_tablas(double **LUTP, double **LUTF);
#endif
