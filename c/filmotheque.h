#ifndef C_FILMOTHEQUE_H
#define C_FILMOTHEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "realisateur.h"
#include "listChrono.h"

struct Filmotheque{
    struct Realisateur* r;
    int maxFilm;
    char realisateurProductif[MAXAUTHOR];
    int plusLongFilm;
    struct ListChrono* listFilmByChrono;
};

//operation de création
struct Filmotheque* createFilmotheque(char* nomfichier);

// Renvoie le nombre de film du réalisateur ayant le plus de film
int getMaxFilm(struct Filmotheque* ft);

// Renvoie la durée du plus long film
int getPlusLongFilm(struct Filmotheque* ft);

// Renvoie le nom du réalisateur avec le plus de film
char* getRealisateurProductif(struct Filmotheque* ft);

// Renvoie un film en fonction d'une durée
struct Film* getFilmByListChrono(struct Filmotheque* ft, int time);

// Permet de rajouter un Film
void addNewFilm(struct Filmotheque* ft,char title[MAXTITLE], char type[MAXTYPE],char author[MAXAUTHOR], char* time);

//affiche la structure
void printFilmotheque(struct Filmotheque* ft);

// True si un réalisateur existe
bool isAuthorExist(struct Filmotheque* ft,char* author);

// Surpimer un film avec le nom du réalisateur et le titre
void deleteFilmFromFilmotheque(struct Filmotheque* ft, char* realisateur, char* title, int time);

//supprimer la structure
void deleteFilmothque(struct Filmotheque** ft);

// Renvoie un fichier result.txt avec les Films cherché par réalisateur
void searchByAuthor(struct Filmotheque* ft, char* realisateur);

// Renvoie un fichier result.txt avec les Films cherché pas temps
void searchByTime(struct Filmotheque* ft, int time);

// Renvoie un fichier avec le meilleur Réalisateur
void searchBestAuthor(struct Filmotheque* ft);

#endif //C_FILMOTHEQUE_H
