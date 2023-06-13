#include <time.h>
#include "realisateur.h"
#include "filmotheque.h"
#include "listChrono.h"
#include "film.h"

// Operation de création de la filmotheque
struct Filmotheque* createFilmotheque(char* nomfichier){

    // On réserve de la place pour la structure
    struct Filmotheque* ft = malloc(sizeof(struct Filmotheque));
    if(ft != NULL){
        // On initie les réalisateurs avec la base de donnée
        ft->r = buildRealisateurFromtxt(nomfichier);

        // On regarde le réalisateur ayant le plus de films et on initie les différentes variable
        struct Realisateur* best = bestRealisateur(ft->r);
        // Le nombre de film du réalisateur qui à le plus de film
        ft->maxFilm = best->film->size;
        // Le nom du réalisateur en question
        strcpy(ft->realisateurProductif, best->film->author);
        // la durée du plus long film
        ft->plusLongFilm = findlongestFilm(ft->r);

        // On crée la liste des films rangé par chrono
        ft->listFilmByChrono = createList(ft->plusLongFilm);
        buildListFromtxt(ft->listFilmByChrono, nomfichier);
    }
    return ft;
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

// Renvoie un film en fonction d'une durée
struct Film* getFilmByListChrono(struct Filmotheque* ft, int time){
    return ft->listFilmByChrono->list[time-1];
}

// Permet de rajouter un Film (non utilisé)
void addNewFilm(struct Filmotheque* ft,char title[MAXTITLE], char type[MAXTYPE],char author[MAXAUTHOR], char* time){

    // Création du film
    struct Film* f = createFilm(title, type, author, time);

    // Insertion du nouveau film
    insertFilm(ft->r, f);

    // Vérification si le réalisateur a été remplacé
    ft->plusLongFilm = findlongestFilm(ft->r);
}

//affiche la structure (pour débug)
void printFilmotheque(struct Filmotheque* ft){

    /* Affiche les réalisateurs ainsi que le meilleur réalisateur et son nombre de films.
     * Ainsi que la longueur du film le plus long*/

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

// Supprimer un film avec le nom du réalisateur et le titre (non utilisé)
void deleteFilmFromFilmotheque(struct Filmotheque* ft, char* realisateur, char* title, int time){

    /* Supprime un Film d'abord dans la listChrono de ft via le titre du film
     * puis dans le Nodetrie de réalisateur toujours avec le titre*/
    deleteFilmByTitleFromListChrono(ft->listFilmByChrono, time, title);
    deleteFilmFromRealisateur(ft->r, realisateur, title);

    // on remet à jour le meilleur réalisateur ainsi que son nombre de films
    struct Realisateur* best = bestRealisateur(ft->r);
    ft->maxFilm = best->film->size;
    strcpy(ft->realisateurProductif, best->film->author);
}

//supprimer la structure
void deleteFilmothque(struct Filmotheque** ft){

    //On supprime la list chrono
    deleteListChrono(&(*ft)->listFilmByChrono);
    //Puis les réalisateurs
    deleteRealisateurs(&(*ft)->r);
    free(*ft);
    *ft = NULL;
}

// Renvoie un fichier result.txt avec les Films cherché par auteur
void searchByAuthor(struct Filmotheque* ft, char* realisateur){

    // Vérifie qu'il n'y ait pas déjà un ready.txt pour que le client ne lise pas notre .txt en avance
    FILE* suppr;
    suppr = fopen("../html/ready.txt", "r");
    if(suppr != NULL){

        // On supprime en conséquence
        remove("../html/ready.txt");
        remove("../html/results.txt");
        fclose(suppr);
    }

    FILE* fichier;
    FILE* ready;

    // Création d'un fichier results.txt
    fichier = fopen("../html/results.txt", "w");

    // On vérifie que le réalisateur recherché existe
    if(isRealisateurExist(ft->r, realisateur)) {

        ///////////////////
        /* On recherche le réalisateur avec findRealisateur()
         * On récupère le temps à un instant t avec click()
         * puis on compare avant et après l'appel de la fonction pour obtenir à l'aide d'une soustraction
         * son temps de calcul */

        clock_t begin = clock();

        struct Realisateur *r = findRealisateur(ft->r, realisateur);

        clock_t end = clock();
        double time_spent = (double) (end - begin);
        time_spent = time_spent / CLOCKS_PER_SEC * 1000; //en microseconde;
        char temps[10];

        // Transforme un int en char*
        sprintf(temps, "%f", time_spent);
        strcat(temps, "\n"); // ajoute d'un \n
        fputs(temps, fichier); // puis écriture dans le fichier results.txt
        ///////////////////

        char texte[MAXAUTHOR + MAXTITLE + MAXTYPE] = {};
        struct Film *iter;
        int nb_film;

        // Vérification que le/les films de l'auteur existe
        if (r != NULL) {
            if (isRealisateur(r) && getFilm(r) != NULL) {
                iter = getFilm(r);
                nb_film = getsize(iter);

                // Pour chaque film, on récupère les informations souhaitées et on les ajoutes au txt
                for (int i = 0; i < nb_film; i++) {
                    strcat(texte, getAuthor(iter));
                    strcat(texte, ";");
                    strcat(texte, getTitle(iter));
                    strcat(texte, ";");
                    strcat(texte, getTime(iter));
                    strcat(texte, ";");
                    strcat(texte, getType(iter));
                    strcat(texte, "\n");
                    fputs(texte, fichier); // fonction pour ajouter le texte au txt
                    iter = getNext(iter); // passer au film suivant

                    // Réinitialisé le conteneur texte. (pour ne pas écrire à la suite de ce qui existe)
                    for (int lettre = 0; lettre < MAXAUTHOR + MAXTITLE + MAXTYPE; lettre++) {
                        texte[lettre] = '\0';
                    }
                }
            }
        }
    }
    // Si le réalisateur n'existe pas
    else {

        // écriture de "errorAuthor" dans le fichier avec le réalisateur qui n'a pas fonctionné
        char texte[50] = "errorAuthor;";
        strcat(texte, realisateur);
        fputs(texte, fichier);
    }

    // autorisé au javascript d'exploiter results.txt avec l'ajout de ready.txt
    fclose(fichier);
    ready = fopen("../html/ready.txt", "w");
    fclose(ready);

    // suppression de la demande pour ne pas l'analysé à nouveau
    remove("../html/request.txt");
}

// Renvoie un fichier result.txt avec les Films cherché pas temps
void searchByTime(struct Filmotheque* ft, int time){

    // Vérifie qu'il n'y ait pas déjà un ready.txt pour que le client ne lise pas notre .txt en avance
    FILE* suppr;
    suppr = fopen("../html/ready.txt", "r");
    if(suppr != NULL){

        // On supprime en conséquence
        remove("../html/ready.txt");
        remove("../html/results.txt");
        fclose(suppr);
    }

    FILE* fichier;
    FILE* ready;

    // Création d'un fichier results.txt
    fichier = fopen("../html/results.txt", "w");

    // Vérification que le/les films d'une durée donné exists (soit dans la liste et non null)
    if(getFilmByListChrono(ft, time) != NULL && ft->plusLongFilm > time) {

        ///////////////////
        /* On recherche le film voulu dans la list chrono
         * On récupère le temps à un instant t avec click()
         * puis on compare avant et après l'appel de la fonction pour obtenir à l'aide d'une soustraction
         * son temps de calcul */

        clock_t begin = clock();

        struct Film *f = getFilmByListChrono(ft, time);

        clock_t end = clock();
        double time_spent = (double) (end - begin);
        time_spent = time_spent / CLOCKS_PER_SEC * 1000; //en microseconde;
        char temps[10];
        sprintf(temps, "%f", time_spent); // Transforme un int en char*
        strcat(temps, "\n"); // ajoute d'un \n
        fputs(temps, fichier); // puis écriture dans le fichier results.txt
        ///////////////////

        char texte[MAXAUTHOR + MAXTITLE + MAXTYPE] = {};
        int nb_film = f->size;

        // Pour chaque film, on écrit les informations souhaitées dans le fichier.txt
        for (int i = 0; i < nb_film; i++) {
            strcat(texte, getAuthor(f));
            strcat(texte, ";");
            strcat(texte, getTitle(f));
            strcat(texte, ";");
            strcat(texte, getTime(f));
            strcat(texte, ";");
            strcat(texte, getType(f));
            strcat(texte, "\n");
            fputs(texte, fichier);
            f = getNext(f); // film suivant

            // Réinitialisation du conteneur
            for (int lettre = 0; lettre < MAXAUTHOR + MAXTITLE + MAXTYPE; lettre++) {
                texte[lettre] = '\0';
            }
        }
    }
    // Si le chrono demander n'existe pas
    else {

        // écriture dans le fichier de "errorTime" avec le temps qui n'a pas fonctionné
        char texte[50] = "errorTime;";
        char time_char[20];
        sprintf(time_char, "%d", time);
        strcat(texte, time_char);
        fputs(texte, fichier);
    }

    // autorisé au javascript d'exploiter results.txt avec l'ajout de ready.txt
    fclose(fichier);
    ready = fopen("../html/ready.txt", "w");
    fclose(ready);

    // suppression de la demande pour ne pas l'analysé à nouveau
    remove("../html/request.txt");
}

// Renvoie un fichier avec le meilleur Réalisateur
void searchBestAuthor(struct Filmotheque* ft){

    // Vérifie qu'il n'y ait pas déjà un ready.txt pour que le client ne lise pas notre .txt en avance
    FILE* suppr;
    suppr = fopen("../html/ready.txt", "r");
    if(suppr != NULL){

        // Supprime les fichiers en consequence s'il existe
        remove("../html/ready.txt");
        remove("../html/results.txt");
        fclose(suppr);
    }

    // Création d'un fichier results.txt
    FILE* fichier;
    FILE* ready;
    fichier = fopen("../html/results.txt", "w");

    ///////////////////
    /* On recherche le film voulu dans la list chrono
     * On récupère le temps à un instant t avec click()
     * puis on compare avant et après l'appel de la fonction pour obtenir à l'aide d'une soustraction
     * son temps de calcul */

    clock_t begin = clock();

    // récupération des deux informations
    char* best = getRealisateurProductif(ft);
    int nb_film = getMaxFilm(ft);

    clock_t end = clock();
    double time_spent = (double)(end - begin);
    time_spent = time_spent / CLOCKS_PER_SEC * 1000; //en microseconde;
    char temps[10];
    ///////////////////

    // Nombre de films du meilleur auteur
    char texte[MAXAUTHOR+5] = {};
    char nombre[5];
    sprintf(nombre, "%d", nb_film);

    // information supplémentaire écrite dans le fichier pour préciser le type de recherche
    char js_print[12] = "bestAuthor";
    strcat(js_print, "\n");
    fputs(js_print, fichier);

    // écriture du temps d'exécution de la fonction
    sprintf(temps, "%f", time_spent);
    strcat(temps, "\n");
    fputs(temps, fichier);

    // écriture du meilleur réalisateur avec son nombre de films
    strcat(texte, best);
    strcat(texte, ";");
    strcat(texte, nombre);
    fputs(texte, fichier);

    fclose(fichier);
    // autorisé au javascript d'exploiter results.txt avec l'ajout de ready.txt
    ready = fopen("../html/ready.txt", "w");
    fclose(ready);
    // suppression de la demande pour ne pas l'analysé à nouveau
    remove("../html/request.txt");
}