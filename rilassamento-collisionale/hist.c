/* :::: FUNZIONE ISTOGRAMMA :::: */

/* Chiede in entrata un puntatore (input) ad un array double contenente i dati da istogrammare con relativa dimensione intera. Chiede in entrata due puntatori a due vettori vuoti (con relativa dimensione) che dovranno contenere uno (output_x) gli intervalli di campionamento [ovvero l'asse x del grafico Istogramma], l'altro (output_y) i valori di campionamento del vettore input [l'asse y dell'Istogramma]. */
		  
void hist_fill ( 
/* 	INPUT		*/	double *input, int dim_input, 
/* 	OUTPUT		*/	double *output_x, int *output_y, int dim_output, 
/* 	GESTIONE	*/	double a, double b
)	{

int i,j;
double delta;

delta = (b-a)/(double)(dim_output);

for (i=0; i<dim_input ;i++) { 
	
	for (j=0; j<dim_output; j++) {

		*(output_x + j )= a + delta*j;
		if ( *(input+i) >= a + delta*j && *(input+i) < a+delta*(j+1) )  *(output_y+j) = *(output_y+j)+1;
}}


}
