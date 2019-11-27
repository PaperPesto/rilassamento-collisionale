/* leonardo bianchini */ /* 16 Novembre 2011 */

/* Simulazione lancio Dado */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "leonardo_bianchini.h"

#define N 	20						/* 	Numero			*/
#define R 	10000 			/*	Ripetizioni		*/
#define OBJ	(double)(1)/(double)(6)	/* 	Tipo di oggetto: dado 	*/



int main() {
	

int i,j;

/* Inizializzazioni */

double data[N+1];		
for (i=0; i<N+1; i++) data[i]=0;

int count;


/* Simulo il lancio della moneta */

for (j=0; j<R; j++) {

count=0;

	for (i=0; i<N; i++) {  

		if ( rnd() < OBJ )  count++;  
	}

data[count]++;
}


/* Normalizzo data */

for (i=0; i<N+1; i++) data[i] = data[i]/(double)(R);


/* Stampo data */

if(0) for (i=0; i<N+1; i++) p(data[i]);


/* Stampo data sul file sper_dado.dat */

FILE *fp3;
fp3 = fopen("sper_dado.dat","w");
for (i=0; i<N+1; i++) fprintf(fp3,"%d\t%lf\n", i, data[i]);
fclose(fp3);


/* Stampo la distribuzione teorica sul file teor_dado.dat */

for (i=0;i<N+1;i++) {  
FILE *fp4;
fp4 = fopen("teor_dado.dat","w");
for (i=0; i<N+1; i++) fprintf(fp4,"%d\t%lf\n", i, probabilita(N,i,OBJ,1-OBJ));
fclose(fp4);

}



}
