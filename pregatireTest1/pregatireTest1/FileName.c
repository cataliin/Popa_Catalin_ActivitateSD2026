#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ListaDubla ListaDubla;

typedef struct Nod Nod;

typedef struct Moneda Moneda;

struct Moneda {
	char* tara;
	int val;
	float greutate;
};



struct Nod {
	Moneda moneda;
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* head;
	Nod* tail;
};



void afisareMoneda(Moneda m) {
	printf("%s\n", m.tara);
	printf("%d\n", m.val);
	printf("%f\n\n", m.greutate);
}

Moneda citireMonedaDinFisier(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	char* aux;
	Moneda m;
	aux = strtok(buffer, sep);
	m.tara = malloc(strlen(aux) + 1);
	strcpy(m.tara, aux);
	aux = strtok(NULL, sep);
	m.val = atoi(aux);
	aux = strtok(NULL, sep);
	m.greutate = atof(aux);

	return m;
}

void push(ListaDubla* q, Moneda m) {
	Nod* nou = malloc(sizeof(Nod));
	nou->next = NULL;
	nou->moneda = m;
	nou->prev = q->tail;
	if (q->tail) {
		q->tail->next = nou;
	}
	else {
		q->head = nou;
	}
	q->tail = nou;
}

void citireDinFisier(char* numeFis, ListaDubla* ld) {
	FILE* f = fopen(numeFis, "r");
	Moneda m;
	while (!feof(f)) {
		m = citireMonedaDinFisier(f);
		push(ld, m);
	}
	fclose(f);
}



Moneda pop(ListaDubla* q) {
	Moneda m;
	if (q->head) {
		m.tara = malloc(strlen(q->head->moneda.tara) + 1);
		strcpy(m.tara, q->head->moneda.tara);
		m.greutate = q->head->moneda.greutate;
		m.val = q->head->moneda.val;

		q->head = q->head->next;
		free(q->head->prev);
	}
	return m;
}

void afisareTOT(ListaDubla ld) {
	while (ld.head != NULL) {
		afisareMoneda(ld.head->moneda);
		ld.head = ld.head->next;
	}
}

int main() {
	ListaDubla ld;
	ld.head = ld.tail = NULL;
	citireDinFisier("monezi.txt", &ld);
	afisareTOT(ld);
	pop(&ld);
	afisareTOT(ld);
	return 0;
}