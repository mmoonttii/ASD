#include <string.h>
#include <stdlib.h>

/* Knuth, Morris and Pratt è un algoritmo per il pattern matching che, a differenza dell'algoritmo banale
 * (che ha complessità O(n * m), ha complessità O(n + m)
 *
 * L'algoritmo è diviso in due sezioni: la funzione insuccesso e l'algoritmo stesso
 *
 * Calcolo della funzione Insuccesso:
 * algoritmo insuccesso (Stringa pat) → intero *
    n ← lunghezza di pat
    alloca dinamicamente il vettore insuccesso (insucc)
    insucc[0] ←-1
    // analisi dei prefissi
    for j← 1 to n-1 do
        i ← insucc[j-1]
        while (pat[j] ≠ pat[i+1] and i≥0) do
            i ← insucc[i]

        if (pat[j] == pat[i+1]) then
            insucc[j] ← i+1
        else
            insucc[j] ← -1

    return insucc
 */

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

/*algoritmo KMP_match (Stringa stringa, Stringa pat) → intero
    insucc ← insuccesso(pat)// array insuccesso
    i ← 0
    j ← 0
    lenS ← lunghezza di stringa
    lenP ← lunghezza di pat
    while (i < lenS and j < lenP) do
        if (stringa[i] == pat[j]) then
            i ← i+1
            j ← j+1
        else if (j == 0) then
            i ← i+1
        else
            j ← insucc[j-1]+1
    if (j == lenP) then
        return i-lenP
    else return -1
*/

int kmpMatch(char *stringa, char *pattern) {
    int *insuccesso = funzInsuccesso(pattern);

    int i = 0,
        j = 0,
        lenS = strlen(stringa),
        lenP = strlen(pattern);

    while (i < lenS && j < lenP) {
        if (stringa[i] == pattern[j]) {
            i++;
            j++;
        } else if (j == 0) {
            i++;
        } else {
            j = insuccesso[j - 1] + 1;
        }
    }
    if (j == lenP) {
        return i - lenP;
    } else {
        return -1;
    }
}

int main(){

}