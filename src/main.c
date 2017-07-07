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
    int N=300000;  // debe generar la tabla seguido de la cantidad de puntos que queremos
    if(argc>2){
        sscanf(argv[2],"%d", &N);
    }
    double* LUT1 = LUT_P(N);
    double* LUT2 = LUT_F(N);
    guardar_tablas(LUT1,LUT2,N);
    free(LUT1);
    free(LUT2);
    printf("Generada con %d puntos\n", N);
  }if(opcion =='s'){
    printf("\nSi no fue por pajero, aca esta la informacion:\n\n");
    printf("\t 't' \t Genera las LookUp Tables, pide cantidad de puntos (Default: 300000)\n");
    printf("\t 'a' \t Ejecuta el punto 1.a), pide cantidad de pasos de Verlet\n");
    printf("\t 'b' \t Ejecuta el punto 1.b), pide los parametros de grano grueso (cantidad de promedios y ancho de intervalo)\n");
    printf("\t 'c' \t Energias en funcion del tiempo; se pasa la cantidad de temperaturas, la minima, la maxima, la cantidad de pasos y el tiempo de termalizacion\n");
    printf("\t '2' \t Ejecuta el punto 2, pide rho\n");
    printf("\t '3' \t Ejecuta el punto 3, pide rho\n\n");
  }

//----------------------------------------------------------------------------------


  if(opcion =='a'){
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
  }
//----------------------------------------------------------------------------------//

  if(opcion == 'b'){
    double T=1.50728;
    int n, k;
    sscanf(argv[2],"%d",&n);
    sscanf(argv[3],"%d",&k);

    int secs = time(NULL);
    int N = 512;
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
    double* vel = malloc(sizeof(double)*3*N);
    srand(time(NULL));

    double L=Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);
    for (int i=0;i<3*N;i++){
      vel[i]=vector[i+3*N];
    }

    printf("Tini = %lg ; KT/m = %lg \n",T ,Energia_Cinetica(vector,N,m)*2.0/(3*N));

    for (int i=0;i<Term;i++){
      Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
    }
    for (int i=0;i<3*N;i++){
      vel[i]=vector[i+3*N];
    }
    printf("Tini = %lg ; KT/m = %lg \n",T ,Energia_Cinetica(vector,N,m)*2.0/(3*N));

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
    for(int i=0;i<n;i++)fprintf(fp, "%lg ", Ecin[i]);
    fprintf(fp, "\n");
    for(int i=0;i<n;i++) fprintf(fp, "%lg ", Epot[i]);
    fprintf(fp, "\n");
    fclose(fp);

    printf("Cinetica media: %lg  Varianza: %lg\n", esperanza(Ecin,n), Varianza(Ecin,n));
    printf("Potencial media: %lg  Varianza: %lg \n", esperanza(Epot,n), Varianza(Epot,n));

    for (int i=0;i<3*N;i++){
      vel[i]=vector[i+3*N];
    }

    printf("Tini = %lg ; KT/m = %lg \n",T ,Energia_Cinetica(vector,N,m)*2.0/(3*N));

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
    int N_pasos, Term, Cant_T,N;
    double Tmin, Tmax;

    sscanf(argv[2],"%d",&Cant_T);
    sscanf(argv[3],"%lg",&Tmin);
    sscanf(argv[4],"%lg",&Tmax);
    sscanf(argv[5],"%d",&N_pasos);
    sscanf(argv[6],"%d",&Term);
    sscanf(argv[7],"%d",&N);

    double T=Tmin,Tposta;
    int secs;
    double rho = 0.8442;
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
        if(i%(N_pasos/20)==0) printf("N = %d, T = %f, Paso %d\n", N,T,i);
      }
      Tposta = esperanza(Ecin,N_pasos)*2.0/(3*N);
      printf("T = %lg -> E = %lg\n", Tposta,esperanza(Epot,N_pasos)+3*0.5*N*Tposta);
      sprintf(nombre,"Energia_T_%4.4f_N_%d.txt", T, N);
      FILE* fp = fopen(nombre, "w");
      fprintf(fp, "#T = %f\n#N = %d\n", T, N);
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


  //----------------------------------------------------------------------------------//
/*
  if(opcion == '2'){
    double T=2.0;
    int n=100;
    double rho=0.8;
    sscanf(argv[2],"%lg",&rho);
    int secs = time(NULL);
    int N = 125;
    int Term = 2000;
    double m=1;
    double h = 1.0E-4;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));
    double* Ecin = malloc(n*sizeof(double));
    double* Epot = malloc(n*sizeof(double));
    double* Etot = malloc(n*sizeof(double));
    double* P = malloc(n*sizeof(double));

    double* LUTF;
    double* LUTP;
    int q_pasos = 100;
    int Ntable = leer_tablas(&LUTP, &LUTF);
    srand(time(NULL));

    double L=Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);
    double T_deseada;
    double Pex;

    for(int t=0;t<n;t++){
      Ecin[t]=0;
      Epot[t]=0;
      P[t]=0;
      for(int q=0;q<q_pasos;q++){
        for (int i=0;i<Term;i++){
          Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
        }
        Ecin[t] = Ecin[t] + Energia_Cinetica(vector,N,m)/q_pasos ;
        Epot[t] = Epot[t] + Energia_Potencial(vector,  N,  LUTP,  Ntable,  L)/q_pasos;
        Pex = Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
        P[t] = P[t] + Presion( Pex, Ecin[t], N ,rho)/q_pasos;
      }

      Etot[t] = Ecin[t]+Epot[t] ;
      T_deseada = T - (2.4/n);
      Reescalar_Vel(vector,N,sqrt(T/T_deseada));
      T = T_deseada;
      printf("temperatura = %f\n", T );
    }
    char name[100];
    sprintf(name, "2_E_P_%lg.txt", rho);
    FILE* fp = fopen(name, "w");
    for(int i=0;i<n;i++)fprintf(fp, "%lg ", Etot[i]);
    fprintf(fp, "\n");
    for(int i=0;i<n;i++) fprintf(fp, "%lg ", P[i]);
    fprintf(fp, "\n");
    fclose(fp);

    free(Ecin);
    free(Epot);
    free(Etot);
    free(P);
    free(vector);
    free(vector_fuerza);
    free(LUTP);
    free(LUTF);

    secs = time(NULL)-secs;
    printf("%d hs %d mins, %d segs\n", secs/3600, (secs/60)%60, secs%60);
  }*/

  if (opcion=='2'){
    double T=2.0;
    int n=33;
    int N_muestras=100;  // Cantidad de muestras por temperatura
    int pasos = 100;    // Cantidad de pasos (media) entre temperaturas; la cantidad es un valor aleatorio entre pasos/2 y 3*pasos/2
    int Term = 2000;
    double rho=0.8;
    if(argc>2) sscanf(argv[2],"%lg",&rho);
    if(argc>3) sscanf(argv[3],"%d",&n);
    if(argc>4) sscanf(argv[4], "%d", &N_muestras);
    if(argc>5) sscanf(argv[5], "%d", &pasos);
    if(argc>6) sscanf(argv[6], "%d", &Term);
    int secs = time(NULL);
    int N = 125;
    double m = 1;
    double h = 1.0E-4;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));
    double* Ecin = malloc(N_muestras*sizeof(double));
    double* Etot = malloc(N_muestras*sizeof(double));
    double* P = malloc(N_muestras*sizeof(double));

    double* LUTF;
    double* LUTP;
    int Ntable = leer_tablas(&LUTP, &LUTF);
    srand(time(NULL));

    double L = Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);
    double Vol = L*L*L;
    double T_deseada;
    double Pex;

// Termalizo el estado inicial (es el que mas tarda)
    printf("Calculando T = %1.3f\n", T);
    for(int i=0;i<Term;i++){
      Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
    }
    for(int i=0;i<N_muestras;i++){
      for(int j=1;j<rand_int(pasos/2,3*pasos/2);j++){  // Hago 1 menos porque avanzo despues (me evito actualizar Pex al pedo)
        Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
      }
      Pex = Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
      Ecin[i] = Energia_Cinetica(vector,N,m);
      Etot[i] = Ecin[i] + Energia_Potencial(vector,  N,  LUTP,  Ntable,  L);
      P[i] = Presion(Pex, Ecin[i], Vol);
    }
    char name[100];
    sprintf(name, "2_E_P_%1.3f.txt", rho);
    FILE* fp = fopen(name, "w");   // >>>>>>> LOS DATOS SE GUARDAN EN [COLUMNAS] <<<<<
    fprintf(fp, "#Cinetica #Total #Presion\n");
    for(int i=0;i<N_muestras;i++) fprintf(fp, "%lg %lg %lg\n", Ecin[i], Etot[i], P[i]);
    fclose(fp);

// Ahora lo hago para las demas temperaturas (Si solo es 1, no hace nada)
// No se si lo optimo seria abrir y cerrar el programa en cada paso o dejarlo abierto de una
    for(int t=0;t<n-1;t++){
      T_deseada = T - 1.6/(n-1);
      Reescalar_Vel(vector,N,sqrt(T_deseada/T));
      T = T_deseada;
      printf("Calculando T = %1.3f\n", T);
      for(int i=0;i<2*Term/n;i++){ // Termalizo menos, dependiendo del salto en T
        Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
      }
      for(int i=0;i<N_muestras;i++){
        for(int j=1;j<rand_int(pasos/2,3*pasos/2);j++){
          Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
        }
        Pex = Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
        Ecin[i] = Energia_Cinetica(vector,N,m);
        Etot[i] = Ecin[i] + Energia_Potencial(vector,  N,  LUTP,  Ntable,  L);
        P[i] = Presion( Pex, Ecin[i], Vol);
      }
      fp = fopen(name, "a");   // Uso "a" para appendear los nuevos datos al final
      for(int i=0;i<N_muestras;i++) fprintf(fp, "%lg %lg %lg\n", Ecin[i], Etot[i], P[i]);
      fclose(fp);
    }

    free(Ecin);
    free(Etot);
    free(P);
    free(vector);
    free(vector_fuerza);
    free(LUTP);
    free(LUTF);
    secs = time(NULL)-secs;
    printf("En total fueron %d hs %d mins, %d segs\n", secs/3600, (secs/60)%60, secs%60);
  }

  //----------------------------------------------------------------------------------

  if(opcion=='r'){
    srand(time(NULL));
    for(int i=0;i<10000;i++){

      printf("%d ", rand_int(1,10));
    }
    printf("\n");
  }

  if(opcion =='3'){
    int secs = time(NULL);
    int N_pasos = 1000;
    int N = 512;
    double rho=0.8442;
    double m=1;
    double T=1.5;
    sscanf(argv[2],"%lg",&rho);
    double h = 5E-4;
    double* vector = malloc(6*N*sizeof(double));
    double* vector_fuerza=malloc(3*N*sizeof(double));
    double* LUTF;
    double* LUTP;
    int Q_pasos = 10 ;
    int Ntable = leer_tablas(&LUTP, &LUTF);
    int Term = 2000;
    srand(time(NULL));

    double L=Inicializar(vector,vector_fuerza, N,LUTF,Ntable, rho, m,T);

    for(int i=0;i<Term;i++){
      Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
    }

/*    for(int i=0;i<2*Term/n;i++){ // Termalizo menos, dependiendo del salto en T
      Verlet(vector,&vector_fuerza,N,LUTF, Ntable,m,h,L);
    }
*/
    double dr = 0.01*pow(1.0/rho,1./3);

    printf("dr=%lg, L=%lg, T=%lg,rho=%lg  \n",dr,L,T,rho );

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

    char name[100];
    sprintf(name, "Histo_gr_%lg.txt", rho);

    FILE* fp = fopen(name, "w");
    fprintf(fp, "# x(rho), g(r), T=%lg \n", T);
    for(int i=0;i<nhist/2;i++){
      fprintf(fp, "%lg %lg \n", dr*i,himean[i]);
    }

    fclose(fp);

    free(vector);
    free(vector_fuerza);
    free(LUTP);
    free(LUTF);
    free(hist_gr);
    secs = time(NULL)-secs;
    printf("%d hs %d mins, %d segs\n", secs/3600, (secs/60)%60, secs%60);
  }
  return 0;
}
