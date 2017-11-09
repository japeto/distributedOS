#include <stdio.h>
#include "mpi.h"

#define BLKSIZE = 100000

int main(int argc,char *argv[]){
	int start, end, size, rank;
	unsigned long sum, sumTotal;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	// Cada nodo de procesamiento tome un rango de numeros y los procese
	// Pueden ser N nodos, cada uno tomara bloques 
	// De a la cantidad de nodos
	start = rank * (BLKSIZE / size) + 1; 
	if(rank==(size-1)){ // Si es el ultimo nodo 
		end = BLKSIZE;  // le toco hasta el final -> BLKSIZE
	}else{
		end = start + (BLKSIZE / size) - 1; // Si no es el ultimo truco: calcule hasta donde va
											// De acuerdo a la cantidad de nodos
	}
	sum = 0; // inicializo en 0, antes no se que habia en estas var :)
	sumTotal=0; // inicializo en 0 
	int i; // para el for
	for(i=start; i<= end; i++){ // Todos vamos a sumar, esa es la tarea
	    sum = sum +i;           // Lo importante son los rangos que le tocan a cada nodo
	}
	// mensaje para analisis de los nodos
	printf("\nRank: %d, sum: %d, sumTotal: %d, start: %d, end: %d\n", rank, sum, sumTotal, start, end);
    // Recupero las sumas en cada nodo para luego realizar la suma total
	MPI_Reduce(&sum, &sumTotal, 1 , MPI_UNSIGNED_LONG, MPI_SUM , 0 , MPI_COMM_WORLD);
	// El nodo Master o "0", indica el total por la salida estandar
	if(rank==0){
		printf ("Master %d \tTotal: %lu\n", rank, sumTotal);
	}
	// Termina la ejecucion
	MPI_Finalize();
	return 0;
}



