#include <stdio.h>

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
};

typedef struct Nod Nod;

void adaugaLaInceputDeLista(Nod* head, Masina masina) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masina;
	nou->next = head;
	head = nou;
}

void dezalocareListaMasini(Nod** lista) {
	Nod* head = *lista;
	Nod* next = NULL;

	while (head != NULL) {
		next = head->next;
		free(head->info.model);
		free(head->info.numeSofer);
		free(head);
		head = next;
	}

	*lista = NULL;
}

int main() {


	return 0;
}