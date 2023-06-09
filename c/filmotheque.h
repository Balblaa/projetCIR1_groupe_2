#ifndef C_FILMOTHEQUE_H
#define C_FILMOTHEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Realisateur.h"
#define MAXLENGTH 100

struct Filmotheque{
    int maxFilm;
    char realisateurProductif[MAXLENGTH];
    struct Realisateur* r;
    int plusLongFilm;
};

//operation de création
struct Filmotheque* createemptyFilmotheque();

//opération d'insertion des éléments de la base de donnée.
struct Filmotheque* buildFilmothequeFromDico(char* nomfichier);

// Renvoie le nombre de film du réalisateur ayant le plus de film
int getMaxFilm(struct Filmotheque* ft);

// Renvoie la durée du plus long film
void getPlusLongFilm(struct Filmotheque* ft);

// Renvoie le nom du réalisateur avec le plus de film
void getRealisateurProductif(struct Filmotheque* ft);

// True si la filmothèque est vide Fasle sinon
bool isFilmothequeEmpty(struct Filmotheque* ft);

//
bool insertRealisateur(struct Filmotheque* ft,struct realisateur* r);

//affiche la structure
void printFilmotheque(struct Filmotheque* ft);

// True si un réalisateur existe
bool isAuthorExist(struct Filmotheque* ft,char* author);

//supprimer la structure
void deleteFilmothque(struct Filmotheque* ft);

#endif //C_FILMOTHEQUE_H
