#include <stdlib.h>
#include <stdio.h>
#include "usefulFunctions.h"


int *generaArray(int dim, inputType tipoSchema) {
    int *arr = NULL;
    arr = (int *) calloc(dim, sizeof(int));
    switch (tipoSchema) {
        case ORDINATO:
            arrayORDINATO(arr, dim);
            break;
        case QUASI_ORDINATO:
            arrayQUASI_ORDINATO (arr, dim);
            break;
        case INV_ORDINATO:
            arrayINV_ORDINATO(arr, dim);
            break;
        case CASUALE:
            arrayCASUALE(arr, dim);
            break;
    }
    return arr;
}

void arrayORDINATO(int arr[], int dim) {
    for (int i = 0; i < dim; ++i) {
        arr[i] = i;
    }
}

void arrayQUASI_ORDINATO (int arr[], int dim) {
    int i = 0;
    for (i = 0; i < dim / 2; ++i) {
        arr[i] = i;
    }
    for (; i < dim; ++i) {
        arr[i] = rand();
    }
}

void arrayINV_ORDINATO (int arr[], int dim) {
    for (int i = 0; i < dim; ++i) {
        arr[i] = dim - i;
    }
}

void arrayCASUALE (int arr[], int dim) {
    for (int i = 0; i < dim; ++i) {
        arr[i] = rand();
    }
}

/*
 * swap scambia tra di loro i valori contenuti in due puntatori interi
 */
void swap(int *a, int *b) {
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void printArray(int arr[], int dim) {
    for (int i = 0; i < dim; ++i) {
        printf("%d ", arr[i]);
    }
}