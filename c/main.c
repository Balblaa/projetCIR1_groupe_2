#include "filmotheque.h"

int main() {

    struct Filmotheque* ft = createFilmotheque("../../BD_medium.txt");

    searchByAuthor(ft, "leandron");

    deleteFilmothque(&ft);
}
