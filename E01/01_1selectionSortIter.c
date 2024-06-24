#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../usefulFunctions.h"

/** selectionSortIter\n
 *  - Problema dell'ordinamento: data una sequenza di valori, disporre in ordine, secondo un opportuno criterio, una
 *  sequenza di elementi:\n
 *  \t 1. Si cerca il minimo nella sequenza iniziale;\n
 *  \t 2. Si scambia il minimo con la prima posizione "ordinata";\n
 *  \t 3. Si ripetono i passi 1 e 2, escludendo la posizione appena sistemata dell'array, fino all'esaurimento di tutti
 *          gli elementi presenti.\n
 *\n
 *  Ha senso che l'algoritmo si fermi un passo prima di controllare anche l'ultimo elemento\n
 *
 *  Il selctionSort ha complessità n^2\n
 *
 *  algoritmo selectionSortIter(array A, int n)\n
    for i ← 0 to n-2 do\n
        min ← i\n
        for j ← i+1 to n-1 do\n
            if (A[j] < A[min]) then min ← j\n
        scambia A[min] con A[i]
*/

unsigned long long selectionSort_swap = 0, selectionSort_cmp = 0;

void selectionSortIter(int *arr, int dim) {
	int min = 0;
	for (int i = 0; i <= dim - 2; ++i) {
		min = i;
		for (int j = i + 1; j <= dim - 1; ++j) {
			if (arr[j] < arr[min]) {
				selectionSort_cmp++;
				min = j;
			}
		}
		swap(&arr[min], &arr[i]);
		selectionSort_swap++;
	}
}

int main(){
	srand(time(NULL));
	clock_t start, end;
	double t;
	int dim = 500000,
		*arr = NULL;


	arr = generaArray(dim, ORDINATO);
	printf("\nArray non ordinato: ");
	printArray(arr, dim);

	start = clock();
    selectionSortIter(arr, dim);
	end = clock();

	t = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("\nArray ordinato: ");Ω
	printArray(arr, dim);
    printf("\ntempo impiegato: %lf sec", t);

	free(arr);
	return 0;
}