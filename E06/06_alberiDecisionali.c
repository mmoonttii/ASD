#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>

#define TEXT_LEN 128
typedef struct nodo {
	char *domanda;
	struct nodo *si;
	struct nodo *no;
} Nodo;

/*
 * algoritmo creaNodo(char* domanda) -> *Nodo
 * Nodo *new_nodo = alloca new_nodo
 * inserisci i dati in new_nodo
 * inizializza le scelte si e no
 * return new_nodo
 */
Nodo *creaNodo(char *domanda) {
	Nodo *new_nodo = NULL;
	new_nodo = (Nodo *)malloc(sizeof(Nodo));
	new_nodo->domanda = domanda;
	new_nodo->no = NULL;
	new_nodo->si = NULL;
	return new_nodo;
}

/*
 * algoritmo isLeaf(Nodo* nodo) -> Bool
 * if(nodo è una foglia):
 *      return True
 * return False
 */
bool isLeaf(Nodo *nodo) {
	if (nodo->si == NULL && nodo->no == NULL) {
		return true;
	}
	return false;
}

/*
 * algoritmo navigaAlbero(Nodo* radice) -> char*
 * Nodo* nodo = radice
 * while(!isLeaf(nodo))
 * stampa i dati del nodo
 * richiesta spostamento figlio destro o sinistro
 * return risposta del nodo
 */
char *navigaAlbero(Nodo *rdx) {
	Nodo *nodo = rdx;
	int choice = 0;

	while (!isLeaf(nodo)) {
		choice = 0;
		printf(" %s\n", nodo->domanda);
		printf("[0] No\n"
			   "[1] Si\n");
		scanf("%d", &choice);
		switch (choice) {
			case 0:
				nodo = nodo->no;
			case 1:
				nodo = nodo->si;
		}
	}
	return nodo->domanda;
}

/*
 * algoritmo creaAlberoDecisionale(Nodo* radice) -> Nodo*
 *     bool flag;
 *     do {
 *         nodo = radice
 *         while(!(isLeaf(nodo))){
 *             seleziona figlio in cui muoversi
 *         }
 *         crea e collega figlio sinistro a nodo
 *         crea e collega figlio destro a nodo
 *         acquisisci flag
 *     } while(flag)
 *     return radice
 */

char *creaDomanda() {
	char *domanda = NULL;
	domanda = (char *)calloc(TEXT_LEN + 1, sizeof(char));
	printf("Inserisci domanda: ");
	scanf(" %128[^\n]s", domanda);
	return domanda;
}

Nodo *creaAlberoDecisionale(Nodo *rdx) {
	bool flag, retry = false;
	int choice = 0;
	char *domanda;
	Nodo *nodo = NULL;
	do {
		nodo = rdx;
		while (!isLeaf(nodo)) {
			printf(" %s\n", nodo->domanda);
			do {
				retry = false;
				printf("[0] No\n"
				       "[1] Si\n"
					   ">>> ");
				scanf("%d", &choice);
				switch (choice) {
					case 0:
						nodo = nodo->no;
					case 1:
						nodo = nodo->si;
					default:
						printf("Errore, riprova\n");
						retry = true;
				}
			} while (retry);
		}
		printf("%s\n", nodo->domanda);
		printf("Nodo no\n");
		domanda = creaDomanda();
		nodo->no = creaNodo(domanda);

		printf("Nodo si\n");
		domanda = creaDomanda();
		nodo->si = creaNodo(domanda);

		printf("Hai finito o vuoi continuare?\n"
			   "[0] Finito\n"
			   "[1] Voglio continuare\n");
		scanf("%d", &choice);
		flag = choice == 0 ? false : true;
	} while (flag);
	return rdx;
}

void classificaPesce(Nodo *rdx) {
	char *ans = NULL;
	ans = navigaAlbero(rdx);
	printf("%s", ans);
}

void freeAll(Nodo *rdx) {
	if (rdx != NULL) {
		freeAll(rdx->si);
		freeAll(rdx->no);
	}
	free(rdx);
}

int main(){
	Nodo *rdx = NULL;
	char *domanda = NULL;
	domanda = creaDomanda();
	rdx = creaNodo(domanda);
	rdx = creaAlberoDecisionale(rdx);

	classificaPesce(rdx);
	freeAll(rdx);
	return 0;
}
