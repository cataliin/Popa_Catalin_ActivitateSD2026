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

//creare structura pentru un nod dintr-un arbore binar de cautare
typedef struct Nod Nod;
struct Nod {
	Masina masina;
	Nod* stanga;
	Nod* dreapta;
};


Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

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


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
	if (*radacina == NULL) {
		Nod* nou = malloc(sizeof(Nod));
		nou->dreapta = NULL;
		nou->stanga = NULL;
		nou->masina = masinaNoua;
		*radacina = nou;
	}
	else {
		if (masinaNoua.id < (*radacina)->masina.id) {
			adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua);
		}
		else {
			adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua);
		}
	}

}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(f)) {
		adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(f));
	}
	fclose(f);
	return radacina;
}

void afisareMasiniDinArboreInOrdine(Nod* radacina) {
	if (radacina) {
		afisareMasiniDinArboreInOrdine(radacina->stanga);
		afisareMasina(radacina->masina);
		afisareMasiniDinArboreInOrdine(radacina->dreapta);
	}
}

void afisareMasiniDinArborePreOrdine(Nod* radacina) {
	if (radacina) {
		afisareMasina(radacina->masina);
		afisareMasiniDinArborePreOrdine(radacina->stanga);
		afisareMasiniDinArborePreOrdine(radacina->dreapta);
	}
}

void afisareMasiniDinArborePostOrdine(Nod* radacina) {
	if (radacina) {
		afisareMasiniDinArborePostOrdine(radacina->stanga);
		afisareMasiniDinArborePostOrdine(radacina->dreapta);
		afisareMasina(radacina->masina);
	}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	if (*radacina) {
		Nod* stanga = (*radacina)->stanga;
		Nod* dreapta = (*radacina)->dreapta;

		free((*radacina)->masina.model);
		free((*radacina)->masina.numeSofer);
		free((*radacina));

		*radacina = NULL;
		dezalocareArboreDeMasini(&stanga);
		dezalocareArboreDeMasini(&dreapta);
	}
}

Masina getMasinaByID(Nod* radacina, int id) {
	Masina m;
	if (radacina == NULL) {
		m.id = -1;
		return m;
	}
	if (radacina->masina.id == id) {
		m = radacina->masina;
		m.model = malloc(strlen(radacina->masina.model + 1) * sizeof(char));
		strcpy(m.model, radacina->masina.model);
		m.numeSofer = malloc(strlen(radacina->masina.numeSofer + 1) * sizeof(char));
		strcpy(m.numeSofer, radacina->masina.numeSofer);

		return m;
	}

	if (radacina->masina.id > id) {
		return getMasinaByID(radacina->stanga, id);
	}
	else return getMasinaByID(radacina->dreapta, id);
}

int determinaNumarNoduri(Nod* radacina) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	if (radacina != NULL) {
		int nrStanga = determinaNumarNoduri(radacina->stanga);
		int nrDreapta = determinaNumarNoduri(radacina->dreapta);

		return 1 + nrStanga + nrDreapta;
	}

	return 0;
}

int calculeazaInaltimeArbore(/*arbore de masini*/) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	return 0;
}

float calculeazaPretTotal(/*arbore de masini*/) {
	//calculeaza pretul tuturor masinilor din arbore.
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt");
	afisareMasiniDinArboreInOrdine(arbore);
	Masina masina = getMasinaByID(arbore, 5);
	afisareMasina(masina);
	return 0;
}