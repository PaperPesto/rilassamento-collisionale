/* RILASSAMENTO COLLISIONALE - NOVEMBRE 2011 - BIANCHINI LEONARDO */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "hist.h"

#define N 2000	/* Numero di particelle */
#define L 1     	/* Lunghezza intervallo */
#define S 100000		/* Simulazioni	 	*/
#define M 500	/* Intervalli Hist 	*/ 
#define a -5.
#define b 5.

double  intervallo;

double  tcoll;





struct particella {

double m;
double x,v;
double dx,dv;
double dt;
} p[N+1];





/* DICHIARAZIONE FUNZIONI */
void init_struct        ( struct particella *p, int dim );
void print              ( struct particella *p, int dim );
int search_coll 	( struct particella *p, int dim );
void make_coll 		( struct particella *p, int icoll );
void refresh 		( struct particella *p, double time, int dim );
int hold_walls 		( struct particella *p );
void god 		( struct particella *p, int dim, int sim);
double ecin 		( struct particella *p, int icalc );
void loading 		( int sim_totali, int sim_attuale );
void init 		( void );
void h                  ( double n );


/* i 'dim' sono riferiti a N grande */






int main () {



/**/
init();
god(p,N,S);
/**/



double vel[N];
double interv[M];
int hist[M];


int i;





for (i=0;i<N;i++) vel[i]=(p+i)->v;
for (i=0;i<M;i++) {hist[i]=0; interv[i]=0;}






if(0) {/* Distribuzione velocità 2D */

for (i=0;i<N;i++) vel[i]=(p+i)->v;
for (i=0;i<M;i++) {hist[i]=0; interv[i]=0;}

hist_fill ( vel, N, interv, hist, M, a, b);


FILE* dist_vel;
dist_vel=fopen("dist_vel.dat", "w");
for (i=0;i<M;i++) fprintf(dist_vel, "%lf\t%d\n", interv[i], hist[i]);
fclose(dist_vel);
/* -------------------------- */ }






if(0) {/* Distribuzione velocità_s 2D */ /*Specie Pari massa 9*/

for (i=0;i<N/2;i++) vel[i]=(p+i*2)->v;
for (i=0;i<M;i++) {hist[i]=0; interv[i]=0;}

hist_fill ( vel, N, interv, hist, M, a, b);

FILE* dist_velp;
dist_velp=fopen("dist_velp.dat", "w");
for (i=0;i<M;i++) fprintf(dist_velp, "%lf\t%d\n", interv[i], hist[i]);
fclose(dist_velp);
/* ---------------------------- */ /*-----*/}





if(1) {/* Distribuzione velocità_s 2D */ /*Specie Dispari massa 1*/

for (i=0;i<N/2;i++) vel[i]=(p+i*2+1)->v;
for (i=0;i<M;i++) {hist[i]=0; interv[i]=0;}

hist_fill ( vel, N, interv, hist, M, a, b);

FILE* dist_veld;
dist_veld=fopen("dist_veld.dat", "w");
for (i=0;i<M;i++) fprintf(dist_veld, "%lf\t%d\n", interv[i], hist[i]);
fclose(dist_veld);
/* ---------------------------- */ /*-----*/ }





if(0) {/* Distribuzione velocità 3D */


double massa[M];
for (i=0;i<M;i++) if(i%2==0) massa[i]=9.; else massa[i]=1.;



hist_fill ( vel, N, interv, hist, M, a, b);


FILE* dist_vel3;
dist_vel3=fopen("dist_vel3.dat", "w");
for (i=0;i<M;i++) fprintf(dist_vel3, "%lf\t%d\t%lf\n", interv[i], hist[i], massa[i]);
fclose(dist_vel3);
/* -------------------------- */ }







}











       /* ------- */

/* F U N Z I O N I */

       /* ------- */




/* Sintassi funzioni:    Azione_Oggetto (variabili) { descrizione }    */









/* -----/\--------/\--------/\-------/\----  INIZIALIZZAZIONE   ----/\--------/\---------/\-------/\------*/


					/* ::::::::::: INIT_STRUCT ::::::::::::::: */
void init_struct ( struct particella *p, int dim ) {

int i; 


/* PARTICELLA 0 */
(p+0)->m  = 9.0 ;
(p+0)->x  = intervallo/2 ;
(p+0)->dx = (p+0)->x;
(p+0)->v  = 2*(rand() / (double)(RAND_MAX) - 0.5);
(p+0)->dv = (p+0)->v;
(p+0)->dt = -(p+0)->dx / (p+0)->dv;
/* ---------- - */




for (i=1; i<dim; i++) {

/*      m       */                      if (i%2 == 0) (p+i)->m = 9.0; else (p+i)->m = 1.0;
/*      x       */                      (p+i)->x        = intervallo*i + intervallo/2;
/*      dx      */              	(p+i)->dx       = (p+i)->x - (p+i-1)->x;
/*      v       */                      (p+i)->v        = 2*(rand() / (double)(RAND_MAX) - 0.5);
/*      dv      */              	(p+i)->dv       = (p+i)->v - (p+i-1)->v;
/*      dt      */              	(p+i)->dt       = - (p+i)->dx / (p+i)->dv;
}



/* MURO DX */
(p+dim)->m  =0 ;
(p+dim)->x  =1 ;
(p+dim)->dx = (p+dim)->x - (p+dim-1)->x;
(p+dim)->v  = 0;
(p+dim)->dv = (p+dim)->v - (p+dim-1)->v;
(p+dim)->dt = -(p+dim)->dx / (p+dim)->dv;
/* ---- -- */


}
					/* ::::::::::: ----------- ::::::::::::::: */


void init ( void ) {

intervallo = (double)(L)/(double)(N);

init_struct(p,N);

if(0) print(p,N);

}


/* -----\/--------\/--------\/-------\/----  INIZIALIZZAZIONE   ----\/--------\/---------\/-------\/------*/









/* -----v--------v--------v--------v---  CALCOLO   ------v-------v------v-----v-----v--- */


				/* :::::: SEARCH_COLL :::::::: */

int search_coll ( struct particella *p , int dim ) {

int i, found;
int icoll_aux;

		/* Cerca il primo numero positivo */
/* condizioni iniziali */
found = 0;
i=0;
/* -------------------- */

while ( found !=1 ) {
	if ( (p+i)->dt > 0 )  found=1; 
	i = i + 1; 
}

icoll_aux = i-1; /* Primo numero positivo */

		/* -------------------------------- */


for (i=icoll_aux; i<=dim; i++) {
	if ( (p + i)->dt > 0 && (p+i)->dt < (p+ icoll_aux)->dt )     icoll_aux = i;
}


tcoll = (p+icoll_aux)->dt; 
return icoll_aux;

}

				/* :::::: ------------ :::::::: */





				/* ::::::::: MAKE_COLL ::::::::: */
/* Esegue la collisione fra le particelle che si scontrano */
/* Esegue il cambiamento di velocità dovuto all'urto */

void make_coll ( struct particella *p, int icoll ) { 

double v1, v2;
double m1, m2;

/* Particella SX */ 	if ( icoll == 0 )   { (p+icoll)->v = -(p+icoll)->v; (p+icoll)->x=0; (p+icoll)->dt=0; } else {
/* Muro DX       */ 	if ( icoll == N )   (p+icoll-1)->v = -(p+icoll-1)->v; else {
					   
			


v1 = (p+icoll-1)->v;	 /* l'indice 1 è per la particella di sinistra n-1 */
v2 = (p+icoll)->v;	 /* l'indice 2 è per la particella di destra n */ 
m1 = (p+icoll-1)->m;
m2 = (p+icoll)->m;

(p+icoll-1)->v 	= 	( m2 / (m1+m2) ) * (v2-v1) + ( m1*v1 + m2*v2 ) / (m1+m2) ;
(p+icoll)->v 	=      -( m1 / (m1+m2) ) * (v2-v1) + ( m1*v1 + m2*v2 ) / (m1+m2) ;

}}
}

				/* ::::::::: -------- ::::::::: */





				/* ::::::::: REFRESH ::::::::: */
void refresh ( struct particella *p, double time, int dim ) {

int i;

double x0, v0;



/* Aggiornamento x */

	(p+0)->x = (p+0)->x + (p+0)->v * time; /* Particella SX */  	

for (i=1; i<=dim; i++) {

	x0 = (p+i)->x;
	v0 = (p+i)->v;
	
	(p+i)->x = x0 + v0 * time;
}

	

/* Aggiornamento dx */

	(p+0)->dx = (p+0)->x; /* Particella SX */  	

for (i=1; i<=dim; i++) {

	(p+i)->dx = (p+i)->x - (p+i-1)->x;
}



/* Aggiornamento v */
make_coll (p, search_coll(p,dim));

/* Aggiornamento dv */

	(p+0)->dv = (p+0)->v; /* Particella SX */  

for (i=1; i<=dim; i++) {

	(p+i)->dv = (p+i)->v - (p+i-1)->v;
}

/* Aggiornamento dt */ 

for (i=0; i<=dim; i++) {

	(p+i)->dt = - (p+i)->dx / (p+i)->dv;



/* ENERGIA CINETICA TOTALE */
double etot;
etot=0;

for (i=0;i<dim;i++) etot = etot + ecin (p,i);

if(0) h(etot);
/* --- */


}}
				/* ::::::::: ------- ::::::::: */





				/* :::::::::  GOD ::::::::: */
void god (struct particella *p, int dim, int sim) {

int i;

for (i=0; i<sim && hold_walls(p) !=1 ;i++) {

refresh (p, (p+search_coll(p,N))->dt ,N);



loading (sim,i);

}

if (hold_walls(p)==1) printf("DANGER\n");

}
				/* :::::::::  --- ::::::::: */




double ecin ( struct particella *p, int icalc ) { /*icalc è l'indice della particella di cui si vuole calcolare l'energia cinetica*/

double m,v;
m=(p+icalc)->m;
v=(p+icalc)->v;

return m*pow(v,2)*0.5;


}





/* ^-------^-------^-----^--------^-----  CALCOLO   ------^------^--------^------^---- */







/* ----v--------v--------v-----v-------  GESTIONE   -----v---------v------v------v------ */



					/* :::::::: PRINT :::::::::: */

void print ( struct particella *p, int dim ) {

int i;		


printf("n\t   m\t\t   x\t\t   dx\t\t   v\t\t   dv\t\t  dt\n\n"); /* Testata */

for (i=0; i<dim+1; i++) {

printf("%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", i, (p+i)->m,
(p+i)->x, (p+i)->dx, (p+i)->v, (p+i)->dv, (p+i)->dt);
}}



void loading ( int sim_totali, int sim_attuale ) {

printf ("%.1f\n", ( (float)(sim_attuale) / (float)(sim_totali)  )*100   );

}




					/* ::::::: ----- ::::::::::*/



/* -----/\--------/\--------/\-------/\----  DEBUGGING   ----/\--------/\---------/\-------/\------*/


void h (double n) { printf("\n\n::::%lf::::\n\n", n); }



				/* ::::::: HOLD_WALLS :::::::::: */
				/* Rende 1 se trova un errore, 0 finché tutto va bene */
int hold_walls ( struct particella *p ) {

if ( (p+0)->x < -0.00000001 || (p+N)->x > 1.00000001 )  return 1; else return 0;

}

/* -----/\--------/\--------/\-------/\----  DEBUGGING   ----/\--------/\---------/\-------/\------*/
