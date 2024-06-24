#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "usefulFunctions.h"

#define N_DIMS 7
#define N_ALGOS 5
#define N_SCHEMS 4

unsigned long long swaps = 0;
unsigned long long cmprs = 0;

int acquireChoice(int lower, int upper);
void manual(int arrayDims[N_DIMS], char *schemeNames[], char *algsNames[]);
void automatic(int arrayDims[N_DIMS], char *schemeNames[], char *algsNames[]);

void selectionSort(int arr[], int dim);
void insertionSort(int arr[], int dim);

void mergeSort(int lista[], int dim);
void mergeSortAlg(int lista[], int ordinata[], int lower, int upper);
void merge(int lista[], int ordinata[], int i, int m, int n);

void heapSort(int arr[], int dim);
void adatta(int lista[], int radice, int n);

void quickSort(int arr[], int dim);
int perno(int arr[], int primo, int ultimo);
void quickSortAlg(int arr[], int u, int v);

int main() {
	int arrayDims[N_DIMS] = {500,
                             1000,
                             2000,
                             5000,
                             10000,
                             20000,
                             50000};

	char *schemeNames[N_SCHEMS] = {"ordinato",
                                 "quasi ordinato",
                                 "inversamente ordinato",
                                 "casuale"};

    char *algsNames[N_ALGOS] = {"sel",
                               "ins",
                               "mrg",
                               "hp",
                               "qck"};

	int choice = -1;

	while (1) {
		printf("REPORT ASD\n");
		printf("[1] Manuale\n");
		printf("[2] Automatico\n");
		printf("[0] Esci\n");
		choice = acquireChoice(0, 2);

		switch (choice) {
			case 1:
				manual(arrayDims, schemeNames, algsNames);
				break;
			case 2:
				automatic(arrayDims, schemeNames, algsNames);
				break;
			case 0:
				return 0;
			default:
				printf("Scelta non valida\n");
		}

	}
	return 0;
}

int acquireChoice(int lower, int upper) {
	int choice;
	do {
		printf(">>> ");
		scanf("%d", &choice);
		if (choice < lower || choice > upper) {
			printf("Scelta non valida\n");
		}
	} while (choice < lower || choice > upper);
	return choice;
}

void manual(int arrayDims[N_DIMS], char *schemeNames[], char *algsNames[]) {
	int dim, scheme, algo;
	int *arr = NULL;

	printf("Manuale\n");
	printf("Scegliere dimensione array: \n");
	for (int i = 0; i < N_DIMS; ++i) {
		printf("[%d] %d\n", i, arrayDims[i]);
	}
	dim = acquireChoice(0, N_DIMS - 1);

	printf("Scegliere schema array: \n");
	for (int i = 0; i < N_SCHEMS; ++i) {
		printf("[%d] %s\n", i, schemeNames[i]);
	}
	scheme = acquireChoice(0, N_SCHEMS - 1);

	printf("Scegliere algoritmo: \n");
	for (int i = 0; i < N_ALGOS; ++i) {
		printf("[%d] %s\n", i, algsNames[i]);
	}
	algo = acquireChoice(0, N_ALGOS - 1);

	arr = generaArray(arrayDims[dim], scheme);
	swaps = 0; cmprs = 0;
	clock_t start = clock();

	switch (algo) {
		case 0:
			selectionSort(arr, arrayDims[dim]);
			break;
		case 1:
			insertionSort(arr, arrayDims[dim]);
			break;
		case 2:
			mergeSort(arr, arrayDims[dim]);
			break;
		case 3:
			heapSort(arr, arrayDims[dim]);
			break;
		case 4:
			quickSort(arr, arrayDims[dim]);
			break;
	}
	clock_t end = clock();
	long double time = ((long double)(end - start)) / CLOCKS_PER_SEC;

	printf("Array %s Dim: %d\n", schemeNames[scheme], arrayDims[dim]);
	printf("Algoritmo: %s\n", algsNames[algo]);
	printf("Tempo: %Lf\n", time);
	printf("Confronti: %llu\n", cmprs);
	printf("Scambi: %llu\n", swaps);
	if (dim <= 2) {
		printf("Array ordinato: ");
		printArray(arr, arrayDims[dim]);
	}
	free(arr);
}

void automatic(int arrayDims[N_DIMS], char *schemeNames[], char *algsNames[]){
	int *arr = NULL;
	clock_t start, end;
	printf("ASD REPORT - Automatic\n");
	printf("Compares - Swaps - Time\n");
	for (int j = 0; j < N_SCHEMS; ++j) {
		for (int k = 0; k < N_DIMS; ++k) {
			printf("Array %s Dim: %d\n", schemeNames[j], arrayDims[k]);
			for (int i = 0; i < N_ALGOS; ++i) {
				arr = generaArray(arrayDims[k], j);
				swaps = 0; cmprs = 0;
				start = clock();
				switch (i) {
					case 0:
						selectionSort(arr, arrayDims[k]);
						break;
					case 1:
						insertionSort(arr, arrayDims[k]);
						break;
					case 2:
						mergeSort(arr, arrayDims[k]);
						break;
					case 3:
						heapSort(arr, arrayDims[k]);
						break;
					case 4:
						quickSort(arr, arrayDims[k]);
						break;
				}
				end = clock();
				long double time = ((long double)(end - start)) / CLOCKS_PER_SEC;

				printf("%s:\t", algsNames[i]);
				printf("%llu\t%llu\t%Lf\n", cmprs, swaps, time);

				free(arr);
			}
			//getchar();
			//getchar();
		}
	}
}

void selectionSort(int arr[], int dim){
	int min = 0;
	for (int i = 0; i <= dim - 2; ++i) {
		min = i;
		for (int j = i + 1; j <= dim - 1; ++j) {
			if (arr[j] < arr[min]) {
				min = j;
			}
			cmprs++;
		}
		swap(&arr[min], &arr[i]);
		swaps++;
	}
}

void insertionSort(int arr[], int dim) {
	int prossimo;
	int j;

	for (int i = 1; i < dim; i++) {
		prossimo = arr[i];
		for (j = i - 1; j >= 0; j--) {
			if (prossimo < arr[j]) {
				arr[j + 1] = arr[j];
				swaps++;
				cmprs++;
			} else {
				cmprs++;
				break;
			}
		}
		arr[j + 1] = prossimo;
		swaps++;
	}
}

void mergeSort(int lista[], int dim) {
	int *ordinata = (int *)malloc(dim * sizeof(int));
	mergeSortAlg(lista, ordinata, 0, dim - 1);
	free(ordinata);
}

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
		cmprs++;
		swaps++;
	}

	if (i > m) {
		// ordinata[k],..., ordinata[n] ← lista[j],..., lista[n]
		for (int t = j; t <= n; t++) {
			ordinata[k + t - j] = lista[t];
			swaps++;
		}
	} else {
		// ordinata[k],..., ordinata[n] ← lista[i],..., lista[m]
		for (int t = i; t <= m; t++) {
			ordinata[k + t - i] = lista[t];
			swaps++;
		}
	}

	for (int t = pos_iniziale; t <= n; t++) {
		lista[t] = ordinata[t];
	}
}

void mergeSortAlg(int lista[], int ordinata[], int lower, int upper) {
	int medium;
	if (lower >= upper) return;

	medium = (lower + upper) / 2;
	mergeSortAlg(lista, ordinata, lower, medium);
	mergeSortAlg(lista, ordinata, medium + 1, upper);
	merge(lista, ordinata, lower, medium, upper);
}

void heapSort(int arr[], int dim) {
	arr[0] = 0;
	for (int i = dim / 2; i >= 1; i--) {
		adatta(arr, i, dim);
	}

	for (int i = dim - 1; i >= 1; i--) {
		swap(&arr[1], &arr[i + 1]);
		swaps++;
		adatta(arr, 1, i);
	}
}

void adatta(int lista[], int radice, int n) {
	int temp = lista[radice];
	int figlio = 2 * radice;

	while (figlio <= n) {
		if (figlio < n && lista[figlio] < lista[figlio + 1]) {
			figlio++;
		}
		cmprs++;

		if (temp > lista[figlio]) {
			cmprs++;
			break;
		} else {
			lista[figlio / 2] = lista[figlio];
			swaps++;
			cmprs++;
			figlio *= 2;
		}
	}
	lista[figlio / 2] = temp;
	swaps++;
}


void quickSort(int arr[], int dim) {
	quickSortAlg(arr, 0, dim - 1);
}

int perno(int arr[], int primo, int ultimo) {
	int i = primo;
	int j = ultimo + 1;
	int pivot = arr[primo];

	while (i < j) {
		do {
			i++;
			cmprs++;
		} while (i <= ultimo && arr[i] <= pivot);

		do {
			j--;
			cmprs++;
		} while (j >= primo && arr[j] > pivot);

		if (i < j) {
			swap(&arr[i], &arr[j]);
			swaps++;
		}
	}
	swap(&arr[primo], &arr[j]);
	swaps++;
	return j;
}

void quickSortAlg(int arr[], int u, int v) {
	if (u == v) return;
	int q = perno(arr, u, v);
	if (u < q) quickSortAlg(arr, u, q - 1);
	if (q < v) quickSortAlg(arr, q + 1, v);
}
