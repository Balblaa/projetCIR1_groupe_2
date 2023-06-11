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
        ft->plusLongFilm = findlongestFilm(ft->r);

        ft->filmParChrnono = ;
    }
}

// Créer la liste des films rangés par chrono
void createListFilmChrono(struct Filmotheque* ft, char* nomfichier){
    FILE* fichier;
    fichier = fopen(nomfichier, "r");

    struct Film* list[ft->plusLongFilm];
    for(int i = 0; i<ft->plusLongFilm; i++){
        list[i] = NULL;
    }

    char realisateur[MAXAUTHOR];
    char title[MAXTITLE];
    char type[MAXTYPE];
    char time[4];
    int counter = 0;
    int index = 0;

    while(!feof(fichier)) {
        char c = fgetc(fichier);
        if (c == '\n') {
            type[index-1] = '\0';
            struct Film* f = createFilm(title, type, realisateur, atoi(time));
            if(list[f->time] == NULL){
                list[f->time] = f;
            }
            else {
                list[f->time] = addFilm(list[f->time], f);
            }
            counter = 0;
            index = 0;
        }
        else if (c == ';') {
            switch (counter) {
                case 0:
                    realisateur[index] = '\0';
                    counter++;
                    index = 0;
                    break;
                case 1:
                    title[index] = '\0';
                    counter++;
                    index = 0;
                    break;
                case 2:
                    time[index] = '\0';
                    counter++;
                    index = 0;
                    break;
            }
        } else {
            switch (counter) {
                case 0:
                    if(c >= 'A' && c <= 'Z'){
                        realisateur[index] = c + 32;
                    }
                    else {
                        realisateur[index] = c;
                    }
                    index++;
                    break;
                case 1:
                    title[index] = c;
                    index++;
                    break;
                case 2:
                    time[index] = c;
                    index++;
                    break;
                case 3:
                    type[index] = c;
                    index++;
                    break;
            }
        }
    }

    fclose(fichier);
    ft->filmParChrnono = list;
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
    ft->plusLongFilm = findlongestFilm(ft->r);
}

//affiche la structure
void printFilmotheque(struct Filmotheque* ft){
    int index = 0;
    char realisateur[MAXAUTHOR];
    displayRealisateurs(ft->r, realisateur, index);

    printf("l'auteur avec le plus de film est %s avec un total de %d\n", ft->realisateurProductif, ft->maxFilm);
    printf("le film le plus long dure %d minutes", getPlusLongFilm(ft));
}

// True si un réalisateur existe
bool isAuthorExist(struct Filmotheque* ft,char* author){
    return isRealisateurExist(ft->r, author);

}

// Surpimer un film avec le nom du réalisateur et le titre
void deleteFilmFromFilmotheque(struct Filmotheque* ft, char* realisateur, char* title){
    deleteFilmFromRealisateur(ft->r, realisateur, title);
    struct Realisateur* best = bestRealisateur(ft->r);
    ft->maxFilm = best->film->size;
    strcpy(ft->realisateurProductif, best->film->author);
}

//supprimer la structure
void deleteFilmothque(struct Filmotheque** ft){
    deleteRealisateurs(&(*ft)->r);
    free(*ft);
    *ft = NULL;
}

