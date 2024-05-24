#include <stdio.h>

#define DIM_NOME 32
#define DIM_ARR 5

typedef struct{
    char nome[DIM_NOME];
    double tempo;
    int difficolta;
} Ricetta;

int compare(Ricetta r1, Ricetta r2) {
    if (r1.tempo < r2.tempo) {
        return 0;
    } else if ((r1.tempo == r2.tempo) && (r1.difficolta < r2.difficolta)) {
        return 0;
    } else {
        return 1;
    }
}

void swapRicette(Ricetta *r1, Ricetta *r2) {
    Ricetta aux;
    aux = *r1;
    *r1 = *r2;
    *r2 = aux;
}

void selectionSortRicette(Ricetta arr[], int dim) {
    int min = 0;
    for (int i = 0; i <= dim - 2; ++i) {
        min = i;
        for (int j = i + 1; j <= dim - 1; ++j) {
            if (compare(arr[j], arr[min])) {
                min = j;
            }
        }
        swapRicette(&arr[min], &arr[i]);
    }
}

void acquisisciRicette(Ricetta arr[], int dim) {
    for (int i = 0; i < dim; ++i) {
        printf("\nRicetta %d: ", i);
        printf("\nNome: ");
        scanf(" %[^\n]31s", arr[i].nome);
        printf("\nTempo: ");
        scanf(" %lf", &arr[i].tempo);
        printf("\nDifficoltà: ");
        scanf(" %d", &arr[i].difficolta);
    }
}

void printRicette(Ricetta arr[], int dim) {
    for (int i = 0; i < dim; ++i) {
        printf("\nRicetta %d: ", i);
        printf("\nNome: %s", arr[i].nome);
        printf("\nTempo: %lf", arr[i].tempo);
        printf("\nDifficoltà: %d", arr[i].difficolta);
        printf("\n");
    }
}

int main(){
    Ricetta arr[DIM_ARR];
    acquisisciRicette(arr, DIM_ARR);
    selectionSortRicette(arr, DIM_ARR);
    printRicette(arr, DIM_ARR);
    return 0;
}