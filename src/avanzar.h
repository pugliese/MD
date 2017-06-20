#ifndef AVANZAR_H
#define AVANZAR_H

int Verlet(double *vector_posvel, double *vector_fuerza, int N,
            double *LUTF, double Ntabla, double m, double h);
int Calcular_Fuerzas(double *vector_posvel, double *vector_fuerza, int N, double *LUTF, int Ntabla);
double Distancia(double *pos, int N, int i, int j);
double Valor_LUT(double *LUT, int Ntable, double R);
double Interpol(double *LUT, double R, double step);

#endif
