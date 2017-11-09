#include <mpi.h>
#include <stdio.h>

#define MAXARRAY 20
/**
* MPI_Custom_Bcast
* int MPI_Bcast( void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm )
*
* Implements a custom broadcasts a message from the process 
* with rank "root" to all other processes of the communicator
* This usage MPI_Recv and MPI_Send
*/
void MPI_Custom_Bcast (void *data, int nelem, MPI_Datatype dt, int root, MPI_Comm comm){
	int size, rank, tag=1;
	MPI_Status Stat;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank!=root){ // Si es la raiz reciba el mensjae
		MPI_Recv(data, ne, dt, root, tag, comm, &Stat);
	}else{ // Si es otro nodo
		for(int i=0; i< size; i++){ // su tarea es enviarselo a todos
			if(i!=root){ // menos a usted mismo
				MPI_Send(data, ne, dt, i, tag, comm);
			}
		}
	}	
}

int iniarray(int n, int *array) {
	int i;
	for (i = 0; i < n; i++) 
		array[i] = i;
	return i;
}

void printarray(int n, int *array) {
	int i = 0;
	printf("[ ");
	for (; i < n; i++) {
		if (i == n - 1) 
			printf("%d ", array[i]);
		else
			printf("%d, ", array[i]);
	}
	printf("]\n");
}
int main(int argc, char** argv) {
	int arreglo[MAXARRAY];
	int rank;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) {
		iniarray(MAXARRAY, arreglo);
		//MPI_Bcast(arreglo, MAXARRAY, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Custom_Bcast(arreglo, MAXARRAY, MPI_INT, 0, MPI_COMM_WORLD);
	} else {
		if (rank == 1) {
			printf("Imprimiendo arreglo desde [%d]\n", rank);
			printarray(MAXARRAY, arreglo);
		}
		//MPI_Bcast(arreglo, MAXARRAY, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Custom_Bcast(arreglo, MAXARRAY, MPI_INT, 0, MPI_COMM_WORLD);
		if (rank == 1) {
			printf("Imprimiendo arreglo desde [%d]\n", rank);
			printarray(MAXARRAY, arreglo);
		}
	}
	MPI_Finalize();
	return 0;
}