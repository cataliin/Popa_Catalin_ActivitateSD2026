#include <stdio.h>
#include <stdlib.h>

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

void pushStack(Nod** stack, Masina masina) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masina;
	nou->next = *stack;
	*stack = nou;
}

Masina popStack(Nod** stack) {
	Masina masina;
	masina.id = -1;
	if (*stack == NULL)
		return masina;
	Nod* aux = *stack;
	masina = aux->info;
	(*stack) = (*stack)->next;
	free(aux);
	return masina;
}

int main() {


	return 0;
}