#include <stdio.h>
#include <stdlib.h>

#define N 10    /* Numero di particelle */
#define L 1             /* Lunghezza intervallo */

double  intervallo;

double  tcoll;
int             icoll;




struct particella {

double m;
double x,v;
double dx,dv;
double dt;
} p[N+1];





/* DICHIARAZIONE FUNZIONI */
void init_struct        ( struct particella *p, int dim );
void print                      ( struct particella *p, int dim );
void search_tcoll ( struct particella *p, int dim );
void h                          (int n);








int main () {


intervallo=(double)(L)/(double)(N);





init_struct(p,N);



search_tcoll (p,N);
print(p,N);

}











        /* ------- */

/* F U N Z I O N I */

        /* ------- */




/* Sintassi funzioni:    Azione_Oggetto (variabili) {}    */









/* INIZIALIZZAZIONE */  /* Inizializza le particelle con le condizioni
iniziali */
void init_struct ( struct particella *p, int dim ) {

int i;


if(0) {/* PARTICELLA 0 */
(p)->m  = 9.0 ;
(p)->x  = intervallo/2 ;
(p)->dx = (p)->x;
(p)->v  = 0;
(p)->dv=0;
(p)->dt=0;
/* ---------- - */}




for (i=0; i<dim; i++) {

/*      m               */                      if (i%2 == 0) (p+i)->m = 9.0; else (p+i)->m = 1.0;
/*      x               */                      (p+i)->x        = intervallo*i + intervallo/2;
/*      dx      */              (p+i)->dx       = (p+i)->x - (p+i-1)->x;
/*      v               */                      (p+i)->v        = 2*(rand() / (double)(RAND_MAX) - 0.5);
/*      dv      */              (p+i)->dv       = (p+i)->v - (p+i-1)->v;
/*      dt      */              (p+i)->dt       = - (p+i)->dx / (p+i)->dv;
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










/* RICERCA */

void search_tcoll ( struct particella *p , int dim ) {

int i;
double tcoll_aux, icoll_aux;

/* Cerca il primo positivo */

dt_aux = p(i+0);






}







/* --------------------------------  GESTIONE   --------------------------*/



/* :::::::: PRINT :::::::::: */

void print ( struct particella *p, int dim ) {

int i;


printf("n \t m \t\t x \t\t dx \t\t v \t\t dv \t\t dt\n\n"); /* Testata */


for (i=0; i<dim+1; i++) {

printf("%d\t%lf\t  %lf \t  %lf \t  %lf \t %lf \t%lf \n", i, (p+i)->m,
(p+i)->x, (p+i)->dx, (p+i)->v, (p+i)->dv, (p+i)->dt);

}

printf("\n***/***La particella %d collide in %lf\n", icoll, tcoll);
}

/* ::::::: ----- ::::::::::: */



/* :::::: DEBUG-HELP :::::::::::: */

void h (int n) { printf("\n\n::::%d::::\n\n", n); }

/* :::::: ---------- :::::::::::: */
