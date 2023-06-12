#ifndef C_LISTCHRONO_H
#define C_LISTCHRONO_H

#include "film.h"

struct ListChrono{
    struct Film** list;
    int size;
};

// Créer une liste
struct ListChrono* createList(int size);

// Remplie la list de film
void buildListFromtxt(struct ListChrono* listFilm, char* nomfichier);

// Rajoute un film dans la liste
void addFilmToList(struct ListChrono* listFilm, struct Film* f);

// Suprime un film à partir de son temps et de son titre
void deleteFilmFromListChrono(struct ListChrono* listFilm, int time, char* title);

// Suprime une liste chrono
void deleteListChrono(struct ListChrono** listFilm);

#endif //C_LISTCHRONO_H