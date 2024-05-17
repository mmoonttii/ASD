#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "../usefulFunctions.h"
#include "../E01/1_1selectionSortIter.h"

#define N_DIMS 7
#define N_ALGS 5
#define N_SCMS 4


int main(){
    int arrayDims[N_DIMS] = {500,
                             1000,
                             2000,
                             5000,
                             10000,
                             20000,
                             50000};

    int *arrs[N_ALGS] = {NULL};

    unsigned long long swaps[N_ALGS] = {},
                       cmprs[N_ALGS] = {};

    clock_t starts[N_ALGS], ends[N_ALGS];
    long double times[N_ALGS];

    // *algs[N_ALGS] = {selectionSort(), insertionSort(), };

    char *schemeNames[N_SCMS] = {"ordinato",
                                 "quasi ordinato",
                                 "inversamente ordinato",
                                 "casuale"};

    char *algsNames[N_ALGS] = {"selectionSort",
                               "insertionSort",
                               "mergeSort",
                               "heapSort",
                               "quickSort"};



    // Ciclo sugli schemi di array
    for (int scheme = 0; scheme < N_SCMS; ++scheme) {
        // Ciclo sulle dimensioni degli array
        for (int dim = 0; dim < N_DIMS; ++dim) {

            // Ciclo sugli algoritmi da applicare, per inizializzare gli array da ordinare

            // Genero un array di dimensione dim e schema scheme
            arrs[0] = generaArray(arrayDims[dim], scheme);
            for (int i = 1; i < N_ALGS; ++i) {
                // Alloco per ogni algoritmo lo spazio necessario per l'array e vi copio l'array generato
                arrs[i] = (int *)calloc(arrayDims[dim], sizeof(int));
                memcpy(arrs[i], arrs[0], arrayDims[dim]* sizeof(int));
            }

            for (int i = 0; i < N_ALGS; ++i) {
                swaps[i] = 0;
                cmprs[i] = 0;

                starts[i] = clock();
                // algs[i](arrs[i]);
                ends[i] = clock();

                times[i] = ((long double)(ends[i] - starts[i])) / CLOCKS_PER_SEC;
            }

            printf("Array %s Dim: %d\n", schemeNames[scheme], arrayDims[dim]);
            printf("%13s | Tempo | Confronti | Scambi\n", "Algoritmi");
            for (int i = 0; i < N_ALGS; ++i) {
                printf("%13s | %LF | %llu | %llu", algsNames[i], times[i], cmprs[i], swaps[i]);
            }

            for (int i = 0; i < N_ALGS; ++i) {
                free(arrs[i]);
            }
        }
    }
    return 0;
}
