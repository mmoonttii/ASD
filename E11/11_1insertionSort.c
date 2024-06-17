#include "../usefulFunctions.h"
/*
algoritmo insertionSort(array lista, int dim) → void
for i ← 1 to dim-1 do
prossimo ← lista[i]
for j← i-1 downto 0 do
if (prossimo < lista[j]) then
lista[j+1]← lista[j]
else
break
lista[j+1] ← prossimo
*/

void insertionSort(int lista[], int dim) {
	int prossimo;
	int j;

	for (int i = 1; i < dim; i++) {
		prossimo = lista[i];
		for (j = i - 1; j >= 0; j--) {
			if (prossimo < lista[j]) {
				lista[j + 1] = lista[j];
			} else {
				break;
			}
		}
		lista[j + 1] = prossimo;
	}
}

/**algoritmo perno(array lista, int primo, int ultimo) → int
	i ← primo
	j← ultimo + 1
	pivot ← lista[primo]
	while (i < j) do
		do i ← i+1 while (i <= ultimo and lista[i] ≤ pivot)
		do j ← j–1 while (j >= primo and lista[j] > pivot)
		if (i < j) then
			scambia (lista[i], lista[j])
	scambia (lista[primo], lista[j])
	return j
 */

int perno(int arr[], int primo, int ultimo) {
	int i = primo;
	int j = ultimo + 1;
	int pivot = arr[primo];

	while (i < j) {
		do {
			i++;
		} while (i <= ultimo && arr[i] <= pivot);

		do {
			j--;
		} while (j >= primo && arr[j] > pivot);

		if (i < j) {
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[primo], &arr[j]);
	return j;
}

/**algoritmo quickSort(array lista, int u, int v) → void
	if (u == v) then return
	q ← perno(lista, u, v)
	if (u < q) then quickSort(lista, u, q–1)
	if (q < v) then quickSort(lista, q+1, v)
*/

void quickSort(int arr[], int u, int v) {
	if (u == v) return;
	int q = perno(arr, u, v);
	if (u < q) quickSort(arr, u, q - 1);
	if (q < v) quickSort(arr, q + 1, v);
}

