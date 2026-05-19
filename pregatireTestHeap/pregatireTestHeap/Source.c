#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Masina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct Masina Masina;

struct Heap {
	int lungime;
	Masina* vector;
	int nrMasini;
};

typedef struct Heap Heap;
Masina citireMasinaFisier(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);

	m1.model = malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);

	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);
	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrMasini = 0;
	heap.vector = malloc(sizeof(Masina) * lungime);

	return heap;
}

void filtreazaHeap(Heap heap, int pozNod) {
	int pozSt = 2 * pozNod + 1;
	int pozDr = 2 * pozNod + 2;
	int pozMax = pozNod;
	
	if (pozSt < heap.nrMasini && heap.vector[pozMax].pret > heap.vector[pozSt].pret) {
		pozMax = pozSt;
	}
	if (pozDr < heap.nrMasini && heap.vector[pozMax].pret > heap.vector[pozDr].pret)
	{
		pozMax = pozDr;
	}
	if (pozMax != pozNod) {
		Masina aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozNod];
		heap.vector[pozNod] = aux;
		if (pozMax <= (heap.nrMasini - 2) / 2) {
			filtreazaHeap(heap, pozMax);
		}

	}
}

Heap citireMasiniHeap(const char* numeFis) {
	FILE* f = fopen(numeFis, "r");
	Heap heap = initializareHeap(10);
	while (!feof(f)) {
		heap.vector[heap.nrMasini++] = citireMasinaFisier(f);
	}
	fclose(f);
	for (int i = (heap.nrMasini - 2) / 2; i >= 0; --i) {
		filtreazaHeap(heap, i);
	}
	return heap;
}
void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrMasini; ++i) {
		afisareMasina(heap.vector[i]);
	}
}

Masina extrageMasina(Heap* heap) {
	Masina aux;
	if (heap->nrMasini > 0) {
		aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrMasini - 1];
		heap->vector[heap->nrMasini - 1] = aux;
		heap->nrMasini--;
		for (int i = (heap->nrMasini - 2) / 2; i >= 0; --i)
			filtreazaHeap(*heap, i);
	}
	return aux;
}

void dezalocHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; ++i) {
		free(heap->vector[i].model);
		free(heap->vector[i].numeSofer);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->lungime = 0;
	heap->nrMasini = 0;
}

int main() {
	Heap heap = citireMasiniHeap("masini.txt");
	afisareHeap(heap);
	printf("\n\n\n\n\n\n");
	extrageMasina(&heap);
	extrageMasina(&heap);
	extrageMasina(&heap);
	extrageMasina(&heap);
	extrageMasina(&heap);
	extrageMasina(&heap);
	extrageMasina(&heap);
	extrageMasina(&heap);
	extrageMasina(&heap);
	extrageMasina(&heap);
	for (int i = heap.nrMasini; i < heap.lungime; ++i) {
		afisareMasina(heap.vector[i]);
	}
	dezalocHeap(&heap);
	return 0;
}