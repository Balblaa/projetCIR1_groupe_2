#include "film.h"
#include "realisateur.h"
#include "filmotheque.h"

int main() {

    struct Filmotheque* ft = createFilmotheque("../../../BD_medium.txt");

    printFilmotheque(ft);
    printFilm(getFilmByListChrono(ft, 341));
    deleteFilmothque(&ft);


    /*
    FILE* fichier;
    fichier = fopen("../../html/result.txt", "w");
    char texte[MAXAUTHOR + MAXTITLE + MAXTYPE] = "bien le bonsoir\n";
    fputs(texte, fichier);

    fclose(fichier);*/
}
