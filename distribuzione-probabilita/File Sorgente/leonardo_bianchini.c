/* leonardo bianchini */ /* 16 Novembre 2011 */

/* Simulazione lancio Moneta */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "leonardo_bianchini.h"

#define N 	50			/* 	Numero			*/
#define R 	10000 			/*	Ripetizioni		*/
#define OBJ 	(double)(1)/(double)(2)	/* 	Tipo di oggetto:moneta	*/



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


/* Stampo data sul file sper.dat */

FILE *fp;
fp = fopen("sper.dat","w");
for (i=0; i<N+1; i++) fprintf(fp,"%d\t%lf\n", i, data[i]);
fclose(fp);


/* Stampo la distribuzione teorica sul file teor.dat */

  
FILE *fp2;
fp2 = fopen("teor.dat","w");
for (i=0; i<N+1; i++) fprintf(fp2,"%d\t%lf\n", i, probabilita(N,i,OBJ,OBJ));
fclose(fp2);





}
