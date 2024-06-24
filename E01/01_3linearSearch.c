#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../usefulFunctions.h"

int contL = 0;

void selectionSortIter(int arr[], int dim) {
    int min = 0;
    for (int i = 0; i <= dim - 2; ++i) {
        min = i;
        for (int j = i + 1; j <= dim - 1; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(&arr[min], &arr[i]);
    }
}

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

int main(){
    srand(time(NULL));
	clock_t start, end;
	double t;

    int dim = 10,
        *arr = NULL,
        numRic,
        idx;

    arr = generaArray(dim, CASUALE);
    printf("Array non ordinato: ");
    printArray(arr, dim);

    selectionSortIter(arr, dim);
    printf("\nArray ordinato: ");
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

    free(arr);
    return 0;
}