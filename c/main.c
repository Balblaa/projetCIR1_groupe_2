#include "film.h"
#include "realisateur.h"
#include "filmotheque.h"

int main() {

    struct Filmotheque* ft = createFilmotheque("../../../BD_medium.txt");

    deleteFilmFromFilmotheque(ft, "leandron", "Joan of Arc of Dark Health");

    printFilmotheque(ft);
    deleteFilmothque(&ft);


    /*
    FILE* fichier;
    fichier = fopen("../../html/result.txt", "w");
    char texte[MAXAUTHOR + MAXTITLE + MAXTYPE] = "bien le bonsoir\n";
    fputs(texte, fichier);

    fclose(fichier);*/
}
