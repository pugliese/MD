#ifndef OBSERVABLES_H
#define OBSERVABLES_H

double Energia_Potencial(double* pos_vel, int N, double* LUT_P, int Ntabla, double L);
double Energia_Cinetica(double* pos_vel, int N, double m);
double Presion (double P, double Ecin,int N, double rho);
double* Gr(double* pos,int N,double rho, double dr, double L,int nhist);
double Orden_verlet (double* pos, int N, double a);
double lambda (double* pos,int comp,int N,double a);


#endif
