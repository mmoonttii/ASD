/// heapSort

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../usefulFunctions.h"

#define N 100
void heapSort(int lista[], int n);
void adatta(int lista[], int radice, int n);

int main() {
    int *arr = generaArray(N, CASUALE);

    printf("Array non ordinato: ");
    printArray(arr, N);

    heapSort(arr, N);

    printf("Array ordinato: ");
    printArray(arr, N);
    return 0;
}
/**algoritmo heapsort(array lista, int n) → void
	// Si costruisce lo heap associato all'insieme da ordinare lista
	for i ← n/2 downto 1
		adatta(lista, i, n)

	for i ← n-1 downto 1
		//si estrae, di volta in volta, il massimo lista[1] e lo si posiziona in fondo alla sequenza
		scambia (lista[1], lista[i+1])
		// si opera nuovamente sullo heap ridotto di un elemento
		adatta(lista, 1, i)
 */

void heapSort(int lista[], int n) {
	for (int i = n / 2; i >= 1; i--) {
		adatta(lista, i, n);
	}

	for (int i = n - 1; i >= 1; i--) {
		swap(&lista[1], &lista[i + 1]);
		adatta(lista, 1, i);
	}
}

/**algoritmo adatta(array lista, int radice, int n) → void
	temp ← lista[radice]
	figlio ← 2 × radice // figlio sx
	while (figlio ≤ n) do
		// trova il maggiore tra il figlio sx e figlio dx
		if (figlio < n and lista[figlio] < lista[figlio+1] ) then
			figlio ← figlio + 1

		// confronta la radice e figlio max
		if (temp > lista[figlio]) then
			break // il padre di figlio sarà la posizione corretta
		else
			lista[figlio/2] ← lista[figlio] // il figlio si sposta verso il padre
			// ripeti sul sottoalbero selezionato
			figlio ← 2 × figlio

	lista[figlio/2] ← temp // copia la radice nella posizione corretta
 */
void adatta(int lista[], int radice, int n) {
	int temp = lista[radice];
	int figlio = 2 * radice;

	while (figlio <= n) {
		if (figlio < n && lista[figlio] < lista[figlio + 1]) {
			figlio++;
		}

		if (temp > lista[figlio]) {
			break;
		} else {
			lista[figlio / 2] = lista[figlio];
			figlio *= 2;
		}
	}
	lista[figlio / 2] = temp;
}
