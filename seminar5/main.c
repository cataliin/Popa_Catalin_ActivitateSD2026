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
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Nod {
	Masina info;
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* head;
	Nod* tail;
};

//creare structura pentru un nod dintr-o lista dublu inlantuita

//creare structura pentru Lista Dubla

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

void afisareListaMasini(ListaDubla lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.head;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}

void afisareInversaListaMasini(ListaDubla lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.tail;
	while (p) {
		afisareMasina(p->info);
		p = p->prev;
	}
}

void adaugaMasinaInLista(ListaDubla* ld, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	nou->prev = ld->tail;
	if (ld->tail){
		ld->tail->next = nou;
	}
	else {
		ld->head = nou;
	}
	ld->tail = nou;
}

void adaugaLaInceputInLista(ListaDubla* ld, Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = ld->head;
	nou->prev = NULL;
	if (ld->head){
		ld->head->prev = nou;
	}
	else {
		ld->tail = nou;
	}
	ld->head = nou;
}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	ListaDubla ld;
	if (f) {
		ld.head = ld.tail = NULL;
		while (!feof(f)) {
			adaugaMasinaInLista(&ld, citireMasinaDinFisier(f));
		}
	}
	fclose(f);
	return ld;
}

void dezalocareLDMasini(ListaDubla* ld) {
	while (ld->head && ld->head->next) {
		free(ld->head->info.numeSofer);
		free(ld->head->info.model);
 		ld->head = ld->head->next;
		free(ld->head->prev);
	}
	if (ld->head) {
		free(ld->head->info.numeSofer);
		free(ld->head->info.model);
		free(ld->head);
	}
	ld->head=ld->tail=NULL;
}

float calculeazaPretMediu(ListaDubla ld) {
	//calculeaza pretul mediu al masinilor din lista.
	float pret = 0.0f;
	int cnt = 0;
	while (ld.head != NULL) {
		pret += ld.head->info.pret;
		cnt++;
		ld.head = ld.head->next;
	}
	return pret/cnt;
}

void stergeMasinaDupaID(ListaDubla* ld, int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	if (ld->head && ld->head->info.id == id) {
		free(ld->head->info.numeSofer);
		free(ld->head->info.model);
		ld->head = ld->head->next;
		if (ld->head) {
			free(ld->head->prev);
		}
		else {
			free(ld->tail);
			ld->tail = NULL;
	}
	}
	Nod* p = ld->head;
	while (p && p->info.id!=id) {
		p = p->next;
	}
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

char* getNumeSoferMasinaScumpa(ListaDubla ld) {
	//cauta masina cea mai scumpa si
	//returneaza numele soferului acestei maasini.
	// char* nume = (char*)malloc(sizeof(char)* 20);
	Nod* nodMasinaScumpa = NULL;
	int maxx = -1;
	while (ld.head != NULL) {
		if (ld.head->info.pret > maxx) {
			maxx = ld.head->info.pret;
			nodMasinaScumpa = ld.head;
		}
		ld.head = ld.head->next;
	}
	return nodMasinaScumpa->info.numeSofer;
}

int main() {
	ListaDubla lista = citireLDMasiniDinFisier("/Users/catalin/Documents/Facultate/SDD/seminar5/masini.txt");
	afisareListaMasini(lista);
	// printf("\n\n%f", calculeazaPretMediu(lista));
	// printf("\n\n%s", getNumeSoferMasinaScumpa(lista));
	stergeMasinaDupaID(&lista,10);
	printf("\n\n");
	afisareListaMasini(lista);
	return 0;
}