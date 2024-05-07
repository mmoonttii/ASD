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
struct song
{
    char title[DIM_TITLE];
    char genre[DIM_GENRE];
    float length;
    struct song* prev;
    struct song* next;
};

typedef struct song Song;

//struttura che rappresenta una PLAYLIST
struct playlist
{
    char name[DIM_NAME];
    Song* top;
};

typedef struct playlist PlayList;

//funzioni (gia' definite) per l'acquisizione e per la stampa di una canzone
Song* acquireSong(); //acquisisce i dati di UNA canzone chiedendoli all'utente
void printSong(Song* s); //stampa i dati relativi ad UNA canzone (passata tramite puntatore)
void insertSong(PlayList* pl, Song* s);

//prototipi funzioni STUDENTE
//...

int main()
{
  //Creazione di una PLAYLIST. Utilizzare e riempire questa playlist
    PlayList p;
    strcpy(p.name, "My favourite songs");
    p.top = NULL;

    //altre chiamate e istruzioni per testare il funzionamento delle funzioni create
    //...


    return 0;
}


/* ---------------------------------------------
* funzioni da NON modificare
* --------------------------------------------*/
Song* acquireSong()
{
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

void printSong(Song* t)
{
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
void insertSong(PlayList* pl, Song* s) {
/* if(playlist vuota) then
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

	Song *tmp_prev = NULL,
		 *tmp_next = NULL;

	if (pl->top == NULL) {
		// <gestire il caso per la lista vuota>
	} else {
		tmp_prev = NULL;
		tmp_next = pl->top;

		while (tmp_next != NULL && strcmp(tmp_next->title, s->title) <= 0) {
			tmp_prev = tmp_next;
			tmp_next = tmp_next->next;
		}
		if (tmp_prev->next == NULL) {
			tmp_prev->next = s;
		} else if (tmp_prev == NULL) {
			s->next = pl->top;
			pl->top = s;
		} else {
			// Inserimento generico tra nodi
		}
	}
}

Song* findSong(PlayList* pl, char title[]) {
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

void deleteSong(PlayList *pl, Song *s) {

}

void modifySong(PlayList *pl, Song *s) {
	printSong(s);
	printf("Inserisci i nuovi dati della canzone");
	s = acquireSong();

	deleteSong(pl, s);
	insertSong(pl, s);
}



void printPlaylist(PlayList *pl) {
	Song *aux = NULL;
	aux = pl->top;
	while (aux != NULL) {
		printSong(aux);
	}
}

