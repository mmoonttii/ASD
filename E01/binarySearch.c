/*
 * iterBinarySearch è uno degli algoritmi di ricerca più efficienti
 * La parte essenziale di questo algoritmo è l'ordinamento dell'array
 *
 * Dato un array ordinato, controllo l'elemento centrale dell'array e lo confronto con l'elemento centrale
 * Se l'elemento centrale è minore(maggiore) del numero cercato, posso non considerare la parte di array a destra
 * (sinistra) e ripetere il procedimento nella restante parte di array
 *
 * La complessità di quest'algoritmo è O(log_2{n}) perchè ogni volta viene dimezzata la parte di array da controllare
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../usefulFunctions.h"
#include "selectionSortIter.h"

int contBI = 0;
int contBR = 0;

int iterBinarySearch(int arr[], int dim, int numRic) {
    int first = 0,
        last = dim - 1,
        middle = 0;

    while (first <= last) {
        middle = (first + last) / 2;
        contBI++;

        if (numRic < arr[middle]) {
            last = middle - 1;
        } else if (numRic == arr[middle]) {
            return middle;
        } else {
            first = middle - 1;
        }
    }
    return -1;
}

int ricBinarySearch(int arr[], int numRic, int first, int last) {
    int middle = 0;

    if (first > last) {
        return -1;
    }

    middle = (first + last) / 2;

    contBR++;
    if (arr[middle] == numRic) {
        return middle;
    } else if (arr[middle] < numRic) {
        return ricBinarySearch(arr, numRic, middle + 1, last);
    } else {
        return ricBinarySearch(arr, numRic, first, middle - 1);
    }
}

int main(){
   	srand(time(NULL));
    clock_t start, end;
	double t;
    int dim = 50,
        *arr = NULL,
        numRic,
        idx;

    arr = generaArray(dim, CASUALE);
    selectionSortIter(arr, dim);

    printArray(arr, dim);

    printf("\nInserisci elemento da cercare: ");
    scanf("%d", &numRic);

    start = clock();
    idx = iterBinarySearch(arr, dim, numRic);
    end = clock();

    t = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nL'elemento è in posizione %d", idx);
    printf("\nIl tempo impiegato è %lf", t);
    printf("\nGli elementi analizzati sono %d", contBI);

    start = clock();
    idx = ricBinarySearch(arr, numRic, 0, dim - 1);
    end = clock();

    t = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nL'elemento è in posizione %d", idx);
    printf("\nIl tempo impiegato è %lf", t);
    printf("\nGli elementi analizzati sono %d", contBR);
    return 0;
}