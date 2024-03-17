#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../usefulFunctions.h"
#include "selectionSortIter.h"

int contL = 0;

int linearSearch(int arr[], int dim, int numRic) {
    int pos = 0;
    while ((pos < dim) && (arr[pos] <= numRic)) {
        if (numRic == arr[pos]) {
            contL++;
            return pos;
        } else {
            contL++;
            pos++;
        }
    }
    return -1;
}

int Notmain(){
    srand(time(NULL));
	clock_t start, end;
	double t;

    int dim = 10,
        *arr = NULL,
        numRic,
        idx;

    arr = generaArray(dim, CASUALE);
    selectionSortIter(arr, dim);

    printArray(arr, dim);

    printf("\nInserisci elemento da cercare: ");
    scanf("%d", &numRic);

    start = clock();
    idx = linearSearch(arr, dim, numRic);
    end = clock();

    t = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("L'elemento è in posizione %d", idx);
    printf("\nIl tempo impiegato è %lf", t);
    printf("\nGli elementi analizzati sono %d", contL);
    return 0;
}