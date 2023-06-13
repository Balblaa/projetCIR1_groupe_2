#include <time.h>
#include "realisateur.h"
#include "filmotheque.h"
#include "listChrono.h"
#include "film.h"

// Operation de création de la filmotheque
struct Filmotheque* createFilmotheque(char* nomfichier){
    struct Filmotheque* ft = malloc(sizeof(struct Filmotheque));
    if(ft != NULL){

        ft->r = buildRealisateurFromtxt(nomfichier);

        struct Realisateur* best = bestRealisateur(ft->r);
        ft->maxFilm = best->film->size;
        strcpy(ft->realisateurProductif, best->film->author);
        ft->plusLongFilm = findlongestFilm(ft->r);

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

// Permet de rajouter un Film
void addNewFilm(struct Filmotheque* ft,char title[MAXTITLE], char type[MAXTYPE],char author[MAXAUTHOR], char* time){
    struct Film* f = createFilm(title, type, author, time);
    insertFilm(ft->r, f);
    ft->plusLongFilm = findlongestFilm(ft->r);
}

//affiche la structure
void printFilmotheque(struct Filmotheque* ft){
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

// Surpimer un film avec le nom du réalisateur et le titre
void deleteFilmFromFilmotheque(struct Filmotheque* ft, char* realisateur, char* title, int time){
    deleteFilmFromListChrono(ft->listFilmByChrono, time, title);
    deleteFilmFromRealisateur(ft->r, realisateur, title);
    struct Realisateur* best = bestRealisateur(ft->r);
    ft->maxFilm = best->film->size;
    strcpy(ft->realisateurProductif, best->film->author);
}

//supprimer la structure
void deleteFilmothque(struct Filmotheque** ft){
    deleteListChrono(&(*ft)->listFilmByChrono);
    deleteRealisateurs(&(*ft)->r);
    free(*ft);
    *ft = NULL;
}

// Renvoie un fichier result.txt avec les Films cherché par auteur
void searchByAuthor(struct Filmotheque* ft, char* realisateur){

    FILE* suppr;
    suppr = fopen("../html/ready.txt", "r");
    if(suppr != NULL){
        fclose(suppr);
        remove("../html/ready.txt");
        remove("../html/results.txt");
    }

    FILE* fichier;
    FILE* ready;
    fichier = fopen("../html/results.txt", "w");

    clock_t begin = clock();

    struct Realisateur* r = findRealisateur(ft->r, realisateur);

    clock_t end = clock();
    double time_spent = (double)(end - begin);
    time_spent = time_spent / CLOCKS_PER_SEC * 1000; //en microseconde;
    char temps[10];
    sprintf(temps, "%f", time_spent);
    strcat(temps, "\n");
    fputs(temps, fichier);

    char texte[
        MAXAUTHOR + MAXTITLE + MAXTYPE] = {};
    struct Film* iter;
    int nb_film;

    if(r != NULL) {
        if (isRealisateur(r) && r->film != NULL) {
            iter = r->film;
            nb_film = iter->size;
            for (int i = 0; i < nb_film; i++) {
                strcat(texte, getAuthor(iter));
                strcat(texte, ";");
                strcat(texte, getTitle(iter));
                strcat(texte, ";");
                strcat(texte, getTime(iter));
                strcat(texte, ";");
                strcat(texte, getType(iter));
                strcat(texte, "\n");
                fputs(texte, fichier);
                iter = iter->next;
                for (int lettre = 0; lettre < MAXAUTHOR + MAXTITLE + MAXTYPE; lettre++) {
                    texte[lettre] = '\0';
                }
            }
        }
    }

    fclose(fichier);
    ready = fopen("../html/ready.txt", "w");
    fclose(ready);
    remove("../html/request.txt");
}

// Renvoie un fichier result.txt avec les Films cherché pas temps
void searchByTime(struct Filmotheque* ft, int time){
    FILE* suppr;
    suppr = fopen("../html/ready.txt", "r");
    if(suppr != NULL){
        fclose(suppr);
        remove("../html/ready.txt");
        remove("../html/results.txt");
    }

    FILE* fichier;
    FILE* ready;
    fichier = fopen("../html/results.txt", "w");

    clock_t  begin = clock();

    struct Film* f = ft->listFilmByChrono->list[time-1];

    clock_t end = clock();
    double time_spent = (double)(end - begin);
    time_spent = time_spent / CLOCKS_PER_SEC * 1000; //en microseconde;
    char temps[10];
    sprintf(temps, "%f", time_spent);
    strcat(temps, "\n");
    fputs(temps, fichier);

    char texte[MAXAUTHOR + MAXTITLE + MAXTYPE] = {};
    int nb_film = f->size;

    for(int i=0; i<nb_film; i++){
        strcat(texte, getAuthor(f));
        strcat(texte, ";");
        strcat(texte, getTitle(f));
        strcat(texte, ";");
        strcat(texte, getTime(f));
        strcat(texte, ";");
        strcat(texte, getType(f));
        strcat(texte, "\n");
        fputs(texte, fichier);
        f = f->next;
        for(int lettre=0; lettre<MAXAUTHOR + MAXTITLE + MAXTYPE; lettre++){
            texte[lettre] = '\0';
        }
    }

    fclose(fichier);
    ready = fopen("../html/ready.txt", "w");
    fclose(ready);
    remove("../html/request.txt");
}

// Renvoie un fichier avec le meilleur Réalisateur
void searchBestAuthor(struct Filmotheque* ft){
    FILE* suppr;
    suppr = fopen("../html/ready.txt", "r");
    if(suppr != NULL){
        fclose(suppr);
        remove("../html/ready.txt");
        remove("../html/results.txt");
    }

    FILE* fichier;
    FILE* ready;
    fichier = fopen("../html/results.txt", "w");

    clock_t begin = clock();

    char* best = ft->realisateurProductif;
    int nb_film = ft->maxFilm;

    clock_t end = clock();
    double time_spent = (double)(end - begin);
    time_spent = time_spent / CLOCKS_PER_SEC * 1000; //en microseconde;
    char temps[10];

    char texte[MAXAUTHOR+5] = {};
    char nombre[5];
    sprintf(nombre, "%d", nb_film);

    char js_print[12] = "bestAuthor";
    strcat(js_print, "\n");
    fputs(js_print, fichier);

    sprintf(temps, "%f", time_spent);
    strcat(temps, "\n");
    fputs(temps, fichier);

    strcat(texte, best);
    strcat(texte, ";");
    strcat(texte, nombre);

    fputs(texte, fichier);

    fclose(fichier);

    ready = fopen("../html/ready.txt", "w");
    fclose(ready);
    remove("../html/request.txt");
}