#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define STR_LEN 128

int *funzInsuccesso(char *pat) {
    int n = strlen(pat),
            i,
            *insuccesso = NULL;
    insuccesso = (int *)calloc(n, sizeof(int));
    insuccesso[0] = -1;

    for (int j = 1; j < n; j++) {
        i = insuccesso[j - 1];
        while ((pat[j] != pat[i + 1]) && i >= 0) {
            i = insuccesso[i];
        }
        if (pat[j] == pat[i + 1]) {
            insuccesso[j] = i + 1;
        } else {
            insuccesso[j] = -1;
        }
    }
    return insuccesso;
}

/*Utilizzare tale metodo per creare un nuovo algoritmo, con tempo
lineare, per determinare se un pattern P è una rotazione ciclica di
un’altra stringa S.
Per esempio, data la stringa abcde, le stringhe deabc e eabcd sono
sue rotazioni cicliche.
NB#1: stringa e pattern devono avere la stessa lunghezza
NB#2: l’utilizzo dell’array insuccesso rimane tale e quale!
NB#3: non potete duplicare la stringa
NB#4: basta modificare KMP_match
*/
int kmpMatchCircolare(char *string, char *pattern) {
    int *insuccesso = funzInsuccesso(pattern);

    int str_idx = 0, // i e j sono gli indici per scorrere la stringa e il pattern
        pat_idx = 0,
        str_len = strlen(string),
        starting_pos = 0, // Posizione del primo carattere
        counter = 0;

    bool end_loop = false;

    // Si trova l'indice della prima lettera del pattern sulla stringa
    for (; str_idx < str_len && string[str_idx] != pattern[0]; str_idx++);

    if (str_idx >= str_len) { // Quando non viene trovato il carattere iniziale restituisco -1
        free(insuccesso);
        return -1;
    }

    starting_pos = str_idx;
    str_idx++;
    pat_idx++;
    if (str_idx == str_len) { // Se i è alla fine della stringa, viene riportato all'inizio
            str_idx = 0;
    }

    while ((str_idx != starting_pos || !end_loop) && pat_idx < str_len ){
        if (string[str_idx] == pattern[pat_idx]) {
            str_idx++;
            pat_idx++;
            counter++;
            if (str_idx >= str_len) {
                str_idx = 0;
            }
        } else if (pat_idx == 0) {
                str_idx++;
                counter++;
                if (str_idx >= str_len) {
                    str_idx = 0;
                }
        } else {
            pat_idx = insuccesso[pat_idx - 1] + 1;
        }
        if (counter == str_len + 1) {
            end_loop = true;
        }
    }

    free(insuccesso);
    if (pat_idx == str_len) {
        return 1; // Pattern trovato, è una rotazione circolare
    } else {
        return -1; // Pattern non trovato
    }
}

int main(){
    char string[STR_LEN] = {},
            pattern[STR_LEN] = {};

    int idx;

    bool retry = false;

    while (retry){
        retry = false;
        printf("Inserisci stringa dove cercare il pattern: ");
        scanf("%127[^\n]s", string);

        printf("Inserisci pattern ciclico da cercare: ");
        scanf("%127[^\n]s", pattern);

        if (strlen(string) != strlen(pattern)) {
            printf("Il pattern e la stringa devono avere la stessa lunghezza, riprovare");
            retry = true;
        }
    }
    idx = kmpMatchCircolare(string, pattern);

    if (idx == -1) {
        printf("Il pattern non è una rotazione circolare della stringa\n");
    } else {
        printf("Il pattern è una rotazione circolare della stringa\n");
    }
    return 0;
}
