#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "leonardo_bianchini.h"




/* Funzione di gestione generica */
/* Stampa velocemente un numero */
void p ( double a) {

printf(":: %lf ::\n",a );

}






/* Rende un numero casuale double compreso tra 0 e 1 */
double rnd () {

double y;

y = rand() / (double)(RAND_MAX);

return y;
}








/* :::: */ /* PROBABILITA' */ /* :::: */


/* n: numero di lanci						*/
/* m: numero di eventi verificati				*/
/* p: probabilità di (ottenere l'evento)			*/
/* q: probabilità di non ottenere l'evento (nel caso specifico)	*/ 

double probabilita ( int n, int m, double p, double q ) {

double y;


y = dist_bin(n,m) * pow(p,m) * pow(q,n-m) ;

return y;
}
/* :::: */ /* ----------- */ /* :::: */









/* :::: */ /* DISTRIBUZIONE BINOMIALE */ /* :::: */

double dist_bin ( int n, int m) {
int i,j;

double y;
y=1.;

if (m==0) return 1;


	for (i=0; i<=m-1; i++) {

		y = y * ( (double)(n-i) / (double)(m-i) );
}

return y;
}
/* :::: */ /* ----------- --------- */ /* :::: */


