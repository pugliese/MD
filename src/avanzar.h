#ifndef AVANZAR_H
#define AVANZAR_H

int Verlet(double *vector_posvel, double *vector_fuerza, int N,
            double *LUTF, double Ntabla, double m, double h);
int Calcular_Fuerzas(double *vector_posvel, double *vector_fuerza, int N, double *LUTF, int Ntabla);

#endif
