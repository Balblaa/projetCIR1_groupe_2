#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "film.h"
#include "realisateur.h"

int main() {


    struct Realisateur* r = createEmptyRealisateur();

    insertRealisateur(r, "bob");
    insertRealisateur(r, "michel");
    insertRealisateur(r, "sebastien");
    insertRealisateur(r, "boby");
    insertRealisateur(r, "bob-shamina");

    char mot[30];
    int index = 0;

    struct Film* a = createFilm("proutland", "prout", "michel", 75);
    struct Film* b = createFilm("underprout", "prout", "patrique", 300);
    struct Film* c = createFilm("Le pull perdu", "aventure", "moi", 160);
    struct Film* d = createFilm("poulpattack", "horreur", "lisa", 69);

    a = addFilm(a, b);
    a = addFilm(a, c);
    a = addFilm(a, d);

    printFilm(a);
    deleteFilmByTitle(a, "Le pull perdu");
    printFilm(a);
    deleteFilms(&a);
}
