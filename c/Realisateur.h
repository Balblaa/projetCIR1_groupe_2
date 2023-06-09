#ifndef C_BANKREALISATEUR_H
#define C_BANKREALISATEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "film.h"

// la 27 lettre est un '''
// la 28 lettre est un ' '
// la 29 lettre est un '-'
#define NBLETTRE 29

struct Realisateur{
    struct Realisateur* lettre[NBLETTRE];
    bool isRealisateur;
    struct Film* film;
    int longestFilm;
};

//  Créer le premier noeud de réalisateur
struct Realisateur* createEmptyRealisateur();

// Renvoie la liste de tout les enfants de réalisateur
struct Realisateur** getChidren(struct Realisateur* trie);

// Renvoie si un réalisateur est vide
bool isRealisateurEmpty(struct Realisateur* r);

// Renvoie la liste des films du réalisateur
struct Film* getFilm(struct Realisateur* r);

// Renvoie le la liste de film d'un realisateur
struct Realisateur* findRealisateur(struct Realisateur* r, char* realisateur);

// rajoute un réalisateur dans l'arbre
struct Realisateur* insertRealisateur(struct Realisateur* r, char* realisateur);

// rajoute un film au réalisateur donné
void insertFilm(struct Realisateur* r, struct Film* f);

// suprime un film avec son titre et son auteur
void deleteFilmFromRealisateur(struct Realisateur* r, char* realisateur, char* title);

// Renvoie si la cellule est un réalisateur ou non
bool isRealisateur(struct Realisateur* r);

// Vérifie qu'un réalisateur existe
bool isRealisateurExist(struct Realisateur* r,char* author);

// Affiche les réalisateur
void displayRealisateurs(struct Realisateur* r, char* realisateur, int index);

// suprime tous les réalisateurs
void deleteRealisateurs(struct Realisateur** r);

// Construie un arbre avec les réalisateur ainsi que les film a partir d'un txt
struct Realisateur* buildRealisateurFromtxt(char* nomfichier);

// renvoie le realisateur avec le plus de film
struct Realisateur* bestRealisateur(struct Realisateur* r);

// Renvoie la durée du plus long film
int findlongestFilm(struct Realisateur* r);


#endif //C_BANKREALISATEUR_H
