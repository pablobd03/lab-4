#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 5
#define COLUMNAS 2 

void ordenarMatriz(int *matriz) {
	int tamanio_mat = FILAS * COLUMNAS;
	int temp;

    //Se utilizó bubble sort como método de ordenamiento
	for (int i=0; i<tamanio_mat-1; i++) {
        	for (int j = 0; j < tamanio_mat - i - 1; j++) {
            		int *actual = matriz + j; //El puntero apunta al valor actual
            		int *siguiente = matriz + j + 1; //El apuntero apunta al Valor siguiente

	 	   	//Condición de ordenamiento
            		if (*actual > *siguiente) {
                		//swap de valor de actual y siguiente
						temp = *actual;
                		*actual = *siguiente;
                		*siguiente = temp;
            		}
        	}
    	}
}

void imprimirMatriz(int *matriz) {
	for (int i = 0; i < FILAS; i++) {
        	for (int j = 0; j < COLUMNAS; j++) {
            		printf("%d ", *(matriz + i * COLUMNAS + j));
        	}
        	printf("\n");
    	}
}

int main() {
	int matriz[FILAS][COLUMNAS];
        
	//Llena la matriz con valores al azar entre 0 y 9
	srand(time(0)); //Permite obtener una matriz al azar distinta
        	for(int i=0; i<FILAS; i++){
                        for(int j=0; j<COLUMNAS; j++){
                                matriz[i][j] = rand() % 10;
                        }
                }


	printf("Matriz original:\n");
	imprimirMatriz(&matriz[0][0]);

    ordenarMatriz(&matriz[0][0]);

    printf("\nMatriz ordenada de menor a mayor:\n");
    imprimirMatriz(&matriz[0][0]);

	return 0;
}

