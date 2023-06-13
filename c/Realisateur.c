#include "realisateur.h"

//  Créer le premier noeud
struct Realisateur* createEmptyRealisateur(){

    // On réserve de la mémoire pour la structure
    struct Realisateur* r = malloc(sizeof (struct Realisateur));
    if(r != NULL){

        // On initie les variables
        r->isRealisateur = false;
        for(int i=0; i<NBLETTRE; i++){
            r->lettre[i] = NULL; // Toute les case du tableau pointe à null
        }
        r->film = NULL;
        r->longestFilm = 0;
    }
    return r;
}

// Renvoie la liste de tous les enfants de réalisateur
struct Realisateur** getChidren(struct Realisateur* r){
    return r->lettre;
}

// Renvoie si un réalisateur est vide
bool isRealisateurEmpty(struct Realisateur* r){

    //Regarde si chaque élément du tableau de réalisateur est vide
    for(int i = 0; i<NBLETTRE; i++){
        if(getChidren(r)[i] != NULL){ // Si un seul ne l'ai pas renvoie false
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

    // On regarde lettre par lettre pour tse déplace à l'intérieur du node trie
    for(int i=0; i<n; i++){

        // Il existe trois cas particulié
        // '
        if(realisateur[i] - '\'' == 0 && getChidren(r)[NBLETTRE-3] != NULL){
            r = getChidren(r)[NBLETTRE-3];
        }
        // un espace
        else if(realisateur[i]-' ' == 0 && getChidren(r)[NBLETTRE-2] != NULL){
            r = getChidren(r)[NBLETTRE-2];
        }
        // -
        else if(realisateur[i]-'-' == 0 && getChidren(r)[NBLETTRE-1] != NULL){
            r = getChidren(r)[NBLETTRE-1];
        }
        else if(getChidren(r)[realisateur[i]-'a'] != NULL){
            r = getChidren(r)[realisateur[i]-'a'];
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
            if(getChidren(r)[NBLETTRE-3] != NULL){
                // Si oui, on se déplace dans la nouvelle "lettre" pour trouvé notre destination
                r = getChidren(r)[NBLETTRE-3];
            }
            else {
                // Si non, on la créer puis on continue de la même manière
                r->lettre[NBLETTRE-3] = createEmptyRealisateur();
                r = getChidren(r)[NBLETTRE-3];
            }
        }
        // On traite d'abord le caractère spécial: " "
        else if (realisateur[i]-' ' == 0){

            // On vérifie si l'emplacement existe
            if(r->lettre[NBLETTRE-2] != NULL){
                // Si oui, on se déplace dans la nouvelle "lettre" pour trouvé notre destination
                r = getChidren(r)[NBLETTRE-2];
            }
            else {
                // Si non, on la créer puis on continue de la même manière
                r->lettre[NBLETTRE-2] = createEmptyRealisateur();
                r = getChidren(r)[NBLETTRE-2];
            }
        }
        // Si se n'est pas un " " alors c'est peut être un "-"
        else if (realisateur[i]-'-' == 0){

            // On vérifie si l'emplacement existe
            if(getChidren(r)[NBLETTRE-1] != NULL){
                // Si oui, on se déplace dans la nouvelle "lettre" pour trouvé notre destination
                r = getChidren(r)[NBLETTRE-1];
            }
            else {
                // Si non, on la créer puis on continue de la même manière
                r->lettre[NBLETTRE-1] = createEmptyRealisateur();
                r = getChidren(r)[NBLETTRE-1];
            }
        }
        // Si se n'est pas un "-" alors c'est une lettre
        else {

            // Et l'on fera la même méthode que précédemment
            if(r->lettre[realisateur[i]-'a'] != NULL){
                r = getChidren(r)[realisateur[i]-'a'];
            }
            else {
                r->lettre[realisateur[i]-'a'] = createEmptyRealisateur();
                r = getChidren(r)[realisateur[i]-'a'];
            }
        }
    }

    // Une fois à la position de la dernière lettre du réalisateur, on met la vérification du réalisateur a true
    r->isRealisateur = true;
    return r;
}

// rajoute un film au réalisateur donné
void insertFilm(struct Realisateur* r, struct Film* f){
    // On récupère le réalisateur du film
    char* realisateur = getAuthor(f);

    /* On regarde si le réalisateur existe déjà
     * auquel cas on l'ajoute a la suite des autres film
     * ou alors, on crée un nouveau réalisateur*/
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

    // pour chaque caractère de réalisateur, on se déplace dans le NodeTrie
    for(int i=0; i<n; i++){
        // Trois cas particuliers à traiter
        //  '
        if(realisateur[i]- '\'' == 0){
            if(getChidren(r)[NBLETTRE-3] == NULL){
                return false;
            }
            r = getChidren(r)[NBLETTRE-3];
        }
        // un espace
        else if(realisateur[i]-' ' == 0){
            if(getChidren(r)[NBLETTRE-2] == NULL){
                return false;
            }
            r = getChidren(r)[NBLETTRE-2];
        }
        // -
        else if(realisateur[i]-'-' == 0){
            if(getChidren(r)[NBLETTRE-1] == NULL){
                return false;
            }
            r = getChidren(r)[NBLETTRE-1];
        }
        // Puis toute les lettres
        else {
            if (getChidren(r)[realisateur[i] - 'a'] == NULL) {
                return false;
            }
            r = getChidren(r)[realisateur[i] - 'a'];
        }
    }
    // On renvoie si la dernière structure Réalisateur est un réalisateur
    return isRealisateur(r);
}

// Affiche les réalisateurs (pour debug)
void displayRealisateurs(struct Realisateur* r, char* realisateur, int index){

    // Si le Réalisateur est un réalisateur alors on l'affiche
    if(isRealisateur(r)){
        realisateur[index] = '\0';
        printf("%s\n", realisateur);
    }
    // On ajoute un caractère à notre réalisateur puis on explore toutes les autres destinations possibles
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

    // Si c'est un réalisateur, on supprime les films qu'il contient
    if(isRealisateur(*r)){
        deleteFilms(&(*r)->film);
    }
    // S'il est dernier de la liste, on libère la mémoire
    if(isRealisateurEmpty(*r)){
        free(*r);
        *r = NULL;
    }
    // Sinon, on applique les conditions du dessus à tous les réalisateurs suivant
    else {
        for (int i = 0; i < NBLETTRE; i++) {
            if (getChidren(*r)[i] != NULL) {
                deleteRealisateurs(&(*r)->lettre[i]);
            }
        }
        // Puis après on libère la mémoire du réalisateur
        free(*r);
        *r = NULL;
    }
}

// Construie un arbre avec les réalisateurs ainsi que les films à partir d'un txt
struct Realisateur* buildRealisateurFromtxt(char* nomfichier){

    // Lecture de la base de donné
    FILE* fichier;
    fichier = fopen(nomfichier, "r");

    // Création d'un réalisateur souche
    struct Realisateur* r = createEmptyRealisateur();

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
         * alors ajoute le film au Réalisateur et on recommence*/
        char c = fgetc(fichier);
        if (c == '\n') {
            type[index] = '\0';
            struct Film* f = createFilm(title, type, realisateur, time);
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

    // si r est un réalisateur, alors on initie max et best avec ses valeurs
    if(isRealisateur(r)){
        max = getsize(getFilm(r));
        best = r;
    }

    // On regarde pour chaque enfant du réalisateur lequel est le meilleur réalisateur
    for(int i=0; i<NBLETTRE; i++){
        if(getChidren(r)[i] != NULL){
            struct Realisateur* temp = bestRealisateur(r->lettre[i]);
            if(getsize(getFilm(temp)) > max){
                max = getsize(getFilm(temp));
                best = temp;
            }
        }
    }

    // On renvoie le meilleur réalisateur
    return best;
}

// Renvoie la durée du plus long film
int findlongestFilm(struct Realisateur* r){
    int max = 0;

    // si r est un réalisateur, alors on initie max avec sa valeur
    if(isRealisateur(r)){
        max = longestFilm(r->film);
    }

    // On regarde pour chaque enfant du réalisateur lequel a le plus long film
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