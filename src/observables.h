#ifndef OBSERVABLES_H
#define OBSERVABLES_H

double Energia_Potencial(double* pos_vel, int N, double* LUT_P, int Ntabla, double L);
double Energia_Cinetica(double* pos_vel, int N, double m);
double Presion (double P, double Ecin,int N, double rho);
double* Gr(double* pos,int N, double dr, double L);

#endif
