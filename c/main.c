#include "film.h"
#include "realisateur.h"

int main() {

    struct Realisateur* r = buildRealisateurFromtxt("../../../BD_test.txt");

    int index = 0;
    char rea[MAXAUTHOR];

    displayRealisateurs(r, rea, index);
}
