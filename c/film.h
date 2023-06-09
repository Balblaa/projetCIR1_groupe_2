#ifndef C_FILM_H
#define C_FILM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXTITLE 60
#define MAXTYPE 30

struct Film{
    char title[MAXTITLE];
    char type[MAXTYPE];
    int time;
    struct Film* f;
};

// crée un film avec les données en paramètre.
struct Film* createFilm(char title[MAXTITLE], char type[MAXTYPE], int time);

// ajoute un film données en paramètre a la suite d'un autre.
struct Film* addFilm(struct Film* f, char title[MAXTITLE], char type[MAXTYPE], int time);

// Renvoie le premier film avec le titre recherché
struct Film* getFilmByTitle(struct Film* f, char title[MAXTITLE]);

// Renvoie le premier film avec le type recherché
struct Film* getFilmByType(struct Film f, char type[MAXTYPE]);



#endif //C_FILM_H
