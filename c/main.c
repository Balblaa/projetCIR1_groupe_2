#include "filmotheque.h"
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/sysinfo.h>

int main() {

    bool stop = true;
    //création du temps de
    clock_t begin = clock();

    struct Filmotheque* ft = createFilmotheque("../BD_medium.txt");

    clock_t end = clock();
    double time_spent = (double)(end - begin);
    time_spent = time_spent / CLOCKS_PER_SEC * 1000; //en microseconde;

    printf("%f", time_spent);
    while(stop) {
        FILE *fichier;
        fichier = fopen("../html/request.txt", "r");
        //création des variables qui vont contenir les paramètres du fichier
        char nomFunction[30];
        char realisateur[MAXAUTHOR];
        char title[MAXTITLE];
        char type[MAXTYPE];
        char time[4];
        //si le fichier n'est pas vide
        if (fichier != NULL) {
            char requestStr[MAXAUTHOR + MAXTITLE + MAXTYPE + 30];
            //on récupère dans une chaine de caractère les éléments de la requête
            fgets(requestStr, MAXAUTHOR + MAXTYPE + MAXTITLE, fichier);
            //on sépare en deux la chaine de caractère
            int info = strlen(requestStr);
            int indexParam = 0;
            int counter = 0;
            for (int i = 0; i < info; i++) {
                if (requestStr[i] == ';') {
                    switch (counter) {
                        case 0:
                            nomFunction[indexParam] = '\0';
                            counter++;
                            indexParam = 0;
                            break;
                        case 1:
                            realisateur[indexParam] = '\0';
                            counter++;
                            indexParam = 0;
                            break;
                        case 2:
                            time[indexParam] = '\0';
                            counter++;
                            indexParam = 0;
                            break;
                    }
                }
                else {
                    switch (counter) {
                        case 0:
                            if (requestStr[i] >= 'A' && requestStr[indexParam] <= 'Z') {
                                nomFunction[indexParam] = requestStr[i] + 32;
                            } else {
                                nomFunction[indexParam] = requestStr[i];
                            }
                            indexParam++;
                            break;
                        case 1:
                            realisateur[indexParam] = requestStr[i];
                            indexParam++;
                            break;
                        case 2:
                            time[indexParam] = requestStr[i];
                            indexParam++;
                            break;
                        case 3:
                            type[indexParam] = requestStr[i];
                            indexParam++;
                            break;
                    }
                }
            }
            //si le nom de fonction en paramètre correspond au nom de fonction
            if (strcmp(nomFunction, "searchbyauthor") == 0) {
                searchByAuthor(ft, realisateur);
            }
            if (strcmp(nomFunction, "searchbytime") == 0) {
                searchByTime(ft, atoi(time));
            }
            //si le nom de la fonction de la requête est stopProcess, on arrête la recherche
            if (strcmp(nomFunction, "stopprocess") == 0) {
                stop = false;
            }

            fclose(fichier);
        }
    }
    //on supprime la structure
    deleteFilmothque(&ft);

}