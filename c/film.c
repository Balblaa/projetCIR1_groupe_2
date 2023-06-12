#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "film.h"

// crée un film avec les données en paramètre.
struct Film* createFilm(char title[MAXTITLE], char type[MAXTYPE],char author[MAXAUTHOR], char* time){
    // On réserve de la mémoire pour un film
    struct Film* f = malloc(sizeof (struct Film));

    if(f != NULL){
        // On attribut chaque valeur donné une à une
        strcpy(f->title, title);
        strcpy(f->type, type);
        strcpy(f->author, author);
        strcpy(f->time, time);

        // On initie la taille du film a 1 car il n'y a qu'un seul film
        f->size = 1;
        f->next = NULL;
    }
    return f;
}

// ajoute un film donné en paramètre à la suite.
struct Film* addFilm(struct Film* f, struct Film* newf){

    // Si f n'est pas un film
    if(f == NULL){
        return newf;
    }
    else {
        // On met bout à bout les deux films
        newf->next = f;
        // En augmentant le nombre de film
        newf->size = f->size + 1;
        return newf;
    }
}

// Renvoie le film suivant
struct Film* getNext(struct Film* f){
    return f->next;
}

// Renvoie le réalisateur du film
char* getAuthor(struct Film* f){
    return f->author;
}

// Renvoie le titre du film
char* getTitle(struct Film* f){
    return f->title;
}

// Renvoie le type du film
char* getType(struct Film* f){
    return f->type;
}

// Renvoie le temps du film
char* getTime(struct Film* f){
    return f->time;
}

// Renvoie le premier film avec le titre recherché
struct Film* getFilmByTitle(struct Film* f, char title[MAXTITLE]){

    // On vérifie que le film ne soit pas nul
    if(f != NULL){
        struct Film* iter = f;
        // On regarde si le premier film correspond à notre recherche
        if(strcmp(getTitle(iter), title) == 0){
            return iter;
        }

        // Puis on regarde si tous les autres films correspondent à notre recherche
        while(getNext(iter) != NULL){
            iter = getNext(iter);
            if(strcmp(getTitle(iter), title) == 0){
                return iter;
            }
        }
    }

    // Dans aucun des cas
    return NULL;
}

// Renvoie le premier film avec le type recherché
struct Film* getFilmByType(struct Film* f, char type[MAXTYPE]){

    // On vérifie que le film ne soit pas nul
    if(f != NULL){
        struct Film* iter = f;
        // On regarde si le premier film correspond à notre recherche
        if(strcmp(getType(iter), type) == 0){
            return iter;
        }
        // Puis on regarde si tous les autres films correspondent à notre recherche
        while(getNext(iter) != NULL){
            iter = getNext(iter);
            if(strcmp(getType(iter), type) == 0){
                return iter;
            }
        }
    }
    // Dans aucun des cas
    return NULL;
}

// Renvoie le premier film avec la durée recherché
struct Film* getFilmByTime(struct Film* f, int time){

    // On regarde si le premier film correspond à notre recherche
    if(f != NULL){
        struct Film* iter = f;
        // On regarde si le premier film correspond à notre recherche
        if(atoi(getTime(f)) == time){
            return iter;
        }
        // Puis on regarde si tous les autres films correspondent à notre recherche
        while(getNext(iter) != NULL){
            iter = getNext(iter);
            if(atoi(getTime(f)) == time){
                return iter;
            }
        }
    }
    // Dans aucun des cas
    return NULL;
}

// Renvoie la durée du film le plus long
int longestFilm(struct Film* f){
    // On récupère le temps du premier film
    int max = atoi(getTime(f));
    struct Film* iter = f;

    // Puis on parcour tous les films next pour comparer le temps des autres films
    while (iter->next != NULL){
        iter = iter->next;
        if(atoi(getTime(iter)) > max){
            max = atoi(getTime(iter));
        }
    }
    return max;
}

// Affiche les films la suite
void printFilm(struct Film* f){

    // Affiche nul et termine la récursion quand f est null
    if (f == NULL) {
        printf("NULL\n");
        return;
    }
    struct Film* iter = f;
    // Affiche chaque information du
    while (iter->next != NULL) {
        printf("%s;%s;%s;%s -> ", getTitle(iter), getType(iter), getAuthor(iter), getTime(iter));
        iter = iter->next;
    }
    printf("%s;%s;%s;%s -> NULL\n", getTitle(iter), getType(iter), getAuthor(iter), getTime(iter));
}

// Suprime le premier film
struct Film* deleteFirst(struct Film* f){
    if (f == NULL) {
        return f;
    }
    struct Film* new = f->next;
    free(f);

    return new;
}

// Suprime un film par son titre
struct Film* deleteFilmByTitle(struct Film* f, char title[MAXTITLE]){
    struct Film* iter = f;
    struct Film* suprFilm;
    if (strcmp(getTitle(iter), title) == 0) {
        f = deleteFirst(iter);
    } else {
        while(strcmp(getTitle(iter->next), title) != 0){
            iter = getNext(iter);
        }
        suprFilm = iter->next;
        iter->next = iter->next->next;
        free(suprFilm);
        f->size = f->size - 1;
    }
    return f;
}

// Suprime tous les films
void deleteFilms(struct Film** f){
    if(*f != NULL) {
        struct Film *iter = *f;
        while (iter->next != NULL) {
            iter = deleteFirst(iter);
        }
        deleteFirst(iter);
        *f = NULL;
    }
}