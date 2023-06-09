#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "film.h"

// crée un film avec les données en paramètre.
struct Film* createFilm(char title[MAXTITLE], char type[MAXTYPE], int time){
    struct Film* f = malloc(sizeof (struct Film));
    if(f != NULL){
        strcpy(f->title, title);
        strcpy(f->type, type);
        f->time = time;
        f->next = NULL;
    }
    return f;
}

// ajoute un film données en paramètre à la suite.
struct Film* addFilm(struct Film* f, char title[MAXTITLE], char type[MAXTYPE], int time){
    if(f == NULL){
        return createFilm(title, type, time);
    }
    else {
        struct Film* iter = f;
        while(f->next != NULL){
            iter = iter->next;
        }
        f->next = createFilm(title, type, time);
        return f;
    }
}

// Renvoie le film suivant
struct Film* getNext(struct Film* f){
    return f->next;
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
        while(getNext(f) != NULL){
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
        while(getNext(f) != NULL){
            iter = getNext(iter);
            if(strcmp(getTitle(iter), type) == 0){
                return iter;
            }
        }
    }
    return NULL;
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

// Suprime tous les films
void deleteFilm(struct Film** f){
    struct Film* iter = *f;
    while(iter->next != NULL){
        iter = deleteFirst(iter);
    }
    deleteFirst(iter);
    *f = NULL;
}