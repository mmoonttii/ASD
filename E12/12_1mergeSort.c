/// mergeSort
#include "../usefulFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 100

void mergeSort(int lista[], int ordinata[], int lower, int upper);
void merge(int lista[], int ordinata[], int i, int m, int n);

int main() {
	srand(time(NULL));
    int *arr = generaArray(N, CASUALE),
        *ordinata;
    ordinata = (int *)calloc(N, sizeof(int));

    printf("Array non ordinato: ");
    printArray(arr, N);

    mergeSort(arr, ordinata, 0, N-1);

    printf("\nArray ordinato: ");
    printArray(arr, N);
    return 0;
}

/** algoritmo mergesort(array lista, array ordinata, int lower, int upper) → void
		if (lower ≥ upper) then return

		medium ← (lower + upper)/2
		mergesort(lista, ordinata, lower, medium)
		mergesort(lista, ordinata, medium+1, upper)
		merge(lista, ordinata, lower, medium, upper)
 */

void mergeSort(int lista[], int ordinata[], int lower, int upper) {
	int medium;
	if (lower >= upper) return;

	medium = (lower + upper) / 2;
	mergeSort(lista, ordinata, lower, medium);
	mergeSort(lista, ordinata, medium + 1, upper);
	merge(lista, ordinata, lower, medium, upper);
}

/**algoritmo merge(array lista, array ordinata, int i, m e n) → void
	j← m+1 // indice per la seconda parte di lista
	k ← i // indice per la lista ordinata
	pos_iniziale← i //posizione iniziale nella lista
	while (i ≤ m and j ≤ n) do
		if (lista[i] ≤ lista[j]) then
			ordinata[k] ← lista[i]
			incrementa i e k
		else
			ordinata[k] ← lista[j]
			incrementa j e k
	if (i > m) then
		// ordinata[k],..., ordinata[n] ← lista[j],..., lista[n]
		for (t ← j; t ≤ n; t++)
		ordinata[k + t - j] = lista[t];
	else
		// ordinata[k],..., ordinata[n] ← lista[i],..., lista[m]
		for (t ← i; t ≤ m; t++)
		ordinata[k + t - i] = lista[t];
	copia ordinata[pos_iniziale : n] in lista[pos_iniziale : n]
 */

void merge(int lista[], int ordinata[], int i, int m, int n) {
	int j = m + 1;
	int k = i;
	int pos_iniziale = i;

	while (i <= m && j <= n) {
		if (lista[i] <= lista[j]) {
			ordinata[k] = lista[i];
			i++;
			k++;
		} else {
			ordinata[k] = lista[j];
			j++;
			k++;
		}
	}

	if (i > m) {
		// ordinata[k],..., ordinata[n] ← lista[j],..., lista[n]
		for (int t = j; t <= n; t++) {
			ordinata[k + t - j] = lista[t];
		}
	} else {
		// ordinata[k],..., ordinata[n] ← lista[i],..., lista[m]
		for (int t = i; t <= m; t++) {
			ordinata[k + t - i] = lista[t];
		}
	}

	for (int t = pos_iniziale; t <= n; t++) {
		lista[t] = ordinata[t];
	}
}
