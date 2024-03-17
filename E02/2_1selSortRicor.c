#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../usefulFunctions.h"

int findMin(int arr[], int minPos, int start, int dim) {
    if (start == dim) {
        return minPos;
    }
    if (arr[start] < arr[minPos]) {
        minPos = start;
    }
    return findMin(arr, minPos, start + 1, dim);
}

void selectionSortRicor(int arr[], int dim, int start) {
    int minIdx = 0;

    if (start >= dim - 1) {
        return;
    }

    minIdx = findMin(arr, start, start + 1, dim);
    swap(&arr[minIdx], &arr[start]);
    selectionSortRicor(arr, dim, start + 1);
}

int Notmain(){
    srand(time(NULL));
	clock_t start, end;
	double t;
	int dim = 500000,
		*arr = NULL;

    arr = generaArray(dim, ORDINATO);
    printf("\nArr generato\n");

    start = clock();
	selectionSortRicor(arr, dim, 0);
	end = clock();

    t = ((double) (end - start)) / CLOCKS_PER_SEC;

    printArray(arr, dim);
    printf("\ntempo impiegato: %lf sec", t);

    return 0;
}