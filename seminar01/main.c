#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct Joc {
	int id;
	int nrJucatori;
	char* denumire;
	float pret;
	char rating;
};

struct Joc initializare(int _id, int _nrMin, char* _denumire, float _pret, char _rating) {
	struct Joc s;
	s.id = 1;
	s.nrJucatori = _nrMin;
	s.denumire = malloc(strlen(_denumire)*(sizeof(char)+1));
	strcpy(s.denumire, _denumire);
	s.pret = _pret;
	s.rating = _rating;
	return s;
}

void afisare(struct Joc j) {
	printf("Nume : %s\n", j.denumire);
	printf("id : %d\n", j.id);
	printf("numar minim jucatori : %d\n", j.nrJucatori);
	printf("rating : %c\n", j.rating);
	printf("pret : %5.2f\n", j.pret);
}

float calcPretIndividual(struct Joc* s) {
	return (*s).pret/(*s).nrJucatori;
}

void modificaDenumire(struct Joc* s, char* _den) {
	if ((*s).denumire != NULL)
		free((*s).denumire);
	(*s).denumire = malloc((strlen(_den)+1) * sizeof(char));
	strcpy((*s).denumire, _den);
}

void dezalocare(struct Joc *s) {
	if (s->denumire != NULL) {
		free(s->denumire);
	}
}

int main() {
	struct Joc s;
	s = initializare(1,2, "Monopoly", 120, 'A');
	afisare(s);
	modificaDenumire(&s, "Secret Hitler");
	printf("\n\n\n");
	afisare(s);
	printf("\n\n");
	printf("%5.2f", calcPretIndividual(&s));
	int nrJoc = 3;
	struct Joc* jocuri;
	jocuri = malloc(sizeof(struct Joc) * nrJoc);
	jocuri[0] = s;
	jocuri[1] = initializare(2,5,"Saboteur",150,'B');
	jocuri[2] = initializare(3,6,"Catan", 200, 'C');
	printf("\n\n");
	// -> - dereferentiere + accesare
	// [] - deplasare + dereferentiere


	afisare(*(jocuri+2));
	free(jocuri);
	// for (int i = 0;i<nrJoc;++i) {
	// 	dezalocare(&jocuri[i]);
	// }
	dezalocare(&s);
	return 0;
}