#include "filmotheque.h"
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/sysinfo.h>

int main() {

    bool stop = true;

    struct Filmotheque* ft = createFilmotheque("../BD_medium.txt");
    remove("../html/request.txt");

    while(stop) {
        FILE *fichier;
        fichier = fopen("../html/request.txt", "r");
        //création des variables qui vont contenir les paramètres du fichier
        char nomFunction[30];
        char realisateur[MAXAUTHOR];
        char time[4];
        //si le fichier n'est pas vide
        if (fichier != NULL) {
            char requestStr[MAXAUTHOR + 30];
            //on récupère dans une chaine de caractère les éléments de la requête
            fgets(requestStr, MAXAUTHOR + 30, fichier);
            strcat(requestStr, ";");
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
            if (strcmp(nomFunction, "searchbestauthor") == 0) {
                searchBestAuthor(ft);
            }
            //si le nom de la fonction de la requête est stopProcess, on arrête la recherche
            if (strcmp(nomFunction, "stopprocess") == 0) {
                stop = false;
                remove("../html/request.txt");
                FILE* suppr;
                suppr = fopen("../html/ready.txt", "r");
                if(suppr != NULL){
                    fclose(suppr);
                    remove("../html/ready.txt");
                    remove("../html/results.txt");
                }
            }

            fclose(fichier);
        }
    }
    //on supprime la structure
    deleteFilmothque(&ft);

}