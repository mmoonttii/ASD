#include <string.h>
#include <stdio.h>

#define DIM_NOME 32
#define DIM_ARR 5

typedef struct {
    char nome[DIM_NOME];
    double prezzo_notte;
    int recensione;
} Hotel;

void swap(Hotel *a, Hotel *b) {
    Hotel aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void selectionSort(Hotel arr[], int dim) {
    int min = 0;
    for (int i = 0; i <= dim - 2; ++i) {
        min = i;
        for (int j = i + 1; j <= dim - 1; ++j) {
            if (strcmp(arr[j].nome, arr[min].nome) < 0) {
                min = j;
            }
        }
        swap(&arr[min], &arr[i]);
    }
}

int iterBinarySearch(Hotel arr[], int dim, char hotelRicName[DIM_NOME]) {
    int first = 0,
        last = dim - 1,
        middle = 0;

    while (first <= last) {
        middle = (first + last) / 2;

        if (strcmp(hotelRicName, arr[middle].nome) > 0) {
            last = middle - 1;
        } else if (strcmp(hotelRicName, arr[middle].nome) == 0) {
            return middle;
        } else {
            first = middle - 1;
        }
    }
    return -1;
}

int main(){
    Hotel array[DIM_ARR] = {{"Hotel Setar", 33.45, 5},
                            {"T-Hotel", 67.00, 3},
                            {"Accor Hotel", 55.45, 4},
                            {"Casa mia hotel", 11.78, 5},
                            {"Locanda dei buoni e cattivi", 45.45, 4}};

    char hotelRicName[DIM_NOME];

    int found;

    selectionSort(array, DIM_ARR);

    printf("Inserisci hotel da cercare: ");
    scanf(" %[^\n]31s", hotelRicName);

    found = iterBinarySearch(array, DIM_ARR, hotelRicName);
    if (found == -1) {
        printf("Hotel non trovato");
        return 1;
    }
    printf("Found at pos: %d\n"
           "Name: %s\n"
           "Price: %lf\n"
           "Revs: %d",
           found, array[found].nome, array[found].prezzo_notte, array[found].recensione);
    return 0;
}