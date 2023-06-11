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
        r->longestFilm = 0;
    }
    return r;
}

// Renvoie la liste de tout les enfants de réalisateur
struct Realisateur** getChidren(struct Realisateur* r){
    return r->lettre;
}

// Renvoie si un réalisateur est vide
bool isRealisateurEmpty(struct Realisateur* r){
    for(int i = 0; i<NBLETTRE; i++){
        if(getChidren(r)[i] != NULL){
            return false;
        }
    }
    return true;
}

// Renvoie la liste des films du réalisateur
struct Film* getFilm(struct Realisateur* r){
    return r->film;
}

// Renvoie le la liste de film d'un realisateur
struct Realisateur* findRealisateur(struct Realisateur* r, char* realisateur){
    int n = strlen(realisateur);
    for(int i=0; i<n; i++){

        // 44 représente le caractère "'"
        if(realisateur[i] - '\'' == 0 && r->lettre[NBLETTRE-3] != NULL){
            r = r->lettre[NBLETTRE-3];
        }
        else if(realisateur[i]-' ' == 0 && r->lettre[NBLETTRE-2] != NULL){
            r = r->lettre[NBLETTRE-2];
        }
        else if(realisateur[i]-'-' == 0 && r->lettre[NBLETTRE-1] != NULL){
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


        // On traite d'abord le caractère spécial: "'"
        if (realisateur[i]- '\'' == 0){

            // On vérifie si l'emplacement existe
            if(r->lettre[NBLETTRE-3] != NULL){
                // Si oui, on se déplace dans la nouvelle "lettre" pour trouvé notre destination
                r = r->lettre[NBLETTRE-3];
            }
            else {
                // Si non, on la créer puis on continue de la même manière
                r->lettre[NBLETTRE-3] = createEmptyRealisateur();
                r = r->lettre[NBLETTRE-3];
            }
        }
        // On traite d'abord le caractère spécial: " "
        else if (realisateur[i]-' ' == 0){

            // On vérifie si l'emplacement existe
            if(r->lettre[NBLETTRE-2] != NULL){
                // Si oui, on se déplace dans la nouvelle "lettre" pour trouvé notre destination
                r = r->lettre[NBLETTRE-2];
            }
            else {
                // Si non, on la créer puis on continue de la même manière
                r->lettre[NBLETTRE-2] = createEmptyRealisateur();
                r = r->lettre[NBLETTRE-2];
            }
        }
        // Si se n'est pas un " " alors c'est peut être un "-"
        else if (realisateur[i]-'-' == 0){

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
void deleteFilmFromRealisateur(struct Realisateur* r, char* realisateur, char* title){
    r = findRealisateur(r, realisateur);
    deleteFilmByTitle(r->film, title);
}

// Renvoie si la cellule est un réalisateur ou non
bool isRealisateur(struct Realisateur* r){
    return r->isRealisateur;
}

// Vérifie qu'un réalisateur existe
bool isRealisateurExist(struct Realisateur* r,char* realisateur){
    int n = strlen(realisateur);
    for(int i=0; i<n; i++){
        if(realisateur[i]- '\'' == 0){
            if(r->lettre[NBLETTRE-3] == NULL){
                return false;
            }
            r = r->lettre[NBLETTRE-3];
        }
        else if(realisateur[i]-' ' == 0){
            if(r->lettre[NBLETTRE-2] == NULL){
                return false;
            }
            r = r->lettre[NBLETTRE-2];
        }
        else if(realisateur[i]-'-' == 0){
            if(r->lettre[NBLETTRE-1] == NULL){
                return false;
            }
            r = r->lettre[NBLETTRE-1];
        }
        else {
            if (r->lettre[realisateur[i] - 'a'] == NULL) {
                return false;
            }
            r = r->lettre[realisateur[i] - 'a'];
        }
    }
    return r->isRealisateur;
}

// Affiche les réalisateur
void displayRealisateurs(struct Realisateur* r, char* realisateur, int index){
    if(isRealisateur(r)){
        realisateur[index] = '\0';
        printf("%s\n", realisateur);
    }
    for(int i=0; i<NBLETTRE; i++){
        if(getChidren(r)[i] != NULL){
            if(i == NBLETTRE-3){
                realisateur[index] = '\'';
            }
            else if(i == NBLETTRE-2){
                realisateur[index] = ' ';
            }
            else if(i == NBLETTRE-1){
                realisateur[index] = '-';
            }
            else {
                realisateur[index] = 'a' + i;
            }
            displayRealisateurs(getChidren(r)[i], realisateur, index+1);
        }
    }
}

// suprime tous les réalisateurs
void deleteRealisateurs(struct Realisateur** r){
    if(isRealisateur(*r)){
        deleteFilms(&(*r)->film);
    }
    if(isRealisateurEmpty(*r)){
        free(*r);
        *r = NULL;
    }
    else {
        for (int i = 0; i < NBLETTRE; i++) {
            if (getChidren(*r)[i] != NULL) {
                deleteRealisateurs(&(*r)->lettre[i]);
            }
        }
        free(*r);
        *r = NULL;
    }
}

// Construie un arbre avec les réalisateur ainsi que les film a partir d'un txt
struct Realisateur* buildRealisateurFromtxt(char* nomfichier){

    FILE* fichier;
    fichier = fopen(nomfichier, "r");

    struct Realisateur* r = createEmptyRealisateur();

    char realisateur[MAXAUTHOR];
    char title[MAXTITLE];
    char type[MAXTYPE];
    char time[3];
    int counter = 0;
    int index = 0;

    while(!feof(fichier)) {
        char c = fgetc(fichier);
        if (c == '\n') {
            type[index-1] = '\0';
            struct Film* f = createFilm(title, type, realisateur, atoi(time));
            insertFilm(r, f);
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
    return r;
}

// renvoie le realisateur avec le plus de film
struct Realisateur* bestRealisateur(struct Realisateur* r){

    int max = 0;
    struct Realisateur* best = NULL;

    if(isRealisateur(r)){
        max = r->film->size;
        best = r;
    }
    for(int i=0; i<NBLETTRE; i++){
        if(r->lettre[i] != NULL){
            struct Realisateur* temp = bestRealisateur(r->lettre[i]);
            if(temp->film->size > max){
                max = temp->film->size;
                best = temp;
            }
        }
    }
    return best;
}

// Renvoie la durée du plus long film
int findlongestFilm(struct Realisateur* r){
    int max = 0;

    if(isRealisateur(r)){
        max = longestFilm(r->film);
    }
    for(int i=0; i<NBLETTRE; i++){
        if(r->lettre[i] != NULL){
            int newTime = findlongestFilm(r->lettre[i]);
            if(newTime > max){
                max = newTime;
            }
        }
    }
    return max;
}