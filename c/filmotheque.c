#include "realisateur.h"
#include "filmotheque.h"
#include "film.h"

// Operation de création de la filmotheque
struct Filmotheque* createFilmotheque(char* nomfichier){
    struct Filmotheque* ft = malloc(sizeof(struct Filmotheque));
    if(ft != NULL){
        ft->r = buildRealisateurFromtxt(nomfichier);
        struct Realisateur* best = bestRealisateur(ft->r);
        ft->maxFilm = best->film->size;
        strcpy(ft->realisateurProductif, best->film->author);
        ft->plusLongFilm = 0;
    }
}

// Renvoie le nombre de film du réalisateur ayant le plus de film
int getMaxFilm(struct Filmotheque* ft){
    return ft->maxFilm;
}

// Renvoie la durée du plus long film
int getPlusLongFilm(struct Filmotheque* ft){
    return ft->plusLongFilm;
}

// Renvoie le nom du réalisateur avec le plus de film
char* getRealisateurProductif(struct Filmotheque* ft){
    return ft->realisateurProductif;
}

// Permet de rajouter un Film
void addNewFilm(struct Filmotheque* ft,struct Film* f){
    insertFilm(ft->r, f);
}

//affiche la structure
void printFilmotheque(struct Filmotheque* ft){
    int index = 0;
    char realisateur[MAXAUTHOR];
    displayRealisateurs(ft->r, realisateur, index);

    printf("l'auteur avec le plus de film est %s avec un total de %d\n", ft->realisateurProductif, ft->maxFilm);
}

// True si un réalisateur existe
bool isAuthorExist(struct Filmotheque* ft,char* author){
    return isRealisateurExist(ft->r, author);
}

//supprimer la structure
void deleteFilmothque(struct Filmotheque** ft){
    deleteRealisateurs(&(*ft)->r);
    free(*ft);
    *ft = NULL;
}

