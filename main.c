#include "database.h"
#include "menu.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    MusicDatabase db;
    init_database(&db);

    run_menu(&db);
    free_database(&db);
    return 0;
}