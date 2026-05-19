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

//void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
//	
//
//	if (*radacina == NULL) {
//		Nod* nou = malloc(sizeof(Nod));
//		nou->dreapta = NULL;
//		nou->stanga = NULL;
//		nou->masina = masinaNoua;
//		*radacina = nou;
//	}
//	else {
//		if ((*radacina)->masina.id > masinaNoua.id) {
//			adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua);
//		}
//		else {
//			adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua);
//		}
//	}
//}


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if (*radacina == NULL) {
		Nod* nou = malloc(sizeof(Nod));
		nou->stanga = NULL;
		nou->dreapta = NULL;
		nou->masina = masinaNoua;
		*radacina = nou;
	}
	else {
		if ((*radacina)->masina.id > masinaNoua.id) {
			adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua);
		}
		else adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua);
	}

}

Nod* citireArboreDinFisier(const char* numeFis) {
	FILE* f = fopen(numeFis, "r");
	Nod* radacina = NULL;
	while (!feof(f)) {
		adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(f));
	}
	fclose(f);

	return radacina;
}

void afisareInOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareInOrdine(radacina->stanga);
		afisareMasina(radacina->masina);
		afisareInOrdine(radacina->dreapta);
	}
}

Masina getMasinaDupaID(Nod* radacina, int id) {
	Masina m;
	if (radacina == NULL) {
		m.id = -1;
		return m;
	}

	if (radacina->masina.id == id) {
		m = radacina->masina;

		m.model = malloc((strlen(radacina->masina.model) + 1) * sizeof(char));
		strcpy(m.model, radacina->masina.model);

		m.numeSofer = malloc((strlen(radacina->masina.numeSofer) + 1) * sizeof(char));
		strcpy(m.numeSofer, radacina->masina.numeSofer);

		return m;
	}

	if (radacina->masina.id > id) {
		return getMasinaDupaID(radacina->stanga, id);
	}
	else {
		return getMasinaDupaID(radacina->dreapta, id);
	}
	
}

void dezalocare(Nod** rad) {
	if (*rad != NULL) {
		Nod* stanga = (*rad)->stanga;
		Nod* dreapta = (*rad)->dreapta;

		free((*rad)->masina.model);
		free((*rad)->masina.numeSofer);

		free(*rad);
		*rad = NULL;

		dezalocare(&stanga);
		dezalocare(&dreapta);
	}
}

int main() {
	Nod* arbore = citireArboreDinFisier("masini.txt");
	afisareInOrdine(arbore);
	Masina m = getMasinaDupaID(arbore, 5);
	afisareMasina(m);
	return 0;
}
