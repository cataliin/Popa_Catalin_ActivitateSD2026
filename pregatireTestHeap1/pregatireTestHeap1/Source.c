//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//struct Masina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct Masina Masina;
//
//struct Heap {
//	int lungime;
//	int nrMasini;
//	Masina* masini;
//};
//typedef struct Heap Heap;
//
//Masina citireMasinaFisier(FILE* f) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, f);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy(m1.model, aux);
//
//	aux = strtok(NULL, sep);
//
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy(m1.numeSofer, aux);
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//Heap initializareHeap(int lungime) {
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrMasini = 0;
//	heap.masini = malloc(lungime * sizeof(Masina));
//
//	return heap;
//}
//
//void filtreazaHeap(Heap heap, int pozNod) {
//	int pozSt = 2 * pozNod + 1;
//	int pozDr = 2 * pozNod + 2;
//	int pozMax = pozNod;
//
//	if (pozSt < heap.nrMasini && heap.masini[pozMax].pret < heap.masini[pozSt].pret) {
//		pozMax = pozSt;
//	}
//
//	if (pozDr < heap.nrMasini && heap.masini[pozMax].pret < heap.masini[pozDr].pret) {
//		pozMax = pozDr;
//	}
//
//	if (pozMax != pozNod) {
//		Masina aux = heap.masini[pozMax];
//		heap.masini[pozMax] = heap.masini[pozNod];
//		heap.masini[pozNod] = aux;
//		filtreazaHeap(heap, pozMax);
//	}
//}
//
////void filtreazaHeap(Heap heap, int pozNod) {
////	int pozSt = pozNod * 2 + 1;
////	int pozDr = pozNod * 2 + 2;
////	int pozMax = pozNod;
////
////	if (pozSt < heap.nrMasini && heap.masini[pozMax].pret < heap.masini[pozSt].pret)
////	{
////		pozMax = pozSt;
////	}
////	if (pozDr < heap.nrMasini && heap.masini[pozMax].pret < heap.masini[pozDr].pret) {
////		pozMax = pozDr;
////	}
////	if (pozMax != pozNod) {
////		Masina aux = heap.masini[pozMax];
////		heap.masini[pozMax] = heap.masini[pozNod];
////		heap.masini[pozNod] = aux;
////		filtreazaHeap(heap, pozMax);
////
////	}
////}
//
//Heap citireMasiniHeap(const char* numeFis) {
//	FILE* f = fopen(numeFis, "r");
//	Heap heap = initializareHeap(10);
//	while (!feof(f)) {
//		heap.masini[heap.nrMasini++] = citireMasinaFisier(f);
//	}
//	fclose(f);
//	for (int i = (heap.nrMasini - 2) / 2; i >= 0; --i) {
//		filtreazaHeap(heap, i);
//	}
//	return heap;
//}
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrMasini; ++i) {
//		afisareMasina(heap.masini[i]);
//	}
//}
//
//Masina extrageMasina(Heap* heap) {
//	Masina aux;
//	if (heap->nrMasini > 0) {
//		aux = heap->masini[0];
//		heap->masini[0] = heap->masini[heap->nrMasini - 1];
//		heap->masini[heap->nrMasini - 1] = aux;
//		heap->nrMasini--;
//		filtreazaHeap(*heap, 0);
//	}
//	return aux;
//}
//
//int main() {
//	Heap heap = citireMasiniHeap("masini.txt");
//
//	afisareHeap(heap);
//	return 0;
//}