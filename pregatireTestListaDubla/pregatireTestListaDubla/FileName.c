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

struct Nod {
	Masina info;
	Nod* next;
	Nod* prev;
};

typedef struct Nod Nod;

struct ListaDubla {
	Nod* head;
	Nod* tail;
};

typedef struct ListaDubla ListaDubla;

void adaugaLaSf(ListaDubla* ld, Masina masina) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masina;
	nou->next = NULL;
	nou->prev = ld->tail;
	if (ld->tail) {
		ld->tail->next = nou;
	}
	else ld->head = nou;
	ld->tail = nou;
}

void adaugaLaInceput(ListaDubla* ld, Masina masina) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masina;
	nou->prev = NULL;
	nou->next = ld->head;
	if (ld->head) {
		ld->head->prev = nou;
	}
	else ld->tail = nou;
	ld->head = nou;
}

void stergeMasinDupaId(ListaDubla* ld, int id) {
	if (ld->head && ld->head->info.id == id) {
		free(ld->head->info.model);
		free(ld->head->info.numeSofer);
		ld->head = ld->head->next;
		if (ld->head)
			free(ld->head->prev);
		else {
			free(ld->tail);
			ld->tail = NULL;
		}
	}
	Nod* p = ld->head;
	while (p && p->info.id != id)
		p = p->next;

	if (p) {
		if (p->prev) {
			p->prev->next = p->next;
		}
		if (p->next) {
			p->next->prev = p->prev;
		}
		else {
			p->prev->next = NULL;
			ld->tail = p->prev;
		}
		free(p->info.numeSofer);
		free(p->info.model);
		free(p);
	}
}

float calculeazaPretMediu(ListaDubla ld) {
	float pret = 0.0f;
	int cnt = 0;
	while (ld.head != NULL) {
		pret += ld.head->info.pret;
		cnt++;
		ld.head = ld.head->next;
	}
	return pret / cnt;
}

char* getNumeSoferMasinaScumpa(ListaDubla ld) {
	Nod* nodMasinaScumpa = NULL;
	int maxx = -1;
	while (ld.head != NULL) {
		if (ld.head->info.pret > maxx)
		{
			maxx = ld.head->info.pret;
			nodMasinaScumpa = ld.head;
		}
		ld.head = ld.head->next;
	}
	return nodMasinaScumpa->info.numeSofer;
}

int main() {


	return 0;
}