#include "film.h"
#include "realisateur.h"

int main() {

    struct Realisateur* r = buildRealisateurFromtxt("../../../BD_medium.txt");

    int index = 0;
    char rea[MAXAUTHOR];

    displayRealisateurs(r, rea, index);
    printf("%d\n%s", bestRealisateur(r)->film->size, getAuthor(bestRealisateur(r)->film));
    deleteRealisateurs(&r);
}
