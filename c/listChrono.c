#include "listChrono.h"
#include "film.h"

// Créer une liste
struct ListChrono* createList(int size){
    struct ListChrono* listFilm = malloc(sizeof (struct ListChrono));
    if(listFilm != NULL){
        listFilm->list = malloc(size * sizeof (struct Film*));
        for(int i=0; i<size; i++){
            listFilm->list[i] = NULL;
        }
        listFilm->size = size;
    }
    return listFilm;
}

// Remplie la list de film
void buildListFromtxt(struct ListChrono* listFilm, char* nomfichier){
    FILE* fichier;
    fichier = fopen(nomfichier, "r");

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
            addFilmToList(listFilm, f);
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
}

// Rajoute un film dans la liste
void addFilmToList(struct ListChrono* listFilm, struct Film* f){
    if(listFilm->list[f->time-1] == NULL){
        listFilm->list[f->time-1] = f;
    }
    else {
        listFilm->list[f->time-1] = addFilm(listFilm->list[f->time-1], f);
    }
}

// Suprime un film à partir de son temps et de son titre
void deleteFilmFromListChrono(struct ListChrono* listFilm, int time, char* title){
    struct Film* f = listFilm->list[time-1];
    deleteFilmByTitle(f, title);
}

// Suprime une liste chrono
void deleteListChrono(struct ListChrono** listFilm){
    int size = (*listFilm)->size;
    for(int i=0; i<size ; i++){
        if((*listFilm)->list[i] != NULL){
            deleteFilms(&(*listFilm)->list[i]);
        }
    }
    free((*listFilm)->list);
    (*listFilm)->list = NULL;
    free(*listFilm);
    *listFilm = NULL;
}