#include "realisateur.h"

//  Créer le premier noeud
struct Realisateur* createEmptyRealisateur(){
    struct Realisateur* r = malloc(sizeof (struct Realisateur));
    if(r != NULL){
        r->isRealisateur = false;
        for(int i=0; i<NBLETTRE; i++){
            r->lettre[i] = NULL;
        }
        r->film = NULL;
    }
    return r;
}

// Renvoie le la liste de film d'un realisateur
struct Realisateur* findRealisateur(struct Realisateur* r, char* realisateur){
    int n = strlen(realisateur);
    for(int i=0; i<n; i++){
        if(r->lettre[realisateur[i]-'a'] != NULL){
            if(r->lettre[realisateur[i]-'a'] == 27){

            } else {
                r = r->lettre[realisateur[i]-'a'];
            }
        }
    }
    return r;
}

// rajoute un film au réalisateur donné
void insertFilm(struct Realisateur* r, struct Film* f);

// suprime un film avec son titre et son auteur
void deleteFilm(struct Realisateur* r, char* realisateur, char* title[MAXTITLE]);

// Renvoie si la cellule est un réalisateur ou non
bool isRealisateur(struct Realisateur* r);

// Vérifie qu'un réalisateur existe
bool isRealisateurExist(struct Realisateur* r,char* author);

// suprime tous les réalisateurs
void deleteRealisateur(struct Realisateur* r);