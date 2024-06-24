#include "../usefulFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100
/*
algoritmo insertionSort(array lista, int dim) → void
for i ← 1 to dim-1 do
prossimo ← lista[i]
for j← i-1 downto 0 do
if (prossimo < lista[j]) then
lista[j+1]← lista[j]
else
break
lista[j+1] ← prossimo
*/

void insertionSort(int lista[], int dim) {
	int prossimo;
	int j;

	for (int i = 1; i < dim; i++) {
		prossimo = lista[i];
		for (j = i - 1; j >= 0; j--) {
			if (prossimo < lista[j]) {
				lista[j + 1] = lista[j];
			} else {
				break;
			}
		}
		lista[j + 1] = prossimo;
	}
}

/*
Popolare un array di N elementi generati casualmente (riciclare la funzione
genera_array(…) dell’Esercitazione 1);
• Creare una funzione stampa_array(…) che prende in input l’array e lo stampa.
Utilizzare questa funzione per stampare l’array prima e dopo l’ordinamento
(anche questa può essere riciclata dall’Esercitazione 1).
*/

int main(){
	srand(time(NULL));
    int *arr = generaArray(N, CASUALE);

    puts("\nArray non ordinato:");
    printArray(arr, N);

    insertionSort(arr, N);

    puts("\nArray ordinato:");
    printArray(arr, N);
	free(arr);
    return 0;
}
