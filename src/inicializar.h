#ifndef INICIALIZAR_H
#define INICIALIZAR_H
double Inicializar (double* vector_posvel,double* vector_fuerza,int N,double* LUTF,int Ntable,double rho, double m, double T);
double Llenar_Pos (double* vector,int N,double rho);
int Llenar_Vel (double* vector,int N,double rho,double m, double T);
double Rand_Gauss (double m, double T);

#endif
