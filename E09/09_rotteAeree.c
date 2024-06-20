/**
 * Un grafo G è una struttura dati astratta non lineare composta da:
 * 	un insieme finito e non vuoto di nodi: N(G)
 * 	un insieme finito (anche vuoto) di archi/lati: L(G)
 *
 * 	I grafi possono essere non orientati o orientati (dove è rilevante il verso in cui si può percorrere il lato)
 *
 * 	Due vertici di un grafo si dicono adiacenti se esiste un lato che li unisce, nei grafi orientati la vicinanza dipende dal verso degli archi.
 * 	In un grafo orientato si dicono incidenti due nodi collegati da un lato
*/
/**
 * Per rappresentare gli archi di un grafo si possono rappresentare tramite liste di adiacenza
 */

// Mediante un grafo orientato vogliamo rappresentare le rotte di una compagnia aerea
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VERTICI 20
#define DIM 50
#define NUM_NODI_TEST 11

typedef struct node
{
    int vertex_id;
    struct node* link;
} Node;

typedef struct
{
    char nome[DIM];
    int  abitanti;
    char nazione[DIM];
    Node* lista_adj;
}Citta;

typedef struct
{
    Node* front;
    Node* back;
    int cont;
}Queue;

/* ==============================
 * Funzioni gia' implementate
 * ============================== */
void carica_citta_test(Citta grafo[]);
void carica_grafo_test_orientato(Citta grafo[], int num_nodi);
void carica_grafo_test_non_orientato(Citta grafo[], int num_nodi);


/* ==============================
 * Funzioni da completare
 * ============================== */
void aggiungi_nodo(Citta grafo[], int *num_nodi);
void crea_arco(Citta grafo[], int idx_coda, int idx_testa, int num_nodi);
void stampa_lista_adiacenze(Citta grafo[], int num_nodi);

void DFS(Citta grafo[], int visited[], int start_id);
void BFS(Citta grafo[], int visited[], int start_id);

void cancella_arco_orientato(Citta grafo[], int id_coda, int id_testa, int num_nodi);
void cancella_arco_non_orientato(Citta grafo[], int id_coda, int id_testa, int num_nodi);

void componenti_connesse(Citta grafo[], int visited[], int num_nodi);

//funzioni studente
int scegli_citta(Citta grafo[], int num_nodi);
void visita_nodo(Citta grafo[], int id);
void reset_visitati(int visited[]);
void pushQueue(Queue *coda, int id);
bool isEmptyQueue(Queue *coda);
bool isFullQueue(Queue *coda);
int popQueue(Queue *coda);
bool trova_arco(Citta grafo[], int id_coda, int id_testa);


int main() {
    Citta grafo[MAX_VERTICI];
    int n_nodi = 0, choice, node1, node2;
    int *visited = (int *) calloc(NUM_NODI_TEST, sizeof(int));
    reset_visitati(visited);

    //Inserire qui le chiamate per testare le varie funzioni e il menu
    do {
        printf("[1] Aggiungi nodo\n"
               "[2] Crea arco\n"
               "[3] Stampa adiacenze\n"
               "[4] Visita in profondità - DFS\n"
               "[5] Visita in ampiezza - BFS\n"
               "[6] Cancella arco\n"
               "[7] Stampa componenti connesse\n"
               "[8] Test grafo orientato\n"
               "[9] Test grafo non orientato\n"
               "[0] Esci\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                aggiungi_nodo(grafo, &n_nodi);
                break;

            case 2:
                node1 = scegli_citta(grafo, n_nodi + 1);
                node2 = scegli_citta(grafo, n_nodi + 1);
                printf("[1] Arco orientato\n"
                       "[2] Arco non orientato\n");
                scanf("%d", &choice);

                if (choice == 1) {
                    if (trova_arco(grafo, node1, node2)) {
                        printf("Arco già presente\n");
                        break;
                    }
                    crea_arco(grafo, node1, node2, n_nodi);

                } else {
                    if (!trova_arco(grafo, node1, node2)) {
                        crea_arco(grafo, node1, node2, n_nodi);
                    }
                    if (!trova_arco(grafo, node2, node1)) {
                        crea_arco(grafo, node2, node1, n_nodi);
                    }
                }
                break;

            case 3:
                stampa_lista_adiacenze(grafo, n_nodi);
                break;

            case 4:
                node1 = scegli_citta(grafo, n_nodi + 1);
                DFS(grafo, visited, node1);
                reset_visitati(visited);
                break;

            case 5:
                node1 = scegli_citta(grafo, n_nodi + 1);
                BFS(grafo, visited, node1);
                reset_visitati(visited);
                break;

            case 6:
                do {
                    printf("[1] Arco orientato\n"
                           "[2] Arco non orientato\n");
                    scanf("%d", &choice);
                } while (choice != 1 && choice != 2);

                printf("Coda arco:\n");
                node1 = scegli_citta(grafo, n_nodi + 1);

                printf("Testa arco:\n");
                node2 = scegli_citta(grafo, n_nodi + 1);

                switch (choice) {
                    case 1:
                        cancella_arco_orientato(grafo, node1, node2, n_nodi);
                        break;
                    case 2:
                        cancella_arco_non_orientato(grafo, node1, node2, n_nodi);
                        break;
                    default:
                        exit(EXIT_FAILURE);
                }
                break;

            case 7:
                componenti_connesse(grafo, visited, n_nodi);
                reset_visitati(visited);
                break;

            case 8:
                if (n_nodi > 0) {
                    printf("Il grafo deve essere vuoto!\n");
                    break;
                }
                n_nodi = NUM_NODI_TEST;
                carica_grafo_test_orientato(grafo, n_nodi);
                break;

            case 9:
                if (n_nodi > 0) {
                    printf("Il grafo deve essere vuoto!\n");
                    break;
                }
                n_nodi = NUM_NODI_TEST;
                carica_grafo_test_non_orientato(grafo, n_nodi);
                break;

            case 0:
                free(visited);
                return 0;

            default:
                printf("Riprovare\n");
        }
    } while (true);
}


void carica_citta_test(Citta grafo[])
{
    //Cagliari
    strcpy(grafo[0].nome, "Cagliari");
    strcpy(grafo[0].nazione, "Italia");
    grafo[0].abitanti = 300000;
    grafo[0].lista_adj = NULL;

    //Zurigo
    strcpy(grafo[1].nome, "Zurigo");
    strcpy(grafo[1].nazione, "Svizzera");
    grafo[1].abitanti = 400000;
    grafo[1].lista_adj = NULL;

    //Lione
    strcpy(grafo[2].nome, "Lione");
    strcpy(grafo[2].nazione, "Francia");
    grafo[2].abitanti = 500000;
    grafo[2].lista_adj = NULL;

    //Genova
    strcpy(grafo[3].nome, "Genova");
    strcpy(grafo[3].nazione, "Italia");
    grafo[3].abitanti = 800000;
    grafo[3].lista_adj = NULL;

    //Roma
    strcpy(grafo[4].nome, "Roma");
    strcpy(grafo[4].nazione, "Italia");
    grafo[4].abitanti = 4000000;
    grafo[4].lista_adj = NULL;

    //New York
    strcpy(grafo[5].nome, "New York");
    strcpy(grafo[5].nazione, "USA");
    grafo[5].abitanti = 8500000;
    grafo[5].lista_adj = NULL;

    //Bilbao
    strcpy(grafo[6].nome, "Bilbao");
    strcpy(grafo[6].nazione, "Spagna");
    grafo[6].abitanti = 350000;
    grafo[6].lista_adj = NULL;

    //Berlino
    strcpy(grafo[7].nome, "Berlino");
    strcpy(grafo[7].nazione, "Germania");
    grafo[7].abitanti = 3500000;
    grafo[7].lista_adj = NULL;

    //Londra
    strcpy(grafo[8].nome, "Londra");
    strcpy(grafo[8].nazione, "Gran Bretagna");
    grafo[8].abitanti = 8700000;
    grafo[8].lista_adj = NULL;

    //Miami
    strcpy(grafo[9].nome, "Miami");
    strcpy(grafo[9].nazione, "USA");
    grafo[9].abitanti = 450000;
    grafo[9].lista_adj = NULL;

    //Tokyo
    strcpy(grafo[10].nome, "Tokyo");
    strcpy(grafo[10].nazione, "Giappone");
    grafo[10].abitanti = 13700000;
    grafo[10].lista_adj = NULL;
}

void carica_grafo_test_orientato(Citta grafo[], int num_nodi)
{
    carica_citta_test(grafo);

    //Creazione archi
    crea_arco(grafo, 0, 1, num_nodi);
    crea_arco(grafo, 0, 4, num_nodi);

    crea_arco(grafo, 1, 0, num_nodi);
    crea_arco(grafo, 1, 2, num_nodi);

    crea_arco(grafo, 2, 1, num_nodi);
    crea_arco(grafo, 2, 3, num_nodi);

    crea_arco(grafo, 4, 0, num_nodi);
    crea_arco(grafo, 4, 1, num_nodi);
    crea_arco(grafo, 4, 5, num_nodi);
    crea_arco(grafo, 4, 6, num_nodi);

    crea_arco(grafo, 5, 1, num_nodi);

    crea_arco(grafo, 6, 7, num_nodi);

    crea_arco(grafo, 8, 9, num_nodi);

    crea_arco(grafo, 9, 8, num_nodi);
    crea_arco(grafo, 9, 10, num_nodi);
}

void carica_grafo_test_non_orientato(Citta grafo [], int num_nodi)
{
    carica_citta_test(grafo);

    //Creazione archi
    crea_arco(grafo, 0, 1, num_nodi);
    crea_arco(grafo, 1, 0, num_nodi);

    crea_arco(grafo, 0, 4, num_nodi);
    crea_arco(grafo, 4, 0, num_nodi);

    crea_arco(grafo, 1, 2, num_nodi);
    crea_arco(grafo, 2, 1, num_nodi);

    crea_arco(grafo, 2, 3, num_nodi);
    crea_arco(grafo, 3, 2, num_nodi);

    crea_arco(grafo, 4, 1, num_nodi);
    crea_arco(grafo, 1, 4, num_nodi);

    crea_arco(grafo, 4, 5, num_nodi);
    crea_arco(grafo, 5, 4, num_nodi);

    crea_arco(grafo, 4, 6, num_nodi);
    crea_arco(grafo, 6, 4, num_nodi);

    crea_arco(grafo, 5, 1, num_nodi);
    crea_arco(grafo, 1, 5, num_nodi);

    crea_arco(grafo, 6, 7, num_nodi);
    crea_arco(grafo, 7, 6, num_nodi);

    crea_arco(grafo, 8, 9, num_nodi);
    crea_arco(grafo, 9, 8, num_nodi);

    crea_arco(grafo, 9, 10, num_nodi);
    crea_arco(grafo, 10, 9, num_nodi);
}

void aggiungi_nodo(Citta grafo[], int *num_nodi)
{
    int idx, choice;

    if ((*num_nodi) >= MAX_VERTICI) {
        printf("Numero massimo di nodi raggiunto\n");
        return;
    }

    (*num_nodi)++;
    printf("Inserire nome citta':");
    scanf(" %s", grafo[(*num_nodi)-1].nome);

    printf("Inserire numero abitanti:");
    scanf("%d", &grafo[(*num_nodi)-1].abitanti);

    printf("Inserire la nazione:");
    scanf(" %s", grafo[(*num_nodi)-1].nazione);

    grafo[(*num_nodi)-1].lista_adj = NULL;
}

void crea_arco(Citta grafo[], int idx_coda, int idx_testa, int num_nodi) {
    Node *adj = NULL,
            *new_node = NULL;

    if (idx_coda > num_nodi - 1 || idx_coda < 0 || idx_testa > num_nodi - 1 || idx_testa < 0) {
        printf("Errore, id non valido!\n");
        return;
    }

    adj = grafo[idx_coda].lista_adj;
    new_node = (Node *) malloc(sizeof(Node));

    if (adj == NULL) {
        grafo[idx_coda].lista_adj = new_node;
        new_node->vertex_id = idx_testa;
        new_node->link = NULL;
    } else {
        new_node->link = grafo[idx_coda].lista_adj;
        new_node->vertex_id = idx_testa;
        grafo[idx_coda].lista_adj = new_node;
    }
}

void stampa_lista_adiacenze(Citta grafo[], int num_nodi)
{
    Node *adj = NULL;
    for (int i = 0; i < num_nodi; ++i) {
        printf("%s", grafo[i].nome);
        adj = grafo[i].lista_adj;
        while (adj!=NULL) {
            printf(" --> %s\t", grafo[adj->vertex_id].nome);
            adj = adj->link;
        }
        printf("\n");
    }
}

void DFS(Citta grafo[], int visited[], int start_id)
{
    Node *adj = NULL;
    int id_next;
    visita_nodo(grafo, start_id);
    visited[start_id] = 1;
    adj = grafo[start_id].lista_adj;

    while (adj != NULL) {
        id_next = adj->vertex_id;
        if (visited[id_next] == 0) {
            DFS(grafo, visited, id_next);
        }
        adj = adj->link;
    }
}

void BFS(Citta grafo[], int visited[], int start_id)
{
    int i;
    Node *adj = NULL;
    Queue C;

    visita_nodo(grafo, start_id);
    visited[start_id] = 1;
    C.cont = 0;
    pushQueue(&C, start_id);

    while (!isEmptyQueue(&C)) {
        i = popQueue(&C);
        adj = grafo[i].lista_adj;

        while (adj != NULL) {
            if (visited[adj->vertex_id] == 0) {
                pushQueue(&C, adj->vertex_id);
                visita_nodo(grafo, adj->vertex_id);
                visited[adj->vertex_id] = 1;
            }
            adj = adj->link;
        }
    }
}

void cancella_arco_orientato(Citta grafo[], int id_coda, int id_testa, int num_nodi)
{
    Node *adj = NULL;
    if (id_coda>num_nodi-1 || id_coda<0 || id_testa>num_nodi-1 || id_testa<0) {
        printf("Errore, id non valido!\n");
        return;
    }

    adj = grafo[id_coda].lista_adj;
    if (adj == NULL) {
        printf("Nessun arco presente\n");
        return;
    }
    if (adj->vertex_id == id_testa) {
        grafo[id_coda].lista_adj = adj->link;
        free(adj);
        printf("Arco eliminato!\n");
        return;
    }

    while (adj->link != NULL) {
        if (adj->link->vertex_id == id_testa) {
            adj->link = adj->link->link;
            free(adj->link);
            printf("Arco eliminato!\n");
            return;
        }
        adj = adj->link;
    }
    printf("Arco non presente\n");
}

void cancella_arco_non_orientato(Citta grafo[], int id_coda, int id_testa, int num_nodi)
{
    if (id_coda > num_nodi-1 || id_coda < 0 || id_testa > num_nodi-1 || id_testa < 0) {
        printf("Errore, id non valido!\n");
        return;
    }

    if (!trova_arco(grafo, id_coda, id_testa) || !trova_arco(grafo, id_testa, id_coda)) {
        printf("Arco non orientato assente\n");
        return;
    }
    cancella_arco_orientato(grafo, id_coda, id_testa, num_nodi);
    cancella_arco_orientato(grafo, id_testa, id_coda, num_nodi);
}

void componenti_connesse(Citta grafo[], int visited[], int num_nodi)
{
    if (num_nodi == 0) {
        printf("Grafo vuoto\n");
        return;
    }
    int num_componenti = 0;
    for (int i = 0; i < num_nodi; ++i) {
        if (visited[i] == 0) {
            printf("Componente %d:\n", num_componenti+1);
            BFS(grafo, visited, i);
            printf("\n");
            num_componenti++;
        }
    }
    reset_visitati(visited);
}

int scegli_citta(Citta grafo[], int num_nodi) {
    int choice;
    for (int i = 0; i < num_nodi-1; ++i) {
        printf("[%d] %s\n", i, grafo[i].nome);
    }
    do {
        printf("Inserire un numero da 0 a %d:", num_nodi-2);
        scanf("%d", &choice);
    } while (choice < 0 || choice > num_nodi-2);
    return choice;
}

void visita_nodo(Citta grafo[], int id) {
    printf("%s\n%d\n%s\n\n", grafo[id].nome, grafo[id].abitanti, grafo[id].nazione);
}

void reset_visitati(int visited[]) {
    for (int i = 0; i < NUM_NODI_TEST; ++i) {
        visited[i] = 0;
    }
}

void pushQueue(Queue *coda, int id) {
    Node* node = NULL;
    if (isFullQueue(coda)) {
        printf("Errore, coda piena\n");
    } else {
        node = (Node*)malloc(sizeof(Node));
        if (node == NULL) {
            exit(EXIT_FAILURE);
        }
        node->vertex_id = id;
        node->link = NULL;

        if (isEmptyQueue(coda)) {
            coda->front = node;
            coda->back = node;
        } else {
            coda->back->link = node;
            coda->back = node;
        }
        coda->cont++;
    }
}

bool isEmptyQueue(Queue *coda) {
    if (coda->cont == 0) {
        return true;
    } else {
        return false;
    }
}

bool isFullQueue(Queue *coda) {
    if (coda->cont == MAX_VERTICI) {
        return true;
    } else {
        return false;
    }
}

int popQueue(Queue *coda) {
    int val;
    Node* temp = NULL;
    if (isEmptyQueue(coda)) {
        printf("Lista vuota\n");
        val = -1;
    } else {
        temp = coda->front;
        val = temp->vertex_id;

        if (coda->cont == 1) {
            coda->front = NULL;
            coda->back = NULL;
        } else {
            coda->front = coda->front->link;
        }
        coda->cont--;
    }
    free(temp);
    return val;
}

bool trova_arco(Citta grafo[], int id_coda, int id_testa) {
    Node *adj = NULL;
    adj = grafo[id_coda].lista_adj;

    while (adj != NULL && adj->vertex_id != id_testa) {
        adj = adj->link;
    }

    return adj != NULL ? true : false;
}
