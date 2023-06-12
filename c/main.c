#include "filmotheque.h"
#include <time.h>
#include <unistd.h>

int main() {
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
    return time_spent;
    struct Filmotheque* ft = createFilmotheque("../../BD_medium.txt");
    printFilmotheque(ft);
    deleteFilmothque(&ft);


    /*
    FILE* fichier;
    fichier = fopen("../../html/result.txt", "w");
    char texte[MAXAUTHOR + MAXTITLE + MAXTYPE] = "bien le bonsoir\n";
    fputs(texte, fichier);

    fclose(fichier);*/
}
