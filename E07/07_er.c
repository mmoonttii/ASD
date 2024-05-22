/** Pronto Soccorso 
 * Si vuole simulare la gestione di una coda di attesa al pronto soccorso gestendo i pazienti come una coda con priorità
 * La priorità dipende dal codice colore bianco < verde < giallo < rosso
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define DIM_NOME 50
#define DIM_HEAP 50

//stuttura che rappresenta un Pronto soccorso
typedef struct {
    int numeroB;
    int numeroG;
    int numeroV;
    int numeroR;
} ProntoSoccorso;

//enumerazione che rappresenta i codici del pronto soccorso
typedef enum {
    BIANCO,
    VERDE,
    GIALLO,
    ROSSO
} Codice;

typedef enum {
    ERR = -1,
    LEAVE,
    ADD,
    COMPARE,
    REMOVE,
    PRINT
} Menu;

//struttura che rappresenta un Paziente
typedef struct {
    char nome[DIM_NOME];
    Codice codice;
    int ordine;
} Paziente;

/*funzione che chiede i dati relativi ad un nuovo paziente e lo restituisce (con il campo ordine calcolato automaticamente), 
pronto per essere inserito nella coda con priorita' (heap) */
Paziente nuovoPaziente(ProntoSoccorso *ps);
void printPaziente(Paziente paz);
void printHeap(Paziente coda[], int n);
Paziente deleteHeap(Paziente coda[], int *n);
void insertHeap(Paziente coda[], Paziente paziente, int *n);
int priorita(Paziente *p1, Paziente *p2);

int main() {
  //inizializzazione pronto soccorso
    ProntoSoccorso ps;
    ps.numeroB = ps.numeroG = ps.numeroV = ps.numeroR = 0;

    //inizializzazione della Coda con priorita'
    Paziente coda[DIM_HEAP];
    int dim_coda = 0;
    Paziente tempPaziente;
    Menu choice;

    printf("Sistema gestione Pronto Soccorso\n");
    do {
        choice = ERR;
        printf("Menu principale:\n"
               "[1] Aggiungi un nuovo paziente alla coda\n"
               "[2] Confronta le priorità di due pazienti\n"
               "[3] Rimuovi il paziente con priorità massima dalla coda\n"
               "[4] Stampa lo stato della coda\n"
               "[0] Lascia il sistema\n"
               ">>> ");
        scanf("%u", &choice);

        switch (choice) {
        case LEAVE:
            printf("Stai lasciando il sistema");
            sleep(1u);
            printf(".");
            sleep(1u);
            printf(".");
            sleep(1u);
            printf(".");
            break;
        
        case ADD:
            tempPaziente = nuovoPaziente(&ps);
            insertHeap(coda, tempPaziente, &dim_coda);
            break;
        
        case COMPARE:
            printf("=== WIP ===\n");
            break;

        case REMOVE:
            tempPaziente = deleteHeap(coda, &dim_coda);
            printPaziente(tempPaziente);
            break;

        case PRINT:
            printHeap(coda, dim_coda);
            break;

        case ERR:
        default:
            printf("Errore con la scelta, riprova");
            break;
        }
    } while (choice != LEAVE);
    return 0;
}

Paziente nuovoPaziente(ProntoSoccorso *ps) {
    Paziente p;

    printf("\nNome paziente -> ");
    scanf(" %[^\n]s", p.nome);
    getchar();

    do {
        printf("\nCodice paziente (0 = bianco, 1 = verde, 2 = giallo, 3 = rosso)-> ");
        scanf("%u", &(p.codice));
        getchar();

        if(p.codice < BIANCO || p.codice > ROSSO)
            printf("\nCodice non valido");
    } while(p.codice < BIANCO || p.codice > ROSSO);

    if (p.codice == BIANCO) {
        ps->numeroB++;
        p.ordine = ps->numeroB;
    } else if (p.codice == GIALLO) {
        ps->numeroG++;
        p.ordine = ps->numeroG;

    } else if (p.codice == VERDE) {
        ps->numeroV++;
        p.ordine = ps->numeroV;
    } else {
        ps->numeroR++;
        p.ordine = ps->numeroR;
    }

    return p;
}

/**
 * priorità è la funzione che confronta le priorità di due pazienti
 * \return int{1,2}: paziente che ha priorità maggiore
*/
int priorita(Paziente *p1, Paziente *p2) {
    if (p1->codice > p2->codice) {
        return 1;
    } else if (p2->codice > p1->codice) {
        return 2;
    } else {
        if (p1->ordine < p2->ordine) {
            return 1;
        } else if (p1->ordine > p2->ordine) {
            return 2;
        } else {
            return 0;
        }
    }
}

/** algoritmo insertHeap(array heap, elemento item, puntatore a intero n) → void
 * / inserisce un nuovo item in un heap di n elementi
 *  if (n == DIM_HEAP-1) then
 *      stampa "L'heap e' pieno"
 *      return
 *  n ← n + 1
 *  i ← n
 *  while (i ≠ 1 and item ha priorità superiore di heap[i/2]) do
 *      heap[i] ← heap[i/2]
 *      i ← i/2
 * heap[i] ← item 
 */

void insertHeap(Paziente coda[], Paziente paziente, int *n) {
    if (*n == DIM_HEAP-1) {
        printf("L'heap e' pieno");
        return;
    }
    *n++;
    int i = *n;

    while (i != 1 && priorita(&paziente, &coda[i/2]) == 1/*item ha priorità superiore di heap[i/2]*/) { 
        coda[i] = coda[i/2];
        i = i/2;
    }
    coda[i] = paziente; 
}

/** algoritmo deleteHeap(array heap, puntatore a intero n) → elemento
    // cancella e restituisce l’elemento radice in un heap di n elementi
    item ← heap[1]
    temp ← heap[n]
    n ← n-1
    padre ← 1
    figlio ← 2
    while(figlio ≤ n) do
        if (figlio < n and heap[figlio] ha priorita’ inferiore di heap[figlio+1]) then
            figlio ← figlio+1
        if (temp ha priorita’ superiore o uguale di heap[figlio]) then
            break
        heap[padre] ← heap[figlio]
        padre ← figlio
        figlio ← 2 ✕ figlio
    heap[padre] ← temp
    return item
*/
Paziente deleteHeap(Paziente coda[], int *n) {
    // cancella e restituisce l’elemento radice in un heap di n elementi
    Paziente item = coda[1];
    Paziente temp = coda[(*n)];
    *n--;
    int padre = 1;
    int figlio = 2;

    while (figlio <= *n) {
        if (figlio < *n && priorita(&coda[figlio], &coda[figlio+1]) == 2/* heap[figlio] ha priorita’ inferiore di heap[figlio+1] */) {
            figlio++;
        }
        if (priorita(&temp, &coda[figlio]) <= 1/* temp ha priorita’ superiore o uguale di heap[figlio] */) {
            break;
        }

        coda[padre] = coda[figlio];
        padre = figlio;
        figlio = 2 * figlio;
    }

    coda[padre] = temp;
    return item;
}

void printHeap(Paziente coda[], int n) {
    
    printf("Pazienti\n");
    for (int i = 1; i <= n; i++) {
        printf(" %d:", i);
        printPaziente(coda[i]);
    }
    
}

void printPaziente(Paziente paz) {
    char *codici[4] = {
        "Bianco", "Verde", "Giallo", "ROSSO"
    };
    printf("%s Cod.: %6s Ord.: %u\n", paz.nome, codici[paz.codice], paz.ordine);
}