#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ranges>

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
	Nod* stanga;
	Nod* dreapta;
	Masina masina;
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
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
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


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
	if ((*radacina) == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->masina = masinaNoua;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		(*radacina) = nou;
		return;
	}

	if (masinaNoua.id < (*radacina)->masina.id) {
		adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua);
	}
	else {
		adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua);
	}


}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(f)) {
		adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(f));
	}
	fclose(f);
	return radacina;
}

void afisareMasiniDinArbore(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere

	if (radacina) {
		afisareMasiniDinArbore(radacina->stanga);
		afisareMasina(radacina->masina);
		afisareMasiniDinArbore(radacina->dreapta);
	}
}

void afisarePostordine(Nod* radacina) {
	if (radacina) {
		afisarePostordine(radacina->stanga);
		afisarePostordine(radacina->dreapta);
		afisareMasina(radacina->masina);

	}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	if (*radacina) {
		dezalocareArboreDeMasini(&(*radacina)->stanga);
		dezalocareArboreDeMasini(&(*radacina)->dreapta);

		free((*radacina)->masina.model);
		free((*radacina)->masina.numeSofer);
		free(*radacina);

		*radacina = NULL;
	}

}

Masina getMasinaByID(Nod* radacina, int id) {
	Masina m;
	if (radacina) {
		if (radacina->masina.id == id) {
			m = radacina->masina;
			m.model = (char*)malloc(strlen(radacina->masina.model) + 1);
			strcpy(m.model, radacina->masina.model);

			m.numeSofer = (char*)malloc(strlen(radacina->masina.numeSofer) + 1);
			strcpy(m.numeSofer, radacina->masina.numeSofer);
		}
		else {
			if (radacina->masina.id <= id) {
				m = getMasinaByID(radacina->dreapta, id);
			}
			else {
				m = getMasinaByID(radacina->stanga, id);
			}
		}
	}
	else m.id = -1;
	return m;
}

int determinaNumarNoduri(Nod* radacina) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	if (radacina) {
		int nrNoduriStanga = determinaNumarNoduri(radacina->stanga);
		int nrNoduriDreapta = determinaNumarNoduri(radacina->dreapta);
		return 1 + nrNoduriDreapta + nrNoduriStanga;
	}

	return 0;
}

int calculeazaInaltimeArbore(Nod* radacina) {
	//calculeaza inaltimea arborelui care este data de
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	if (radacina == NULL) return -1;
	else {
		return 1 + std::ranges::max(calculeazaInaltimeArbore(radacina->stanga), calculeazaInaltimeArbore(radacina->dreapta));
	}
}

float calculeazaPretTotal(Nod* radacina) {
	//calculeaza pretul tuturor masinilor din arbore.
	if (radacina == NULL)
		return 0;
	else {
		float st = calculeazaPretTotal(radacina->stanga);
		float dr = calculeazaPretTotal(radacina->dreapta);
		return radacina->masina.pret + st + dr;
	}
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* arbore = (Nod*)citireArboreDeMasiniDinFisier("/Users/catalin/Documents/Facultate/SDD/seminar10/masini.txt");
	afisareMasiniDinArbore(arbore);
	afisareMasina(getMasinaByID(arbore, 5));

	printf("\n\n\n%d", determinaNumarNoduri(arbore));

	printf("%d", calculeazaInaltimeArbore(arbore));
	return 0;
}