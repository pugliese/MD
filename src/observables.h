#ifndef OBSERVABLES_H
#define OBSERVABLES_H

float Energia_Potencial(double* pos_vel, int N, double* LUT_P, int Ntabla, double L);
float Energia_Cinetica(double* pos_vel, int N, double m);

#endif
