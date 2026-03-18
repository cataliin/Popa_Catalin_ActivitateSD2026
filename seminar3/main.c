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

void afisareMasina(Masina masina) {
	printf("\nId Masina: %d", masina.id);
	printf("\nNumar Usi: %d", masina.nrUsi);
	printf("\nPret Masina: %.2f", masina.pret);
	printf("\nModel Masina: %s", masina.model);
	printf("\nSofer Masina: %s", masina.numeSofer);
	printf("\nSerie Masina: %c\n", masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	for (int i = 0; i < nrMasini; ++i)
		afisareMasina(masini[i]);
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	//adauga in vectorul primit o noua masina pe care o primim ca parametru
	//ATENTIE - se modifica numarul de masini din vector;
	(*nrMasini)++;
	Masina* temp = (Masina*)malloc(sizeof(Masina) * (*nrMasini));
	for (int i = 0; i < *nrMasini - 1; ++i)
		temp[i] = (*masini)[i];

	temp[(*nrMasini) - 1] = masinaNoua;

	free(*masini);
	*masini = temp;
}

Masina citireMasinaFisier(FILE* file) {
	char linie[50];
	fgets(linie, 50, file);
	char delim[3] =",\n";
	Masina m;
	m.id = atoi(strtok(linie, delim));
	m.nrUsi = atoi(strtok(NULL, delim));
	m.pret = atof(strtok(NULL, delim));
	char* modelMasina = strtok(NULL, delim);
	m.model = (char*)malloc((strlen(modelMasina)+1)*sizeof(char));
	strcpy(m.model,modelMasina);

	char* numeSofer = strtok(NULL, delim);
	m.numeSofer = (char*)malloc((strlen(numeSofer)+1)*sizeof(char));
	strcpy(m.numeSofer,numeSofer);

	char* serie = strtok(NULL, delim);
	m.serie = serie[0];

	return m;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* fisier = fopen(numeFisier,"r");
	(*nrMasiniCitite) = 0;
	Masina* masini = NULL;
	int k = 0;
	while (!feof(fisier)) {
		Masina masina = citireMasinaFisier(fisier);
		adaugaMasinaInVector(&masini, nrMasiniCitite,masina);
	}
	fclose(fisier);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
}

int main() {
	// FILE* file = fopen("/Users/catalin/Documents/SDD/seminar3/masini.txt", "r");
	// if (file == NULL) {
	// 	printf("Error: Could not open masini.txt. Check the file path!");
	// 	return 1;
	// }
	// Masina masina = citireMasinaFisier(file);
	// afisareMasina(masina);
	// fclose(file);
	Masina *masini;
	int nr = 0;
	masini = citireVectorMasiniFisier("/Users/catalin/Documents/SDD/seminar3/masini.txt",&nr);
	afisareVectorMasini(masini, nr);
	return 0;
}