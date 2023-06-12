#include "filmotheque.h"
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

int main() {
    bool stop = true;
    //création du temps de
    double time_spent = 0.0;
    clock_t begin = clock();
    //mettre le code à éxecuter
    for (int i = 0; i < 100000; ++i) {
        int e=e+i;
    }
    clock_t end = clock();
    time_spent += (double)(end - begin);
    time_spent=time_spent/10000;
    // return time_spent;

    struct Filmotheque* ft = createFilmotheque("../../BD_medium.txt");

    FILE *fichier;
    while(stop) {
        fichier = fopen("../html/request.txt", "r");
        int index;
        char nomFunction[30];
        char nomParametre[MAXAUTHOR + MAXTITLE + MAXTYPE];
        if (fichier != NULL) {
            char requestStr[MAXAUTHOR + MAXTITLE + MAXTYPE + 30];
            fgets(requestStr, MAXAUTHOR + MAXTYPE + MAXTITLE, fichier);
            for (int i = 0; i < strlen(requestStr); i++) {
                if (requestStr[i] == ';') {
                    index = i;
                }
            }
            for (int j = 0; j < index; j++) {
                nomFunction[j] = requestStr[j];
            }
            for (int k = 1; k < strlen(requestStr); k++) {
                nomParametre[k - 1] = requestStr[k + index];
            }
            if (strcmp(nomFunction, "searchByAuthor") == 0) {
                searchByAuthor(ft, nomParametre);
            }
            if (strcmp(nomFunction, "searchByTime") == 0) {
                searchByTime(ft, atoi(nomParametre));
            }
            if (strcmp(nomFunction, "stopProcess") == 0){
                stop = false;
            }
            fclose(fichier);
        }
    }

    deleteFilmothque(&ft);

}