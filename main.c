#include "database.h"
#include "menu.h"

int main() {
    MusicDatabase db;
    init_database(&db);


    free_database(&db);
    return 0;
}