#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "film.h"

// crée un film avec les données en paramètre.
struct Film* createFilm(char title[MAXTITLE], char type[MAXTYPE],char author[MAXAUTHOR], int time){
    struct Film* f = malloc(sizeof (struct Film));
    if(f != NULL){
        strcpy(f->title, title);
        strcpy(f->type, type);
        strcpy(f->author, author);
        f->time = time;
        f->size = 1;
        f->next = NULL;
    }
    return f;
}

// ajoute un film données en paramètre à la suite.
struct Film* addFilm(struct Film* f, struct Film* newf){
    if(f == NULL){
        return newf;
    }
    else {
        newf->next = f;
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
int getTime(struct Film* f){
    return f->time;
}

// Renvoie le premier film avec le titre recherché
struct Film* getFilmByTitle(struct Film* f, char title[MAXTITLE]){
    if(f != NULL){
        struct Film* iter = f;
        if(strcmp(getTitle(iter), title) == 0){
            return iter;
        }
        while(getNext(iter) != NULL){
            iter = getNext(iter);
            if(strcmp(getTitle(iter), title) == 0){
                return iter;
            }
        }
    }
    return NULL;
}

// Renvoie le premier film avec le type recherché
struct Film* getFilmByType(struct Film* f, char type[MAXTYPE]){
    if(f != NULL){
        struct Film* iter = f;
        if(strcmp(getType(iter), type) == 0){
            return iter;
        }
        while(getNext(iter) != NULL){
            iter = getNext(iter);
            if(strcmp(getType(iter), type) == 0){
                return iter;
            }
        }
    }
    return NULL;
}

// Renvoie le premier film avec la durée recherché
struct Film* getFilmByTime(struct Film* f, int time){
    if(f != NULL){
        struct Film* iter = f;
        if(getTime(f) == time){
            return iter;
        }
        while(getNext(iter) != NULL){
            iter = getNext(iter);
            if(getTime(f) == time){
                return iter;
            }
        }
    }
    return NULL;
}

// Renvoie la durée du film le plus long
int longestFilm(struct Film* f){
    int max = getTime(f);
    struct Film* iter = f;
    while (iter->next != NULL){
        iter = iter->next;
        if(getTime(iter) > max){
            max = getTime(iter);
        }
    }
    return max;
}

// Affiche les film a la suite
void printFilm(struct Film* f){
    if (f == NULL) {
        printf("NULL\n");
        return;
    }
    struct Film* iter = f;

    while (iter->next != NULL) {
        printf("%s;%s;%s;%d -> ", getTitle(iter), getType(iter), getAuthor(iter), getTime(iter));
        iter = iter->next;
    }
    printf("%s;%s;%s;%d -> NULL\n", getTitle(iter), getType(iter), getAuthor(iter), getTime(iter));
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