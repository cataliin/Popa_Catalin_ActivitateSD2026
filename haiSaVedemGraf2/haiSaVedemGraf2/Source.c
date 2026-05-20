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
	NodP* next;
	NodS* vecini;
	Masina info;
};

struct NodS {
	NodP* info;
	NodS* next;
};

void inserareListaPrincipala(NodP** lista, Masina m) {
	NodP* nou = malloc(sizeof(NodP));
	nou->next = NULL;
	nou->info = m;
	nou->vecini = NULL;

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
		if (lista->info.id == id) {
			return lista;
		}
		lista = lista->next;
	}
	return NULL;
}


void inserareMuchie(NodP* lista, int idStart, int idSfarsit) {
	NodP* start = cautaNodDupaID(lista, idStart);
	NodP* sfarsit = cautaNodDupaID(lista, idSfarsit);

	if (start && sfarsit) {
		inserareListaSecundara(&start->vecini, sfarsit);
		inserareListaSecundara(&sfarsit->vecini, start);
	}
}

NodP* citireMasiniDinFisier(const char* numeFis) {
	NodP* graf = NULL;
	FILE* f = fopen(numeFis, "r");
	while (!feof(f)) {
		inserareListaPrincipala(&graf, citireMasinaDinFisier(f));
	}
	fclose(f);
	return graf;
}

void citireMuchiiDinFisier(const char* numeFis, NodP* lista) {
	FILE* f = fopen(numeFis, "r");
	while (!feof(f)) {
		int idStart = 0;
		int idStop = 0;
		fscanf(f, "%d %d", &idStop, &idStart);
		inserareMuchie(lista, idStart, idStop);
	}
}

void afisareMasini(NodP* lista) {
	while (lista) {
		afisareMasina(lista->info);
		lista = lista->next;
	}
}

void afisareVecini(NodP* lista, int id) {
	NodP* nod = cautaNodDupaID(lista, id);

	NodS* aux = nod->vecini;
	while (aux) {
		afisareMasina(aux->info->info);
		aux = aux->next;
	}
}

int main() {
	NodP* graf = citireMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier("muchii.txt", graf);
	afisareVecini(graf, 4);
	return 0;
}