#ifndef C_BANKREALISATEUR_H
#define C_BANKREALISATEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "film.h"

struct Realisateur{
    struct Realisateur* alphabetSuivant[26];
    bool isRealisateur;
    struct Film* f;
};

//  Créer le premier noeud
struct realisateur* createEmptyRealisateur();

// rajoute un film au réalisateur donné
void insertFilm(struct Realisateur* r, struct Film* f);

// suprime un film avec son titre et son auteur
void deleteFilm(struct Realisateur* r, char* realisateur, char* title[MAXTITLE]);

// Renvoie si la cellule est un réalisateur ou non
bool isRealisateur(struct Realisateur* r);

// Renvoie le la liste de film d'un realisateur
struct Realisateur* findRealisateur(struct Realisateur* r, char* realisateur);

// Vérifie qu'un réalisateur existe
bool isRealisateurExist(struct Realisateur* r,char* author);

// suprime tous les réalisateurs
void deleteRealisateur(struct Realisateur* r);


#endif //C_BANKREALISATEUR_H
