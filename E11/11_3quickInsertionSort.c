/*
Implementare una versione modificata dell’algoritmo di ordinamento
quicksort ricorsivo che ad ogni passo verifica la dimensione delle liste
parziali:
• Se la lista parziale ha dimensione superiore a M si continua con un
passo del quicksort.
• Se la lista parziale ha dimensione inferiore o uguale a M si continua
l’ordinamento con l’insertionsort (ovviamente applicato solo alla
lista parziale esaminata e NON su tutto l’array).
• M è fornito in input dall’utente.
• Popolare un array di N elementi generati casualmente;
• Apportare le opportune modifiche al quicksort e all’insertionsort
(crearne una copia per non modificare le versioni originali);
• Stampare l’
array prima e dopo l’ordinamento.
*/
#include "../usefulFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20

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

int perno(int arr[], int primo, int ultimo) {
    int i = primo;
    int j = ultimo + 1;
    int pivot = arr[primo];

    while (i < j) {
        do {
            i++;
        } while (i <= ultimo && arr[i] <= pivot);

        do {
            j--;
        } while (j >= primo && arr[j] > pivot);

        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[primo], &arr[j]);
    return j;
}

void quickInsertionSort(int arr[], int u, int v, int m){
    if (v - u <= m) {
        insertionSort(arr, v+1);
        return;z
    }
    int q = perno(arr, u, v);
    if (u < q) quickInsertionSort(arr, u, q - 1, m);
    if (q < v) quickInsertionSort(arr, q + 1, v, m);

}

int main() {
	srand(time(NULL));
    int *arr = generaArray(N, CASUALE),
        m;

    printf("Inserire valore per m: ");
    scanf("%d", &m);

    printf("Array prima dell'ordinamento:\n");
    printArray(arr, N);

    quickInsertionSort(arr, 0, N - 1, m);

    printf("Array dopo l'ordinamento:\n");
    printArray(arr, N);
    return 0;
}
