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
struct Filmotheque* createemptyFilmotheque(struct Filmotheque* ft);
bool isFilmothequeEmpty(struct Filmotheque* ft);
//opération d'insertion des éléments de la base de donnée.
bool insertRealisateur(struct Filmotheque* ft,struct realisateur* r);
//affiche la structure
void printFilmotheque(struct Filmotheque* ft);
//opérations d'accès aux éléments de la structure
int getMaxFilm(struct Filmotheque* ft);
void getPlusLongFilm(struct Filmotheque* ft);
void getRealisateurProductif(struct Filmotheque* ft);
bool isAuthorExist(struct Filmotheque* ft,char* author);
//supprimer la structure banane
void deleteFilmothque(struct Filmotheque* ft);
#endif //C_FILMOTHEQUE_H
