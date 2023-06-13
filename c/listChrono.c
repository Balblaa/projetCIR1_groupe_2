#include "listChrono.h"
#include "film.h"

// Créer une liste
struct ListChrono* createList(int size){

    // Réservation de mémoire pour une listChrono
    struct ListChrono* listFilm = malloc(sizeof (struct ListChrono));
    if(listFilm != NULL){

        // Initialisation de la list de film a NULL
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

    // Lecture de la base
    FILE* fichier;
    fichier = fopen(nomfichier, "r");

    // Initialisation des variable
    char realisateur[MAXAUTHOR];
    char title[MAXTITLE];
    char type[MAXTYPE];
    char time[4];
    int counter = 0;
    int index = 0;

    while(!feof(fichier)) {

        /* Pour chaque lettre de la base de donnée remplit la catégorie correspondante,
         * on change de catégorie lorsqu'un caractère est égal à ";",
         * lorsqu'il y a "\n", cela signifie que l'on change de ligne dans le txt :
         * alors ajoute le film à la list et on recommence*/
        char c = fgetc(fichier);
        if (c == '\n') {
            type[index] = '\0';
            struct Film* f = createFilm(title, type, realisateur, time);
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
    // On vérifie l'emplacement ou rajouter le film
    if(listFilm->list[atoi(f->time)-1] == NULL){
        // S'il est vide, il sera nouveau et la case ne sera plus vide
        listFilm->list[atoi(f->time)-1] = f;
    }
    else {
        // S'il y a déjà un film, on ajoute les films ensemble
        listFilm->list[atoi(f->time)-1] = addFilm(listFilm->list[atoi(f->time)-1], f);
    }
}

// Suprime un film à partir de son temps et de son titre (non utilisé
void deleteFilmByTitleFromListChrono(struct ListChrono* listFilm, int time, char* title){
    // récupère l'emplacement du film à supprimer
    struct Film* f = listFilm->list[time-1];
    // Supprime le film en libérant la mémoire
    deleteFilmByTitle(f, title);
}

// Suprime une liste chrono
void deleteListChrono(struct ListChrono** listFilm){

    //Pour chaque élément de la ListChrono
    int size = (*listFilm)->size;
    for(int i=0; i<size ; i++){

        // S'il y a un film dans une case
        if((*listFilm)->list[i] != NULL){
            // Il est supprimé et la mémoire est libéré
            deleteFilms(&(*listFilm)->list[i]);
        }
    }

    // On libère la mémoire pour la liste ainsi que la ListChrono
    free((*listFilm)->list);
    (*listFilm)->list = NULL;
    free(*listFilm);
    *listFilm = NULL;
}