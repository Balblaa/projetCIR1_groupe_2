#ifndef C_FILMOTHEQUE_H
#define C_FILMOTHEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "realisateur.h"

struct Filmotheque{
    int maxFilm;
    char realisateurProductif[MAXAUTHOR];
    struct Realisateur* r;
    int plusLongFilm;
};

//operation de création
struct Filmotheque* createFilmotheque();

// Renvoie le nombre de film du réalisateur ayant le plus de film
int getMaxFilm(struct Filmotheque* ft);

// Renvoie la durée du plus long film
void getPlusLongFilm(struct Filmotheque* ft);

// Renvoie le nom du réalisateur avec le plus de film
void getRealisateurProductif(struct Filmotheque* ft);

// True si la filmothèque est vide False sinon
bool isFilmothequeEmpty(struct Filmotheque* ft);

// Permet de rajouter un Film
void addNewFilm(struct Filmotheque* ft,struct Film* f);

//affiche la structure
void printFilmotheque(struct Filmotheque* ft);

// True si un réalisateur existe
bool isAuthorExist(struct Filmotheque* ft,char* author);

//supprimer la structure
void deleteFilmothque(struct Filmotheque* ft);

#endif //C_FILMOTHEQUE_H
