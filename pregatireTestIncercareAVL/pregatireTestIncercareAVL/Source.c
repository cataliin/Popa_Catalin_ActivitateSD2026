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
	Masina m;
	Nod* stanga;
	Nod* dreapta;
};

Masina citireMasinaDinFisier(FILE* f) {
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
	m.model = malloc(strlen(aux) + 1);
	strcpy(m.model, aux);

	aux = strtok(NULL, sep);
	m.numeSofer = malloc(strlen(aux) + 1);
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

int calcInaltime(Nod* root) {
	if (root) {
		return 1 +max(calcInaltime(root->stanga), calcInaltime(root->dreapta));
	}
	return 0;
}

int calcGrad(Nod* root) {
	if (root) {
		return calcInaltime(root->stanga) - calcInaltime(root->dreapta);
	}
	return 0;
}

void rotireStanga(Nod** root) {
	Nod* aux = (*root)->dreapta;
	(*root)->dreapta = aux->stanga;
	aux->stanga = (*root);
	(*root) = aux;
}
void rotireDreapta(Nod** root) {
	Nod* aux = (*root)->stanga;
	(*root)->stanga = aux->dreapta;
	aux->dreapta = (*root);
	(*root) = aux;
}

void adaugaInArbore(Nod** root, Masina m) {
	if (*root)
	{
		if ((*root)->m.id > m.id) {
			adaugaInArbore(&(*root)->stanga, m);
		}
		else adaugaInArbore(&(*root)->dreapta, m);
	
	int grad = calcGrad(*root);
	if (grad == 2) {
		if (calcGrad((*root)->stanga) == -1)
			rotireStanga(&(*root)->stanga);
		rotireDreapta(root);
	}
	if (grad == -2) {
		if (calcGrad((*root)->dreapta) == 1)
			rotireDreapta(&(*root)->dreapta);
		rotireStanga(root);
		}
	}
	else {
		Nod* nou = malloc(sizeof(Nod));
		nou->dreapta = NULL;
		nou->stanga = NULL;
		nou->m = m;
		(*root) = nou;
	}
}
Nod* citireDinFis(const char* numeFis) {
	FILE* f = fopen(numeFis, "r");
	Nod* root = NULL;
	while (!feof(f)) {
		adaugaInArbore(&root, citireMasinaDinFisier(f));
	}
	fclose(f);
	return root;
}

void afisareInOrdine(Nod* root) {
	if (root) {
		afisareInOrdine(root->stanga);
		afisareMasina(root->m);
		afisareInOrdine(root->dreapta);
	}
}

int main() {
	Nod* root = citireDinFis("masini.txt");
	afisareInOrdine(root);
	return 0;
}