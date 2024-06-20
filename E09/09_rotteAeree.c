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
 * Per rappresentare un grafo si possono rappresentare tramite liste di adiacenza
 */


// Mediante un grafo orientato vogliamo rappresentare le rotte di una compagnia aerea
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICI 20
#define DIM 50
#define NUM_NODI_TEST 11

typedef struct node{
    int vertex_id;
    struct node* link;
} Node;

typedef struct {
    char nome[DIM];
    int  abitanti;
    char nazione[DIM];
    Node* lista_adj;
} Citta;

typedef struct {
    Node* front;
    Node* back;
    int cont;
} Queue;

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
void crea_arco(Citta grafo[], int id_coda, int id_testa, int num_nodi);
void stampa_lista_adiacenze(Citta grafo[], int num_nodi);

void DFS(Citta grafo[], int visited[], int start_id);
void BFS(Citta grafo[], int visited[], int start_id);

void cancella_arco_orientato(Citta grafo[], int id_coda, int id_testa, int num_nodi);
void cancella_arco_non_orientato(Citta grafo[], int id_coda, int id_testa, int num_nodi);

void componenti_connesse(Citta grafo[], int visited[], int num_nodi);

int main() {
    Citta grafo[MAX_VERTICI];
    int num_nodi;
    int *visited = (int*)calloc(NUM_NODI_TEST, sizeof(int));

    //Inserire qui le chiamate per testare le varie funzioni e il menu
}

void carica_citta_test(Citta grafo[]) {
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

void carica_grafo_test_orientato(Citta grafo[], int num_nodi) {
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

void carica_grafo_test_non_orientato(Citta grafo [], int num_nodi) {
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

/// Funzioni da implementare
/*
    Aggiunge una città nel grafo chiedendo i dati all’utente
*/
void aggiungi_nodo(Citta grafo[], int *num_nodi) {
	char tmp_nome[DIM] = {},
		 tmp_nazione[DIM] = {};

	int tmp_abitanti = 0;

	if (*num_nodi >= MAX_VERTICI) {
        printf("Grafo pieno\n");
        return;
	}

	(*num_nodi)++;
	printf("Inserisci nome città: ");
	scanf("%[^\n]50s", tmp_nome);
	printf("Insrisci nazione città: ");
	scanf("%[^\n]50s", tmp_nazione);
	printf("Inserisci abitanti città: ");
	scanf("%d", &tmp_abitanti);

	strcpy(grafo[*num_nodi - 1].nome, tmp_nome);
	strcpy(grafo[*num_nodi - 1].nazione, tmp_nazione);
	grafo[*num_nodi - 1].abitanti = tmp_abitanti;
	grafo[*num_nodi - 1].lista_adj = NULL;
}

/*
    crea un arco tra due nodi esistenti (orientato)
*/
void crea_arco(Citta grafo[], int id_coda, int id_testa, int num_nodi) {
	Node *nodo_adj = NULL,
		 *lista_adj = NULL;

	nodo_adj = (Node *)malloc(sizeof(Node));

	if (id_coda < 0 || id_coda > num_nodi - 1) {
        printf("Id nodo coda non valido\n");
        return;
    }
	if (id_testa < 0 || id_testa > num_nodi - 1) {
        printf("Id nodo testa non valido\n");
        return;
    }

	lista_adj = grafo[id_testa].lista_adj;

	if (lista_adj == NULL) {
		grafo[id_testa].lista_adj = nodo_adj;
	} else {
		for (; lista_adj->link != NULL; lista_adj = lista_adj->link);
		lista_adj->link = nodo_adj;
	}
}

void stampa_lista_adiacenze(Citta grafo[], int num_nodi)
{
    // inserire qui il codice della funzione...
}

void DFS(Citta grafo[], int visited[], int start_id)
{
    // inserire qui il codice della funzione...
}

void BFS(Citta grafo[], int visited[], int start_id)
{
    // inserire qui il codice della funzione...
}

void cancella_arco_orientato(Citta grafo[], int id_coda, int id_testa, int num_nodi)
{
    // inserire qui il codice della funzione...

}

void cancella_arco_non_orientato(Citta grafo[], int id_coda, int id_testa, int num_nodi)
{
    // inserire qui il codice della funzione...
}

void componenti_connesse(Citta grafo[], int visited[], int num_nodi)
{
    // inserire qui il codice della funzione...
}
