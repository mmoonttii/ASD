#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../usefulFunctions.h"

unsigned long long confronti_iter = 0, scambi_iter = 0;
unsigned long long confronti_ric = 0, scambi_ric = 0;

void selectionSortIter(int arr[], int dim) {
    int min = 0;
    for (int i = 0; i <= dim - 2; ++i) {
        min = i;
        for (int j = i + 1; j <= dim - 1; ++j) {
            if (arr[j] < arr[min]) {
                confronti_iter++;
                min = j;
            }
        }
        swap(&arr[min], &arr[i]);
        scambi_iter++;
    }
}

int findMin(int arr[], int minPos, int start, int dim) {
    if (start == dim) {
        return minPos;
    }
    if (arr[start] < arr[minPos]) {
        confronti_ric++;
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
    scambi_ric++;
    selectionSortRicor(arr, dim, start + 1);
}

int main() {
    int arrDim[] = {100,
                    1000,
                    10000,
                    100000,
                    200000,
                    500000};

    int *arr1, * arr2;
    clock_t start1, end1,
            start2, end2;
    long double t1, t2;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            scambi_iter = 0, confronti_iter = 0;
            scambi_ric = 0, confronti_ric = 0;

            arr1 = generaArray(arrDim[j], i);
            arr2 = generaArray(arrDim[j], i);

            start1 = clock();
            selectionSortIter(arr1, arrDim[j]);
            end1 = clock();

            t1 = ((long double) (end1 - start1)) / CLOCKS_PER_SEC;

            printf("\nSelection Sort iterativo\n"
                   "Tipo Array: %d\t Dimensione Array: %d\n"
                   "--> Tempo impiegato: %LF\n"
                   "--> Confronti effettuati: %llu\n"
                   "--> Scambi effettuati: %llu\n",
                   i, arrDim[j], t1, confronti_iter, scambi_iter);


            start2 = clock();
            selectionSortRicor(arr2, arrDim[j], 0);
            end2 = clock();

            t2 = ((long double) (end2 - start2)) / CLOCKS_PER_SEC;

            printf("\nSelection Sort ricorsivo\n"
                   "Tipo Array: %d\t Dimensione Array: %d\n"
                   "--> Tempo impiegato: %LF\n"
                   "--> Confronti effettuati: %llu\n"
                   "--> Scambi effettuati: %llu\n",
                   i, arrDim[j], t2, confronti_ric, scambi_ric);

        }
    }
}