#ifndef ASD_USEFULFUNCTIONS_H
#define ASD_USEFULFUNCTIONS_H

typedef enum{ORDINATO,
             QUASI_ORDINATO, // Ordinato da 1 a n/2
             INV_ORDINATO,   // Ordinato da n a 1
             CASUALE
} inputType;

int *generaArray(int dim, inputType tipoSchema);

// Generazione tipologie di array
void arrayORDINATO(int arr[], int dim);

void arrayQUASI_ORDINATO (int arr[], int dim);

void arrayINV_ORDINATO (int arr[], int dim);

void arrayCASUALE (int arr[], int dim);

// Swap
void swap(int *a, int *b);

// Stampa array
void printArray(int arr[], int dim);

int findMin(int arr[], int minPos, int start, int dim);

#endif //ASD_USEFULFUNCTIONS_H
