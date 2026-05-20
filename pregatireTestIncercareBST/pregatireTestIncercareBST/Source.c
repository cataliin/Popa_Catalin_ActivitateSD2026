#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

struct Nod {
	Nod* stanga;
	Nod* dreapta;
	Masina m;
};

Masina citireMasinaFis(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	Masina m;
	char* aux;
	fgets(buffer, 100, f);
	aux = strtok(buffer, sep);
	m.id = atoi(aux);
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m.model = malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(m.model, aux);
	aux = strtok(NULL, sep);
	m.numeSofer = malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(m.numeSofer, aux);
	m.serie = *strtok(NULL, sep);
	return m;

}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void adaugaInArbore(Nod** root, Masina m) {
	if (*root == NULL) {
		Nod* nou = malloc(sizeof(Nod));
		nou->stanga = NULL;
		nou->dreapta = NULL;
		nou->m = m;
		*root = nou;
	}
	else {
		if ((*root)->m.id > m.id) {
			adaugaInArbore(&(*root)->stanga, m);
		}
		else adaugaInArbore(&(*root)->dreapta, m);
	}
}

void afisareMasinInOrdine(Nod* root) {
	if (root) {
		afisareMasinInOrdine(root->stanga);
		afisareMasina(root->m);
		afisareMasinInOrdine(root->dreapta);
	}
}

Nod* citireMasiniFis(const char* numeFis) {
	FILE* f = fopen(numeFis, "r");
	Nod* root = NULL;
	while (!feof(f)) {
		adaugaInArbore(&root, citireMasinaFis(f));
	}
	fclose(f);

	return root;
}

int nrNoduri(Nod* root) {
	if (root) {
		Nod* stanga = root->stanga;
		Nod* dreapta = root->dreapta;
		return 1 + nrNoduri(stanga) + nrNoduri(dreapta);
	}
	return 0;
}

int main() {
	Nod* arb = citireMasiniFis("masini.txt");
	afisareMasinInOrdine(arb);
	printf("\n\n\n\n\n\n%d", nrNoduri(arb));
	return 0;
}