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
	Masina masina;
	Nod* stanga;
	Nod* dreapta;
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

void adaugaMasinaInArbore(Nod** radacina, Masina masina) {
	if (*radacina == NULL) {
		Nod* nou = malloc(sizeof(Nod));
		nou->dreapta = NULL;
		nou->stanga = NULL;
		nou->masina = masina;
		*radacina = nou;
	}
	else {
		if ((*radacina)->masina.id > masina.id) {
			adaugaMasinaInArbore(&(*radacina)->stanga, masina);
		}
		else adaugaMasinaInArbore(&(*radacina)->dreapta, masina);
	}
}

void afisareMasinaInOrdine(Nod* radacina) {
	if (radacina) {
		afisareMasinaInOrdine(radacina->stanga);
		afisareMasina(radacina->masina);
		afisareMasinaInOrdine(radacina->dreapta);
	}
}

Nod* citireArboreDinFis(const char* numeFis) {
	FILE* f = fopen(numeFis, "r");
	Nod* radacina = NULL;
	while (!feof(f)) {
		adaugaMasinaInArbore(&radacina, citireMasinaFis(f));
	}
	fclose(f);
	return radacina;
}

int nrNoduri(Nod* radacina) {
	if (radacina) {
		Nod* stanga = radacina->stanga;
		Nod* dreapta = radacina->dreapta;
		return 1 + nrNoduri(stanga) + nrNoduri(dreapta);
	}
	return 0;
}

int main() {
	Nod* arbore = citireArboreDinFis("masini.txt");
	afisareMasinaInOrdine(arbore);
	printf("\n\n\n\n\n");
	printf("%d", nrNoduri(arbore));
	return 0;
}