#include <stdlib.h>
#include <stdio.h>
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
    Nod* next;
};

struct HashTable {
	int dim;
	Nod** tabel;
};
typedef struct HashTable HashTable;

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

HashTable initHash(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.tabel = malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; ++i) {
		ht.tabel[i] = NULL;
	}
	return ht;
}

int fctHash(int dim, char* model) {
	int a = strlen(model);
	return (a * 67) % dim;
}

void adaugaMasinaInLista(Nod** head, Masina m) {
	Nod* nou = malloc(sizeof(Nod));
	nou->masina = m;
	nou->next = NULL;
	if (*head == NULL) {
		*head = nou;
		return;
	}
	Nod* aux = *head;
	while (aux->next != NULL) {
		aux = aux->next;
	}
	aux->next = nou;
}

void adaugaMasinaInTabel(HashTable ht, Masina m) {
	int poz = fctHash(ht.dim, m.model);
	if (ht.tabel[poz] != NULL) {
		adaugaMasinaInLista(&ht.tabel[poz], m);
	}
	else {
		ht.tabel[poz] = malloc(sizeof(Nod));
		ht.tabel[poz]->masina = m;
		ht.tabel[poz]->next = NULL;
	}
}

void afisareTabel(HashTable ht) {
	for (int i = 0; i < ht.dim; ++i) {
		if (ht.tabel[i]) {
			Nod* head = ht.tabel[i];
			while (head != NULL) {
				afisareMasina(head->masina);
				head = head->next;
			}
		}
	}
}

void dezaloc(HashTable* ht) {
	for (int i = 0; i < ht->dim; ++i) {
		if (ht->tabel[i]) {
			Nod* head = ht->tabel[i];
			Nod* next= NULL;
			while (head) {
				next = head->next;
				free(head->masina.model);
				free(head->masina.numeSofer);
				free(head);
				head = next;
			}
		}
	}
	free(ht->tabel);
	ht->dim = 0;
	ht->tabel = NULL;
}

int main() {
	HashTable ht = initHash(10);
	Masina m1;
	m1.id = 1;
	m1.model = _strdup("Papa");
	m1.numeSofer = _strdup("Regele");
	m1.nrUsi = 2;
	m1.pret = 50.5;
	m1.serie ='A';
	//adaugaMasinaInTabel(ht, m1);
	m1.pret = 80;
	adaugaMasinaInTabel(ht, m1);
	dezaloc(&ht);
	afisareTabel(ht);
	return 0;
}