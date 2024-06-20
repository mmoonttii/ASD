/**
 * Tavole hash:
 *  U : insieme universo delle chiavi
 *  T : tavola hash
 *  m : dimensione della tabella
 *  n : numero elementi memorizzati in T
 *  k : generica chiavi
 *  h(k) : posizione della chiave k nella tabella T, tramite la funzione k
 *  T[h(k)] : elemento della tabella T di chiave k
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TARGA 10
#define NUM_PIANI 7

typedef struct
{
    char targa[MAX_TARGA];
    int ora;
    int min;
} Auto;

typedef struct nodo
{
    Auto info;
    struct nodo *link;
} Nodo;

int hash_function(char targa[]);
Auto acquisisci_auto();
void inserisci_auto(Nodo* parcheggio[], Auto a);
void carica_auto_test(Nodo* parcheggio[]);
void stampa_parcheggio(Nodo* parcheggio[]);
void stampa_piano(Nodo* parcheggio[], int piano);
Nodo* ricerca_auto(Nodo* parcheggio[], char targa[]);
void elimina_auto(Nodo* parcheggio[], char targa[]);

int main() {
    Nodo *parcheggio[NUM_PIANI],
         *found = NULL;

    int choice;
    char targa[MAX_TARGA];

    for(int i = 0; i < NUM_PIANI; i++)
        parcheggio[i] = NULL;

    carica_auto_test(parcheggio);

    while (1) {
        puts("PDS Parking\n"
             "[1] Aggiungi auto\n"
             "[2] Stampa piano\n"
             "[3] Stampa parcheggio\n"
             "[4] Cerca auto\n"
             "[5] Elimina auto\n"
             "[0] Lascia parcheggio\n"
             ">>> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inserisci_auto(parcheggio, acquisisci_auto());
                break;

            case 2:
                puts("Inserisci piano da stampare: ");
                scanf("%d", &choice);
                if (choice >= NUM_PIANI) {
                    puts("Piano non valido, riprovare\n");
                    break;
                }
                stampa_piano(parcheggio, choice);
                break;

            case 3:
                stampa_parcheggio(parcheggio);
                break;

            case 4:
                puts("Inserisci targa da ricercare: ");
                scanf("%6s", targa);
                found = ricerca_auto(parcheggio, targa);

                if (found == NULL) {
                    puts("Auto non trovata");
                    break;
                }

                puts("Ecco l'auto\n");
                printf("> %6s Piano %d - %2d:%2d\n", found->info.targa, hash_function(found->info.targa), found->info.ora, found->info.min);
                break;

            case 5:
                printf("Targa dell'auto da eliminare:");
                scanf("%6s", targa);
                elimina_auto(parcheggio, targa);
                break;

            case 0:
                exit(EXIT_SUCCESS);

            default:
                puts("Input non valido");
                break;
            }
    }
    return 0;
}

void carica_auto_test(Nodo* parcheggio[]) {
    Auto a0 = {"PI555TA", 12, 15};
    Auto a1 = {"CA220TO", 7, 59};
    Auto a2 = {"EG000AL", 19, 45};
    Auto a3 = {"GO000LE", 15, 20};
    Auto a4 = {"BA220TO", 10, 35};
    Auto a5 = {"AP111LE", 15, 20};
    Auto a6 = {"MI123FT", 18, 40};
    Auto a7 = {"NO985LE", 20, 30};
    Auto a8 = {"GI124CH", 11, 20};
    Auto a9 = {"LO199RE", 9, 30};
    Auto a10 = {"ZA156KF", 7, 10};

    inserisci_auto(parcheggio, a0);
    inserisci_auto(parcheggio, a1);
    inserisci_auto(parcheggio, a2);
    inserisci_auto(parcheggio, a3);
    inserisci_auto(parcheggio, a4);
    inserisci_auto(parcheggio, a5);
    inserisci_auto(parcheggio, a6);
    inserisci_auto(parcheggio, a7);
    inserisci_auto(parcheggio, a8);
    inserisci_auto(parcheggio, a9);
    inserisci_auto(parcheggio, a10);
}

int hash_function(char targa[]) {
    int hash = 0;
    for (int i = 0; i < MAX_TARGA && targa[i] != '\0'; i++)
    {
        hash += targa[i];
    }
    hash %= NUM_PIANI;
    return hash;
}

Auto acquisisci_auto() {
    Auto car;
    puts("Inserisci targa: ");
    scanf("%10s", car.targa);
    puts("Inserisci ora di arrivo: ");
    scanf("%d", &car.ora);
    puts("Inserisci minuti di arrivo: ");
    scanf("%d", &car.min);

    return car;
}

void inserisci_auto(Nodo* parcheggio[], Auto a) {
    int hash = hash_function(a.targa);
    Nodo *aux = NULL,
         *node = NULL;
    node = (Nodo *)malloc(sizeof(Nodo));
    node->info = a;
    node->link = NULL;

    if (parcheggio[hash] == NULL) {
        parcheggio[hash] = node;
    } else {
        for (aux = parcheggio[hash]; aux->link != NULL; aux = aux->link);
        aux->link = node;
    }
}

void stampa_parcheggio(Nodo* parcheggio[]) {
    for (int i = 0; i < NUM_PIANI; i++) {
        stampa_piano(parcheggio, i);
    }
}

void stampa_piano(Nodo* parcheggio[], int floor) {
    Nodo *aux = NULL;
    printf("Piano %d:\n", floor);
    for (aux = parcheggio[floor]; aux != NULL; aux = aux->link) {
        printf("\t%6s -> %2d:%2d\n", aux->info.targa, aux->info.ora, aux->info.min);
    }
}

Nodo* ricerca_auto(Nodo* parcheggio[], char targa[]) {
    int hash = hash_function(targa);
    Nodo* aux = NULL;
    aux = parcheggio[hash];

    for (; aux != NULL && strcmp(aux->info.targa, targa) != 0; aux = aux->link);
    return aux;
}

void elimina_auto(Nodo* parcheggio[], char targa[]) {
    int hash = hash_function(targa);
    Nodo *aux = parcheggio[hash],
         *prev = NULL;

    for (; aux != NULL && strcmp(aux->info.targa, targa) != 0; aux = aux->link){
        prev = aux;
    }

    prev->link = aux->link;

    free(aux);
}
