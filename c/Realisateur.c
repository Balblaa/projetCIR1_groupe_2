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

// Renvoie la liste de tout les enfants de réalisateur
struct Realisateur** getChidren(struct Realisateur* r){
    return r->lettre;
}

// Renvoie la liste des films du réalisateur
struct Film* getFilm(struct Realisateur* r){
    return r->film;
}

// Renvoie le la liste de film d'un realisateur
struct Realisateur* findRealisateur(struct Realisateur* r, char* realisateur){
    int n = strlen(realisateur);
    for(int i=0; i<n; i++){
        if(realisateur[i]-'-' == 0 && r->lettre[NBLETTRE-1] == NULL){
            r = r->lettre[NBLETTRE-1];
        }
        else if(r->lettre[realisateur[i]-'a'] != NULL){
            r = r->lettre[realisateur[i]-'a'];
            }
        else {
            return NULL;
        }
    }
    return r;
}

// rajoute un réalisateur dans l'arbre et le renvoie
struct Realisateur* insertRealisateur(struct Realisateur* r, char* realisateur){

    // Obtenir la longueur du nom de du réalisateur
    int n = strlen(realisateur);

    // Pour chaque lettre du nom du réalisateur on regarde la destination
    for(int i=0; i<n; i++){

        // On traite d'abord le caractère spécial: "-"
        if (realisateur[i]-'-' == 0){

            // On vérifie si l'emplacement existe
            if(r->lettre[NBLETTRE-1] != NULL){
                // Si oui, on se déplace dans la nouvelle "lettre" pour trouvé notre destination
                r = r->lettre[NBLETTRE-1];
            }
            else {
                // Si non, on la créer puis on continue de la même manière
                r->lettre[NBLETTRE-1] = createEmptyRealisateur();
                r = r->lettre[NBLETTRE-1];
            }
        }
        // Si se n'est pas un "-" alors c'est une lettre
        else {

            // Et l'on fera la même méthode que précédemment
            if(r->lettre[realisateur[i]-'a'] != NULL){
                r = r->lettre[realisateur[i]-'a'];
            }
            else {
                r->lettre[realisateur[i]-'a'] = createEmptyRealisateur();
                r = r->lettre[realisateur[i]-'a'];
            }
        }
    }

    // Une fois à la position de la dernière lettre du réalisateur, on met la vérification du réalisateur a true
    r->isRealisateur = true;
    return r;
}

// rajoute un film au réalisateur donné
void insertFilm(struct Realisateur* r, struct Film* f){
    char* realisateur = getAuthor(f);
    if(isRealisateurExist(r, realisateur)){
        r = findRealisateur(r, realisateur);
        r->film = addFilm(r->film, f);
    }
    else {
        r = insertRealisateur(r, realisateur);
        r->film = addFilm(r->film, f);
    }
}

// suprime un film avec son titre et son auteur
void deleteFilmByName(struct Realisateur* r, char* realisateur, char* title[MAXTITLE]);

// Renvoie si la cellule est un réalisateur ou non
bool isRealisateur(struct Realisateur* r){
    return r->isRealisateur;
}

// Vérifie qu'un réalisateur existe
bool isRealisateurExist(struct Realisateur* r,char* realisateur){
    int n = strlen(realisateur);
    for(int i=0; i<n; i++){
        if(realisateur[i]-'-' == 0 && r->lettre[NBLETTRE-1] == NULL){
            return false;
        }
        else {
            if(r->lettre[realisateur[i]-'a'] == NULL){
                return false;
            }
        }
        r = r->lettre[realisateur[i]-'a'];
    }
    return r->isRealisateur;
}

// Affiche les réalisateur
void displayRealisateur(struct Realisateur* r, char* realisateur, int index){
    if(isRealisateur(r)){
        realisateur[index] = '\0';
        printf("%s\n", realisateur);
    }
    for(int i=0; i<NBLETTRE; i++){
        if(getChidren(r)[i] != NULL){
            if(i == 26){
                realisateur[index] = '-';
            }
            else {
                realisateur[index] = 'a' + i;
            }
            displayRealisateur(getChidren(r)[i], realisateur, index+1);
        }
    }
}

// suprime tous les réalisateurs
void deleteRealisateur(struct Realisateur* r);