#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
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

typedef struct NodP NodP;
typedef struct NodS NodS;

struct NodP {
	Masina masina;
	NodP* next;
	NodS* vecini;
};

struct NodS {
	NodP* info;
	NodS* next;
};

void inserareListaPrincipala(NodP** lista, Masina masina) {
	NodP* nou = malloc(sizeof(NodP));
	nou->next = NULL;
	nou->vecini = NULL;
	nou->masina = masina;

	if (*lista == NULL) {
		*lista = nou;
		return;
	}
	NodP* aux = *lista;
	while (aux->next) {
		aux = aux->next;
	}
	aux->next = nou;
}

void inserareListaSecundara(NodS** lista, NodP* vecin) {
	NodS* nou = malloc(sizeof(NodS));
	nou->next = NULL;
	nou->info = vecin;

	if (*lista == NULL) {
		*lista = nou;
		return;
	}

	NodS* aux = *lista;
	while (aux->next) {
		aux = aux->next;
	}
	aux->next = nou;
}

NodP* cautaNodDupaID(NodP* lista, int id) {
	while (lista) {
		if (lista->masina.id == id) {
			return lista;
		}
		lista = lista->next;
	}

	return NULL;
}

NodP* citireMasiniDinFiser(const char* numeFis) {
	NodP* graf = NULL;

	FILE* f = fopen(numeFis, "r");
	while (!feof(f)) {
		inserareListaPrincipala(&graf, citireMasinaDinFisier(f));
	}
	fclose(f);
	return graf;
}

void inserareMuchie(NodP* lista, int idStart, int idStop) {
	NodP* start = cautaNodDupaID(lista, idStart);
	NodP* stop = cautaNodDupaID(lista, idStop);
	if (start && stop) {
		inserareListaSecundara(&start->vecini, stop);
		inserareListaSecundara(&stop->vecini, start);
	}
}

void citireMuchiiDinFisier(NodP* lista, const char* numeFis) {
	FILE* f = fopen(numeFis, "r");

	while (!feof(f)) {
		int idStart = 0;
		int idStop = 0;
		fscanf(f, "%d %d", &idStart, &idStop);
		inserareMuchie(lista, idStart, idStop);
	}
	fclose(f);
}

void afisareVecini(NodP* graf, int id) {
	NodP* nod = cautaNodDupaID(graf, id);
	NodS* aux = nod->vecini;

	while (aux) {
		afisareMasina(aux->info->masina);
		aux = aux->next;
	}
}

int main() {
	NodP* graf = citireMasiniDinFiser("masini.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");
	afisareVecini(graf, 8);
	return 0;
}