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

//creare structura pentru un nod dintr-un arbore binar de cautare
struct NodArbore {
	Masina masina;
	struct Nod* stanga;
	struct Nod* dreapta;
};
typedef struct NodArbore Nod;

Masina citireMasinaDinFisier(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	char* aux;
	Masina m;
	aux = strtok(buffer, sep);
	m.id = atoi(aux);
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m.model = malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(m.model, aux);
	aux = strtok(NULL, sep);
	m.numeSofer= malloc((strlen(aux) + 1) * sizeof(char));
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

int calculeazaInaltimeArbore(Nod* root) {
	if (root) {
		return max(calculeazaInaltimeArbore(root->stanga), calculeazaInaltimeArbore(root->dreapta));
	}
}

int calcGradEchilibru(Nod* root) {
	if (root) {
		return calculeazaInaltimeArbore(root->stanga) - calculeazaInaltimeArbore(root->dreapta);
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

//void adaugaInArbore(Nod** root, Masina masina) {
//	if (*root) {
//		if (masina.id < (*root)->masina.id) {
//			adaugaInArbore(&(*root)->stanga, masina);
//		}
//		else adaugaInArbore(&(*root)->dreapta, masina);
//
//		int grad = calcGradEchilibru(*root);
//		if (grad == 2) {
//			if (calcGradEchilibru((*root)->stanga) == -1) {
//				rotireStanga(&(*root)->stanga);
//			}
//			rotireDreapta(root);
//		}
//
//		if (grad == -2) {
//			if (calcGradEchilibru((*root)->dreapta == 1))
//				rotireDreapta(&(*root)->dreapta);
//			rotireStanga(root);
//		}
//	}
//	else {
//		Nod* nou = malloc(sizeof(Nod));
//		nou->dreapta = NULL;
//		nou->stanga = NULL;
//		nou->masina = masina;
//
//		(*root) = nou;
//	}
//}

void adaugareInArbore(Nod** root, Masina masina) {
	if (*root) {
		if (masina.id < (*root)->masina.id) {
			adaugareInArbore(&(*root)->stanga, masina);
		}
		else adaugareInArbore(&(*root)->dreapta, masina);

		int grad = calcGradEchilibru(*root);
		if (grad == 2) {
			if (calcGradEchilibru((*root)->stanga ) == -1)
				rotireStanga(&(*root)->stanga);
			rotireDreapta(root);
		}
		if (grad == -2) {
			if (calcGradEchilibru((*root)->dreapta) == 1)
				rotireDreapta(&(*root)->dreapta);
			rotireStanga(root);
		}
	}
	else {
		Nod* nou = malloc(sizeof(Nod));
		nou->dreapta = NULL;
		nou->stanga = NULL;
		nou->masina = masina;

		(*root) = nou;
	}

}

void adaugareInArbore(Nod** root, Masina masina) {
	if (*root) {
		if (masina.id > (*root)->masina.id) {
			adaugareInArbore(&(*root)->dreapta, masina);
		}
		else adaugareInArbore(&(*root)->stanga, masina);
		int grad = calcGradEchilibru(*root);
		if (grad == 2) {
			if (calcGradEchilibru((*root)->stanga) == -1)
				rotireStanga(&(*root)->stanga);
			rotireDreapta(root);
		}
		if (grad == -2) {
			if (calcGradEchilibru((*root)->dreapta) == 1)
				rotireDreapta(&(*root)->dreapta);
			rotireStanga(root);
		}
	}
	else {
		Nod* nou = malloc(sizeof(Nod));
		nou->dreapta = NULL;
		nou->stanga = NULL;
		nou->masina = masina;
		*root = nou;
	}
}

Nod* citireDinFisier(const char* numeFis) {
	FILE* f = fopen(numeFis, "r");

	Nod* root = NULL;
	while (!feof(f)) {
		adaugareInArbore(&root, citireMasinaDinFisier(f));
	}
	fclose(f);
	return root;
}

void afisMasinaInOrdine(Nod* root) {
	if (root) {
		//SRD
		afisMasinaInOrdine(root->stanga);
		afisareMasina(root->masina);
		afisMasinaInOrdine(root->dreapta);
	}
}



int main() {


	return 0;
}