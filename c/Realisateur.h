#ifndef C_BANKREALISATEUR_H
#define C_BANKREALISATEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "film.h"

#define NBLETTRE 27

struct Realisateur{
    struct Realisateur* lettre[NBLETTRE];
    bool isRealisateur;
    struct Film* film;
};

//  Créer le premier noeud de réalisateur
struct Realisateur* createEmptyRealisateur();

// Renvoie le la liste de film d'un realisateur
struct Realisateur* findRealisateur(struct Realisateur* r, char* realisateur);

// rajoute un film au réalisateur donné
void insertFilm(struct Realisateur* r, struct Film* f);

// suprime un film avec son titre et son auteur
void deleteFilm(struct Realisateur* r, char* realisateur, char* title[MAXTITLE]);

// Renvoie si la cellule est un réalisateur ou non
bool isRealisateur(struct Realisateur* r);

// Vérifie qu'un réalisateur existe
bool isRealisateurExist(struct Realisateur* r,char* author);

// suprime tous les réalisateurs
void deleteRealisateur(struct Realisateur* r);


#endif //C_BANKREALISATEUR_H
