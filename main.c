#include "database.h"
#include "menu.h"

int main() {
    MusicDatabase db;
    init_database(&db);

    run_menu(&db);
    free_database(&db);
    return 0;
}