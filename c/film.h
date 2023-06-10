#ifndef C_FILM_H
#define C_FILM_H
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXAUTHOR 40
#define MAXTITLE 60
#define MAXTYPE 30

struct Film{
    char author[MAXAUTHOR];
    char title[MAXTITLE];
    char type[MAXTYPE];
    int time;
    struct Film* next;
};

// crée un film avec les données en paramètre.
struct Film* createFilm(char title[MAXTITLE], char type[MAXTYPE], char author[MAXAUTHOR], int time);

// ajoute un film données en paramètre a la suite d'un autre.
struct Film* addFilm(struct Film* f, struct Film* newf);

// Renvoie le film suivant
struct Film* getNext(struct Film* f);

// Renvoie le réalisateur du film
char* getAuthor(struct Film*);

// Renvoie le titre du film
char* getTitle(struct Film* f);

// Renvoie le type du film
char* getType(struct Film* f);

// Renvoie le temps du film
int getTime(struct Film* f);

// Renvoie le premier film avec le titre recherché
struct Film* getFilmByTitle(struct Film* f, char title[MAXTITLE]);

// Renvoie le premier film avec le type recherché
struct Film* getFilmByType(struct Film* f, char type[MAXTYPE]);

// Renvoie le premier film avec la durée recherché
struct Film* getFilmByTime(struct Film* f, int time);

// Affiche les film a la suite
void printFilm(struct Film* iter);

// Suprime le premier film et renvoie le film suivant
struct Film* deleteFirst(struct Film* f);

// Suprime un film par son titre
struct Film* deleteFilmByTitle(struct Film* f, char title[MAXTITLE]);

// Suprime tous les films
void deleteFilms(struct Film** f);

#endif //C_FILM_H
