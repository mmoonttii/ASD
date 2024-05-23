#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

int kmpMatch(char *string, char *pattern) {
    int *insuccesso = funzInsuccesso(pattern);

    int i = 0,
            j = 0,
            lenS = strlen(string),
            lenP = strlen(pattern);

    while (i < lenS && j < lenP) {
        if (string[i] == pattern[j]) {
            i++;
            j++;
        } else if (j == 0) {
            i++;
        } else {
            j = insuccesso[j - 1] + 1;
        }
    }

    if (j == lenP) {
        free(insuccesso);
        return i - lenP;
    } else {
        free(insuccesso);
        return -1;
    }
}

int main(){
    char string[STR_LEN] = {},
            pattern[STR_LEN] = {};

    int idx;

    _Bool retry = 0;

    while (retry == 0){
        printf("Inserisci stringa dove cercare il pattern: ");
        scanf("%127[^\n]s", string);

        printf("Inserisci pattern ciclico da cercare: ");
        scanf("%127[^\n]s", pattern);

        if (strlen(string) == strlen(pattern)) {
            // TODO: KMP per controllo rotazioni cicliche
        } else {
            printf("Il pattern e la stringa devono avere la stessa lunghezza, riprovare");
            retry = 1;
        }
    }

    printf("Il pattern è stato trovato alla pos %d", idx);

    return 0;
}