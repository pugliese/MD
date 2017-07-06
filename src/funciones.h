#ifndef FUNCIONES_H
#define FUNCIONES_H

double Delta(double *pos, int N, int comp, int i, int j, double L);
double Distancia(double *pos, int N, int i, int j, double L);
double Valor_LUT(double *LUT, int Ntabla, double R);
double Interpol(double *LUT, double R, double step);
int Reescalar_Vel(double *posvel,int N, double resca);
double Varianza(double *vector,int N);
double esperanza2(double *vector, int n);
double esperanza(double *vector, int n);
int rand_int(int a, int b);


#endif
