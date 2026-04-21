#include <stdlib.h>
#include <stdio.h>

typedef struct Nod Nod;
typedef struct Queue Queue;

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
	Masina masina;
	Nod* next;
	Nod* prev;
};
struct Queue {
	Nod* start;
	Nod* end;
};

void enqueue(Queue* q, Masina m) {
	Nod* nou = malloc(sizeof(Nod));
	nou->masina = m;
	nou->next = q->start;
	nou->prev = NULL;
	if (q->start) {
		q->start->prev = nou;
	}
	else {
		q->end = nou;
	}
	q->start = nou;
}

Masina dequeue(Queue* q) {
	Masina m;
	if (q->start == NULL) {
		m.id = -1;
		return m;
	}

	m = q->end->masina;
	if (q->end == q->start) {
		free(q->start);
		q->start = q->end = NULL;
	}
	else {
		q->end = q->end->prev;
		free(q->end->next);
		q->end->next = NULL;
	}

	return m;
}


int main() {

	return 0;
}