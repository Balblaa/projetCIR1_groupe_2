#include "realisateur.h"
#include "filmotheque.h"
#include "film.h"

// Operation de création de la filmotheque
struct Filmotheque* createFilmotheque(char* nomfichier){
    struct Filmotheque* ft = malloc(sizeof(struct Filmotheque));
    if(ft != NULL){
        ft->r = buildRealisateurFromtxt(nomfichier);
        ft->maxFilm = 0;
        ft->plusLongFilm = 0;
    }
}

// Renvoie le nombre de film du réalisateur ayant le plus de film
int getMaxFilm(struct Filmotheque* ft);

// Renvoie la durée du plus long film
void getPlusLongFilm(struct Filmotheque* ft);

// Renvoie le nom du réalisateur avec le plus de film
void getRealisateurProductif(struct Filmotheque* ft);

// True si la filmothèque est vide False sinon
bool isFilmothequeEmpty(struct Filmotheque* ft);

// Permet de rajouter un Film
void addNewFilm(struct Filmotheque* ft,struct Film* f);

//affiche la structure
void printFilmotheque(struct Filmotheque* ft);

// True si un réalisateur existe
bool isAuthorExist(struct Filmotheque* ft,char* author);

//supprimer la structure
void deleteFilmothque(struct Filmotheque* ft);