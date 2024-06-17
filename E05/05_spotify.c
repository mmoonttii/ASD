/* Le liste sono un insieme dinamico di elementi con accesso sequenziale
 * Ogni elemento della lista ha una chiave e un riferimento all'elemento successivo nella lista
 *
 * Esistono diversi tipi di lista:
 *  - lineari singolarmente concatenate
 *  - lineari doppiamente concatenate
 *  - circolari singolarmente concatenate
 *  - circolari doppiamente concatenate
 *
 * inserimento ordinato:
 *  - Si cerca il posto in cui inserire il nuovo nodo
 *  - Si inserisce il nuovo elemento adattando i collegamemti
 * cancellazione:
 *  -
 * fusione:
 *  -,,,,
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_TITLE 50
#define DIM_GENRE 50
#define DIM_NAME 50

//struttura che rappresenta una CANZONE
typedef struct song {
    char title[DIM_TITLE];
    char genre[DIM_GENRE];
    float length;
    struct song* prev;
    struct song* next;
} Song;

//struttura che rappresenta una PLAYLIST
typedef struct playlist {
    char name[DIM_NAME];
    Song* top;
} Playlist;

//funzioni (gia' definite) per l'acquisizione e per la stampa di una canzone
Song* acquireSong(); //acquisisce i dati di UNA canzone chiedendoli all'utente
void printSong(Song* s); //stampa i dati relativi ad UNA canzone (passata tramite puntatore)
Song *nextSong(Song *s);
Song *prevSong(Song *s);

//prototipi funzioni STUDENTE
void insertSong(Playlist* pl, Song* s);
Song* findSong(Playlist* pl, char title[]);
void printPlaylist(Playlist* pl);
void modifySong(Playlist* pl, Song* s);
void deleteSong(Playlist* pl, Song* s);
void mergePlaylist(Playlist* a, Playlist* b, Playlist* c);


int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
  //Creazione di una PLAYLIST. Utilizzare e riempire questa playlist
    Playlist p;
    strcpy(p.name, "My favourite songs");
    p.top = NULL;

    Playlist b;
    strcpy(b.name, "Playlist b");
    b.top = NULL;

    Playlist c;
    strcpy(c.name, "Playlist c");
    c.top = NULL;

    int choice;
    Song *s, *aux;
    char title[DIM_TITLE];

    while (1) {
        printf("\nMenu:"
            "\n[1] Inserisci nuova canzone"
            "\n[2] Cerca una canzone"
            "\n[3] Stampa playlist"
            "\n[4] Modifica una canzone"
            "\n[5] Cancella una canzone"
            "\n[6] Unisci due playlist"
            "\n[0] Esci");
        printf("\n>>> ");
        scanf("%d", &choice);
		getchar();

        switch (choice) {
            case 1:
                s = acquireSong();
				getchar();
                insertSong(&p, s);
                break;

            case 2:
                printf("\nCanzone da cercare: ");
                scanf("%49[^\n]s", title);
                getchar();
                s = findSong(&p, title);
                if (s != NULL) {
                    printSong(s);
                }
                break;

            case 3:
                printPlaylist(&p);
                putchar('\n');
                printPlaylist(&b);
                putchar('\n');
                printPlaylist(&c);
                putchar('\n');
                break;

            case 4:
                printf("\nCanzone da modificare: ");
                scanf("%49[^\n]s", title);
                s = findSong(&p, title);
                if (s != NULL) {
                    modifySong(&p, s);
                } else {
                    printf("\nCanzone non trovata");
                }
                break;

            case 5:
                printf("\nCanzone da eliminare: ");
                scanf("%49[^\n]s", title);
                s = findSong(&p, title);
                if (s != NULL) {
                    deleteSong(&p, s);
                } else {
                    printf("\nCanzone non trovata");
                }
                break;

            case 6:
                mergePlaylist(&p, &b, &c);
                break;

            case 0:
                aux = p.top;
                while (aux!=NULL) {
                    p.top = p.top->next;
                    free(aux);
                    aux = p.top;
                }

                aux = b.top;
                while (aux!=NULL) {
                    b.top = b.top->next;
                    free(aux);
                    aux = b.top;
                }
                aux = c.top;
                while (aux!=NULL) {
                    c.top = c.top->next;
                    free(aux);
                    aux = c.top;
                }
                return 0;

            default:
                printf("\nScelta non valida, riprovare\n");
        }
    }



    return 0;
}


/* ---------------------------------------------
* funzioni da NON modificare
* --------------------------------------------*/
Song* acquireSong() {
    Song* new_s = (Song*)malloc(sizeof(Song));
    printf("\nInsert title -> ");
    scanf("%[^\n]s", new_s->title);
    getchar();

    printf("Insert genre -> ");
    scanf("%[^\n]s", new_s->genre);
    getchar();

    printf("Insert length -> ");
    scanf("%f", &(new_s->length));
    getchar();

    new_s->prev = NULL;
    new_s->next = NULL;

    return new_s;
}

void printSong(Song* t){
    printf("TITLE :%s \n", t->title);
    printf("GENRE :%s \n", t->genre);
    printf("LENGTH:%.2f \n\n", t->length);
}

Song *nextSong(Song *s) {
	return s->next;
}

Song *prevSong(Song *s) {
	return s->prev;
}

/* ---------------------------------------------
* funzioni STUDENTE
* --------------------------------------------*/

/** Inserisce una canzone (creata con la funzione acquire) nella lista in maniera ordinata

if(playlist vuota) then
    <gestire il caso per la lista vuota>
else
	//ricerca della posizione in cui inserire (tmp_prev e tmp_next sono due puntatori d’appoggio)
	tmp_prev = NULL
	tmp_next = testa della playlist
	while(tmp_next ≠ NULL and tmp_next->title ≤ s->title) //attenzione al confronto tra stringhe!
		tmp_prev = tmp_next
		tmp_next = tmp_next->next
	//ora conosciamo il nodo a cui appendere il nuovo nodo s
	if(siamo arrivati alla fine della playlist) then
		<gestire il caso di inserimento in coda>
	else if(dobbiamo inserire prima del primo elemento della playlist) then
		<gestire il caso di inserimento in testa>
	else
		<gestire il caso di inserimento generico tra due nodi>
*/
void insertSong(Playlist* pl, Song* s) {
	Song *tmp_prev = NULL,
		 *tmp_next = NULL;

	// Caso playlist vuota
	if (pl->top == NULL) {
		pl->top = s;
	} else {
		// ricerca posizione in cui inserire
		tmp_prev = NULL;
		tmp_next = pl->top;

		while (tmp_next != NULL && strcmp(tmp_next->title, s->title) <= 0) {
			tmp_prev = tmp_next;
			tmp_next = tmp_next->next;
		}

		// Inserimento in coda
		if (tmp_prev->next == NULL) {
			tmp_prev->next = s;
			s->next = NULL;
			s->prev = tmp_prev;
		// Inserimento in testa
		} else if (tmp_prev == NULL) {
			s->next = pl->top;
			pl->top = s;
			s->prev = NULL;
		// Inserimento generico
		} else {
		    tmp_prev->next = s;
            s->next = tmp_next;
            s->prev = tmp_prev;
		}
	}
}

// cerca una canzone nella lista (tramite il titolo) e restituisce il suo puntatore
Song* findSong(Playlist* pl, char title[]) {
	Song *aux = NULL;

	aux = pl->top;
	while (aux != NULL && strcmp(aux->title, title) != 0) {
		aux = aux->next;
	}
	if (aux == NULL) {
		printf("Canzone non trovata");
	}
	return aux;
}

// elimina una canzone gia’ presente (trovata tramite la funzione findSong) e
// dealloca l’elemento
void deleteSong(Playlist *pl, Song *s) {
    Song *aux = NULL;

    // Rimozione se la canzone è in testa
    if (pl->top == s) {
        pl->top = s->next;
        free(s);
    // Rimozione generica
    } else {
        aux = s->prev;
        aux->next = s->next;
        if (s->next != NULL){
            aux->next->prev = aux;
        }
        free(s);
    }
}

// modifica una canzone gia’ presente (trovata tramite la funzione findSong) e
// la riposiziona nella posizione corretta
void modifySong(Playlist *pl, Song *s) {
	printSong(s);
	deleteSong(pl, s);

	printf("Inserisci i nuovi dati della canzone");
	getchar();
	s = acquireSong();

	insertSong(pl, s);
}

//stampa tutte le canzoni presenti nella playlist
void printPlaylist(Playlist *pl) {
	Song *aux = NULL;
	aux = pl->top;
	while (aux != NULL) {
		printSong(aux);
		aux = aux->next;
	}
}

// fonde le liste plA e plB in un’unica lista plC (anch’essa passata come parametro).
// NESSUN nuovo nodo deve essere allocato
void mergePlaylist(Playlist *plA, Playlist *plB, Playlist *plC) {
    Song *aux = NULL;

    // Copia lista A
	aux = plA->top;
    while (aux != NULL) {
        aux = plA->top;
        plA->top = plA->top->next;
        aux->next = NULL;
        aux->prev = NULL;
        insertSong(plC, aux);
    }

    // Copia lista B
	aux = plA->top;
    while (aux != NULL) {
        aux = plB->top;
        plB->top = plB->top->next;
        aux->next = NULL;
        aux->prev = NULL;
        insertSong(plC, aux);
    }
}
