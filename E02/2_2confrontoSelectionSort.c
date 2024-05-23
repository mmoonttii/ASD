#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../usefulFunctions.h"

unsigned long long cmprsIter = 0, swapsIter = 0;
unsigned long long cmprsRic = 0, swapsRic = 0;

void selectionSortIter(int arr[], int dim) {
    int min = 0;
    for (int i = 0; i <= dim - 2; ++i) {
        min = i;
        for (int j = i + 1; j <= dim - 1; ++j) {
            if (arr[j] < arr[min]) {
                cmprsIter++;
                min = j;
            }
        }
        swap(&arr[min], &arr[i]);
        swapsIter++;
    }
}

void selectionSortRicor(int arr[], int dim, int start) {
    int minIdx = 0;

    if (start >= dim - 1) {
        return;
    }

    minIdx = findMin(arr, start, start + 1, dim);
    swap(&arr[minIdx], &arr[start]);
    swapsRic++;
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
            swapsIter = 0, cmprsIter = 0;
            swapsRic = 0, cmprsRic = 0;

            arr1 = generaArray(arrDim[j], i);
            arr2 = calloc(arrDim[j], sizeof(int));
            memcpy(arr2, arr1, arrDim[j] * sizeof(int));

            start1 = clock();
            selectionSortIter(arr1, arrDim[j]);
            end1 = clock();

            t1 = ((long double) (end1 - start1)) / CLOCKS_PER_SEC;

            printf("\nI: %d Dim: %d\n"
                   "T: %LF Confr: %llu Scambi: %llu\n",
                   i, arrDim[j], t1, cmprsIter, swapsIter);


            start2 = clock();
            selectionSortRicor(arr2, arrDim[j], 0);
            end2 = clock();

            t2 = ((long double) (end2 - start2)) / CLOCKS_PER_SEC;

            printf("\nR: %d Dim: %d\n"
                   "T: %LF Confr: %llu Scambi: %llu\n",
                   i, arrDim[j], t2, cmprsRic, swapsRic);

            free(arr1), free(arr2);

        }
    }

}