#ifndef AVANZAR_H
#define AVANZAR_H

int Verlet(double *vector_posvel, double *vector_fuerza, int N,
            double *LUTF, double Ntabla, double m, double h,double L);
int Calcular_Fuerzas(double *vector_posvel, double *vector_fuerza, int N, double *LUTF, int Ntabla, double L);
int Verlet_pos(double *vector_posvel, double *vector_fuerza, int N,double m, double h, double L);
int Verlet_vel(double *vector_posvel, double *vector_fuerza,double *vector_fuerza_h, int N,double m, double h);

#endif
