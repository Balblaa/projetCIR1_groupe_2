#ifndef C_BANKREALISATEUR_H
#define C_BANKREALISATEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "film.h"

struct Realisateur{
    char alphabetSuivant[26];
    bool isAuthor;
    struct Film;
};
struct realisateur* createEmptyRealisateur();
bool isRealisateurEmpty(struct Realisateur* r);
bool insertFilm(struct Realisateur* r,struct Film* f);
bool isAuthor(struct Realisateur* r);
bool getIsAuthor(struct Realisateur* r);
bool isRealisateurExist(struct Realisateur* r,char* author);
void deleteRealisateur(struct Realisateur* r);
#endif //C_BANKREALISATEUR_H
