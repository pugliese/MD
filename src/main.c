#include "avanzar.h"
#include "inicializar.h"
#include "tablas.h"
#include "funciones.h"
#include "observables.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char const *argv[]) {
// Mi idea es tener la variable opcion que es un caracter que puede hacer referencia a las distintas opciones
// Por ahora, la unica opcion es t para generar una nueva tabla
  char opcion;
  if(argc>1){
    sscanf(argv[1], "%c", &opcion);
  }else{
    opcion ='s';
  }
  if(opcion=='t'){  // Para generar la tabla, luego del .e escribimos t para que sepa que
    int N;        // debe generar la tabla seguido de la cantidad de puntos que queremos
    sscanf(argv[2],"%d", &N);
    double* LUT1 = LUT_P(N);
    double* LUT2 = LUT_F(N);
    guardar_tablas(LUT1,LUT2,N);
    free(LUT1);
    free(LUT2);
  }if(opcion =='s'){
/*
    int N=13*13*13;
    double rho=0.8442;
    double m=1;
    double T=0.728;
    double L = pow(N/rho,1./3);
    double h = 1E-4;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));*/
    double* LUTF ;
    double* LUTP ;

    int Ntable = leer_tablas(&LUTP, &LUTF);
/*
    srand(time(NULL));

    Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);*/
/*
    for (int i=0;i<N;i++) {
      printf("particula %d \n",i);
      printf("r : %f %f %f \n",vector[i],vector[i+N],vector[i+2*N]);
      printf("v : %f %f %f \n",vector[i+3*N],vector[i+4*N],vector[i+5*N]);
    }
*/
/*
    double PromVel = 0;
    for(int i = 0;i<3*N;i++) PromVel = PromVel + vector[3*N+i]*vector[3*N+i]/(3*N);
    printf("promedio velocidad = %f\n",PromVel);
    Verlet(vector,&vector_fuerza,N,LUTF,Ntable,m,h,L);

    free(vector);
    free(vector_fuerza);
    free(LUTP);
    free(LUTF);*/

    double *vector = malloc(6*2*sizeof(double));
    double *vector_fuerza = malloc(3*2*sizeof(double));
    double L = 12;
    // Posiciones
    vector[0] = 3;
    vector[2] = 3;
    vector[4] = 3;
    vector[1] = 4.5;
    vector[3] = 3;
    vector[5] = 3;
    // Velocidades
    vector[6] = 0;
    vector[8] = 0.1;
    vector[10] = 0;
    vector[7] = 0;
    vector[9] = -0.1;
    vector[11] = 0;

    int Np = 20000;
    Calcular_Fuerzas(vector,vector_fuerza,2,LUTF,Ntable,L);
    double* X1 = malloc(Np*sizeof(double)/10);
    double* Y1 = malloc(Np*sizeof(double)/10);
    double* X2 = malloc(Np*sizeof(double)/10);
    double* Y2 = malloc(Np*sizeof(double)/10);
    double *Ecin =  malloc(Np*sizeof(double));
    double *Epot =  malloc(Np*sizeof(double));
    X1[0] = vector[0];
    X2[0] = vector[1];
    Y1[0] = vector[2];
    Y2[0] = vector[3];
    Ecin[0] = Energia_Cinetica(vector, 2, 1);
    Epot[0] = Energia_Potencial(vector,  2,  LUTP,  Ntable,  L);
    for(int i=1;i<Np;i++){
      Verlet(vector,&vector_fuerza,2,LUTF, Ntable,1,1E-3,L);
      Ecin[i] = Energia_Cinetica(vector, 2, 1);
      Epot[i] = Energia_Potencial(vector,  2,  LUTP,  Ntable,  L);
      //printf("%lg -> (%lg, %lg, %lg)\n", Delta(vector,2,0,0,1,L),vector_fuerza[0],vector_fuerza[2],vector_fuerza[4]);
      /*if (i%10==0){
        X1[i/10] = vector[0];
        X2[i/10] = vector[1];
        Y1[i/10] = vector[2];
        Y2[i/10] = vector[3];
      }*/
    }/*
    printf("X1=[");
    for(int i=0;i<Np/10-1;i++){
      printf("%lg,", X1[i]);
    }
    printf("%lg];\n", X1[Np/10-1]);
    printf("X2=[");
    for(int i=0;i<Np/10-1;i++){
      printf("%lg,", X2[i]);
    }
    printf("%lg];\n", X2[Np/10-1]);
    printf("Y1=[");
    for(int i=0;i<Np/10-1;i++){
      printf("%lg,", Y1[i]);
    }
    printf("%lg];\n", Y1[Np/10-1]);
    printf("Y2=[");
    for(int i=0;i<Np/10-1;i++){
      printf("%lg,", Y2[i]);
    }
    printf("%lg];\n", Y2[Np/10-1]);
    printf("Z1=[");
    for(int i=0;i<Np-1;i++){
      printf("%lg,", Z1[i]);
    }
    printf("%lg];\n", Z1[Np-1]);
    printf("Z2=[");
    for(int i=0;i<Np-1;i++){
      printf("%lg,", Z2[i]);
    }
    printf("%lg];\n", Z2[Np-1]);*/
    FILE* fp = fopen("paja.txt", "w");
    for(int i=0;i<Np-1;i++){
      fprintf(fp,"%lg ", Ecin[i]);
    }
    fprintf(fp,"%lg\n", Ecin[Np-1]);
    for(int i=0;i<Np-1;i++){
      fprintf(fp,"%lg ", Epot[i]);
    }
    fprintf(fp,"%lg\n", Epot[Np-1]);
    free(X1);
    free(X2);
    free(Y1);
    free(Y2);
    free(vector);
    free(LUTP);
    free(LUTF);
    free(Ecin);
    free(Epot);

//----------------------------------------------------------------------------------


  }if(opcion =='a'){
    int secs = time(NULL);
    int N_pasos;
    sscanf(argv[2],"%d", &N_pasos);
    int N = 125;
    double rho=0.8442;
    double m=1;
    double T=0.728;
    double L = pow(N/rho,1./3);
    double h = 1E-4;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));
    double* LUTF;
    double* LUTP;

    int Ntable = leer_tablas(&LUTP, &LUTF);

    srand(time(NULL));

    Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);

    double* Ecin= malloc(N_pasos*sizeof(double));
    double* Epot= malloc(N_pasos*sizeof(double));
    Ecin[0] = Energia_Cinetica(vector, N, m);
    Epot[0] = Energia_Potencial(vector,  N,  LUTP,  Ntable,  L);
    for(int i=1;i<N_pasos;i++){
      Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
      Ecin[i] = Energia_Cinetica(vector, N, m);
      Epot[i] = Energia_Potencial(vector,  N,  LUTP,  Ntable,  L);
      if (i%1000==0) printf("Paso %d\n", i);
      // Algun observable mas //
    }
    FILE* fp = fopen("Energia_1a.txt", "w");
    fprintf(fp, "#Energias a %d pasos de Verlet\n#Cinetica:\n", N_pasos);
    for(int i=0;i<N_pasos-1;i++){
      fprintf(fp, "%lg ", Ecin[i]);
    }
    fprintf(fp, "%lg\n#Potencial:\n", Ecin[N_pasos-1]);
    for(int i=0;i<N_pasos-1;i++){
      fprintf(fp, "%lg ", Epot[i]);
    }
    fprintf(fp, "%lg\n", Epot[N_pasos-1]);
    fclose(fp);
    free(vector);
    free(vector_fuerza);
    free(LUTP);
    free(LUTF);
    free(Ecin);
    free(Epot);
    secs = time(NULL)-secs;
    printf("%d hs %d mins, %d segs\n", secs/3600, (secs/60)%60, secs%60);

//----------------------------------------------------------------------------------

  }if(opcion =='g'){
    int secs = time(NULL);
    int N_pasos = 1000;
    int N = 512;
    double rho=0.8442;
    double m=1;
    double T=15;
    sscanf(argv[2],"%lg",&rho);
    sscanf(argv[3],"%lg",&T);
//    double L = pow(N/rho,1./3);
    double h = 5E-4;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));
    double* LUTF;
    double* LUTP;
    int Q_pasos = 100 ;
    int Ntable = leer_tablas(&LUTP, &LUTF);

    srand(time(NULL));

    double L=Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);

    double dr = 0.01*pow(1.0/rho,1./3);

    printf("dr=%lg, L=%lg, rho=%lg, T=%lg  \n",dr,L,rho,T );

    int nhist= ceil (L/dr);

    double* hist_gr;
    double* himean = malloc(nhist*sizeof(double));
    for (int i=0; i<nhist;i++) {
      himean[i]=0 ;
    }

    for(int q=0;q<Q_pasos;q++){
      for(int i=1; i<N_pasos;i++){
        Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
      }
        hist_gr = Gr(vector, N,rho, dr, L,nhist);
        for (int m=0;m<nhist;m++){
          himean[m] = himean[m] + hist_gr[m]/Q_pasos;
        }
        printf("Paso %d\n", q+1);

    }

    FILE* fp = fopen("Histo_gr.txt", "w");
    fprintf(fp, "#g(r)\n");
    for(int i=0;i<nhist/2;i++){
      fprintf(fp, " %lg \n", himean[i]);
    }

    fclose(fp);

    free(vector);
    free(vector_fuerza);
    free(LUTP);
    free(LUTF);
    free(hist_gr);
    //free(Ecin);
    //free(Epot);
    secs = time(NULL)-secs;
    printf("%d hs %d mins, %d segs\n", secs/3600, (secs/60)%60, secs%60);
  }

//----------------------------------------------------------------------------------//

  if(opcion =='v'){ // Probando la funcion reescalar
    double T=1;
    double T_deseada =4 ;

    int secs = time(NULL);
    int N = 8;
    double rho=0.8442;
    double m=1;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));
    double* LUTF;
    double* LUTP;
    int Ntable = leer_tablas(&LUTP, &LUTF);
    srand(time(NULL));

    Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);

    printf("T=%lg, T_deseada=%lg, rho=%lg, v=%lg \n",T,T_deseada,rho,vector[3*N+10]);

    Reescalar_Vel(vector,N,T,T_deseada);

    printf("T=%lg, T_deseada=%lg, rho=%lg, v=%lg,\n",T,T_deseada,rho,vector[3*N+10]);

    secs = time(NULL)-secs;
    printf("%d hs %d mins, %d segs\n", secs/3600, (secs/60)%60, secs%60);
  }

  if(opcion == 'b'){
    double T=0.728;
    int n, k;
    sscanf(argv[2],"%d",&n);
    sscanf(argv[3],"%d",&k);

    int secs = time(NULL);
    int N = 125;
    int Term = k;
    double rho=0.8442;
    double m=1;
    double h = 1.0E-4;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));
    double* Ecin = malloc(n*sizeof(double));
    double* Epot = malloc(n*sizeof(double));
    double* Ecin_k = malloc(k*sizeof(double));
    double* Epot_k = malloc(k*sizeof(double));
    double* LUTF;
    double* LUTP;
    int Ntable = leer_tablas(&LUTP, &LUTF);
    srand(time(NULL));

    double L = Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);

    for (int i=0;i<Term;i++){
      Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
    }
    for(int i=0;i<n;i++){
      for(int j=0;j<k;j++){
        Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
        Ecin_k[j] = Energia_Cinetica(vector, N, m);
        Epot_k[j] = Energia_Potencial(vector,  N,  LUTP,  Ntable,  L);
      }
      Ecin[i] = esperanza(Ecin_k,k);
      Epot[i] = esperanza(Epot_k,k);
      printf("Paso %d\n", i);
    }

    FILE* fp = fopen("Cinetica-Potencial.txt", "w");
    for(int i=0;i<n;i++){
      fprintf(fp, "%lg ", Ecin[i]);
    }
    fprintf(fp, "\n");
    for(int i=0;i<n;i++){
      fprintf(fp, "%lg ", Epot[i]);
    }
    fprintf(fp, "\n");
    printf("Cinetica media: %lg  Varianza: %lg\n", esperanza(Ecin,n), Varianza(Ecin,n));
    printf("Potencial media: %lg  Varianza: %lg \n", esperanza(Epot,n), Varianza(Epot,n));
    secs = time(NULL)-secs;
    printf("%d hs %d mins, %d segs\n", secs/3600, (secs/60)%60, secs%60);

    fclose(fp);
    free(Ecin);
    free(Epot);
    free(Ecin_k);
    free(Epot_k);
    free(vector);
    free(vector_fuerza);
    free(LUTP);
    free(LUTF);
  }
// Se pasa la cantidad de temperaturas, la minima, la maxima, la cantidad de pasos y el tiempo de termalizacion
  if(opcion=='c'){
    int N_pasos, Term, Cant_T;
    double Tmin, Tmax;
    sscanf(argv[2],"%d",&Cant_T);
    sscanf(argv[3],"%lg",&Tmin);
    sscanf(argv[4],"%lg",&Tmax);
    sscanf(argv[5],"%d",&N_pasos);
    sscanf(argv[6],"%d",&Term);
    double T=Tmin;

    int secs;
    int N = 125;
    double rho=0.8442;
    double m=1;
    double h = 1.0E-4;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));
    double* Ecin = malloc(N_pasos*sizeof(double));
    double* Epot = malloc(N_pasos*sizeof(double));
    char nombre[50];
    double* LUTF;
    double* LUTP;
    int Ntable = leer_tablas(&LUTP, &LUTF);
    srand(time(NULL));


    for(int l=0;l<Cant_T;l++){
      secs = time(NULL);
      T = Tmin+l*(Tmax-Tmin)/(Cant_T-1);
      double L = Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);
      for(int i=0;i<Term;i++){
        Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
      }
      for(int i=0;i<N_pasos;i++){
        Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
        Ecin[i] = Energia_Cinetica(vector, N, m);
        Epot[i] = Energia_Potencial(vector,  N,  LUTP,  Ntable,  L);
      }
      sprintf(nombre,"Energia_T_%4.4f.txt", T);
      FILE* fp = fopen(nombre, "w");
      fprintf(fp, "#Cinetica:\n");
      for(int i=0;i<N_pasos;i++){
        fprintf(fp, "%lg ", Ecin[i]);
      }
      fprintf(fp, "\n#Potencial:\n");
      for(int i=0;i<N_pasos;i++){
        fprintf(fp, "%lg ", Epot[i]);
      }
      fprintf(fp, "\n");
      fclose(fp);
      secs = time(NULL)-secs;
      printf("Temperatura %lg en %d hs %d mins, %d segs\n", T, secs/3600, (secs/60)%60, secs%60);
    }
    free(vector);
    free(vector_fuerza);
    free(Ecin);
    free(Epot);
    free(LUTP);
    free(LUTF);

  }
  return 0;
}
