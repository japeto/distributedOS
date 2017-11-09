#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N_DECIMALES 1000000 // decimales a aproximar
#define PI 3.14159265358979323846 // valor de PI desde wikipedia

double get_coord(){
	double aux=100.0*((double)(rand())/RAND_MAX);
	aux=aux - (int)(aux);
	return aux;
}
int main(int argc,char *argv[]){
	int size, rank;
	int pi_value, error, counter;  //
	int in_circle, out_circle; //
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank != 0){
		for(i=0;i<N_DECIMALES;i++){
			x=get_coord(); //
			y=get_coord(); //
			if((x*x + y*y) <= 1) {	
				++counter; //
			}
		}
	}

    MPI_Reduce(&counter, &in_circle , 1 , MPI_UNSIGNED_LONG, MPI_SUM , 0 , MPI_COMM_WORLD );  
    MPI_Reduce(&N_DECIMALES, &out_circle, 1 ,MPI_UNSIGNED_LONG, MPI_SUM , 0 , MPI_COMM_WORLD );
    out_circle -= N_DECIMALES // Va 

	if(rank==0){
		pi_value = 4.0 * ((double)in_circle/(double)out_circle);
		error = pi_value - PI;
		printf("[VALOR DE PI] = %.15f \t",PI);
		printf("[VALOR CALCULADO DE PI] = %.15f \t",pi_value);
		printf("[ERROR (PI-CALCULADO)] = %.15f \t", error);
		printf("\n");
		printf("[DECIMALES] = %d \t", in_circle);
		printf("[ERROR DECIMALES] = %d \t", (out_circle - in_circle));
	}
	// Termina la ejecucion
	MPI_Finalize();
	return 0;

}