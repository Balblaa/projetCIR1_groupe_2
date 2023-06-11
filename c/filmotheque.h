#ifndef C_FILMOTHEQUE_H
#define C_FILMOTHEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "realisateur.h"

struct Filmotheque{
    struct Realisateur* r;
    int maxFilm;
    char realisateurProductif[MAXAUTHOR];
    int plusLongFilm;
    struct Film** filmParChrnono;
};

//operation de création
struct Filmotheque* createFilmotheque(char* nomfichier);

// Créer la liste des films rangés par chrono
void createListFilmChrono(struct Filmotheque* ft,char* nomfichier);

// Renvoie le nombre de film du réalisateur ayant le plus de film
int getMaxFilm(struct Filmotheque* ft);

// Renvoie la durée du plus long film
int getPlusLongFilm(struct Filmotheque* ft);

// Renvoie le nom du réalisateur avec le plus de film
char* getRealisateurProductif(struct Filmotheque* ft);

// Permet de rajouter un Film
void addNewFilm(struct Filmotheque* ft,struct Film* f);

//affiche la structure
void printFilmotheque(struct Filmotheque* ft);

// True si un réalisateur existe
bool isAuthorExist(struct Filmotheque* ft,char* author);

// Surpimer un film avec le nom du réalisateur et le titre
void deleteFilmFromFilmotheque(struct Filmotheque* ft, char* realisateur, char* title);

//supprimer la structure
void deleteFilmothque(struct Filmotheque** ft);

// Renvoie un fichier result.txt avec les Films cherché par Titre
void searchByAuthor(struct Filmotheque* ft);

#endif //C_FILMOTHEQUE_H
