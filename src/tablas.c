#include "tablas.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double Lennard_Jones(double r){
  double r6 = r*r*r;
  r6 = r6*r6;
  return (1.0/r6-1)*4.0/r6;
}

// Acá mezclamos 2 métodos, el potencial es desplazado un valor
// constante para que solo sea necesario un spline de grado 2
// Aclaro esto porque el valor minimo ahora es -1+So-Fo/4 ~ -1
// Para que se den una idea, So-Fo/4 ~ 7E-3
double* LUT_P(int N){
  double step = 3.0/N;
  int m= floor(2.5/step);
  double r=0;
  double* res=malloc(N*sizeof(double));
  double Fo = Fuerza_Lennard_Jones(2.5);
  printf("%lg\n",Fo );
  double So = Lennard_Jones(2.5);
  for(int i=0;i<m;i++){
    r = r+step;
    res[i] = Lennard_Jones(r)-So+Fo/4; // Corro para que V(2.5) = -Fo/4 (lo que vale la interpolacion)
  }
  for(int i=m;i<N;i++){
    r = r+step;
    res[i] = Fo*(r-3.0)*(r-3.0);  // En r=2.5 vale Fo*(0.5)² = -Fo/4
  }
  return res;
}


double Fuerza_Lennard_Jones(double r){  // Devuelve el módulo de la fuerza
  double r6 = r*r*r;
  r6 = r6*r6;
  return (2.0/r6-1)*24.0/(r*r6);
}

double* LUT_F(int N){    // Tabla con los modulos de la fuerza de Lennard-Jones
  double step = 3.0/N;
  int m= floor(2.5/step);
  double r=0;
  double* res=malloc(N*sizeof(double));
  for(int i=0;i<m;i++){
    r = r+step;
    res[i] = Fuerza_Lennard_Jones(r);
  }
  double Fo = Fuerza_Lennard_Jones(2.5);
  for(int i=m;i<N;i++){
    r = r+step;
    res[i] = -2*Fo*(r-3.0);
  }
  return res;
}

int guardar_tablas(double *LUTP, double *LUTF, int N){
  FILE* fp = fopen("tablas.txt", "w");
  fprintf(fp, "%d\n", N);   // Guardo la longitud de la tabla en el primer renglon
  for(int i=0;i<N;i++){
    fprintf(fp, "%f ", LUTP[i]);  // Guardo la tabla con potenciales separadas por espacios
  }
  fprintf(fp, "\n"); // Salto de linea para que sepa que termino una tabla
  for(int i=0;i<N;i++){
    fprintf(fp, "%f ", LUTF[i]); // Guardo la tabla con fuerzas separadas por espacios
  }
  fclose(fp);
  return 0;
}

int leer_tablas(double **LUTP, double **LUTF){
  FILE* fp = fopen("tablas.txt","r");
  int N,k=0;
  k=fscanf(fp,"%d\n",&N); // Leo la longitud de mi tabla
  double* tabP = malloc(N*sizeof(double));
  double* tabF = malloc(N*sizeof(double));
  double aux;
  for(int i=0;i<N;i++){
    k=k+fscanf(fp,"%lg",&aux);
    tabP[i]=aux;
  }
  for(int i=0;i<N;i++){
    k=k+fscanf(fp,"%lg",&aux);
    tabF[i]=aux;
  }
  fclose(fp);
  *LUTF = tabF;
  *LUTP = tabP;
  if (k==2*N+1){
    return N;
  }else{ // Si no lei 2*N elementos, algo salió mal y devuelvo 0
    printf("Error al leer tabla: %d en lugar de %d\n",k,2*N+1);
    return 0;
  }
}

/*int main(int argc, char **argv){
  if (argc==2){
    int N;
    sscanf(argv[1],"%d", &N);
    printf("1\n");
    double* LUT1 = LUT_P(N);
    double* LUT2 = LUT_F(N);
    guardar_tablas(LUT1,LUT2,N);
    printf("2\n");
    double* LUT3;
    double* LUT4;
    leer_tablas(&LUT3, &LUT4);
    printf("3\n");
    for(int i=0;i<N;i++){
      printf("%lg %lg\n", LUT3[i], LUT4[i]);
    }
    printf("5\n");
    free(LUT1);
    free(LUT2);
    free(LUT3);
    free(LUT4);
  }else{
    printf("Error: Introduzca cantidad de puntos\n");
  }
  return 0;
}*/
