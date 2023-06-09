#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "film.h"

int main() {
    struct Film* f = createFilm("rasta kekette", "humour", 95);
    addFilm(f, "le petit garcon au pyjama rayé", "humour", 150);
    addFilm(f, "le sang de dieu", "action", 69);
    addFilm(f, "alcoolisme", "drame", 78);
    addFilm(f, "les victoire de ssm", "horreur", 199);
    printFilm(f);
    printFilm(getFilmByType(f, "action"));
}
