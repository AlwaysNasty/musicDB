#include "database.h"
#include "menu.h"

int main() {
    system("chcp 65001>nul");

    MusicDatabase db;
    init_database(&db);

    run_menu(&db);
    free_database(&db);
    return 0;
}