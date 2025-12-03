#include <stdio.h>
#include "menu.h"
#include "database.h"

void show_menu() {
    printf("\n====== Ф О Н О Т Е К А ======\n");
    printf("1 — Добавить песню\n");
    printf("2 — Удалить песню\n");
    printf("3 — Редактировать песню\n");
    printf("4 — Показать все песни\n");
    printf("5 — Сортировка\n");
    printf("6 — Сохранить базу в файл\n");
    printf("7 — Поиск песен\n");
    printf("8 — Загрузить базу из файла\n");
    printf("0 — Выход\n");
    printf("==============================\n");
    printf("Ваш выбор: ");
}


void menu_add_song(MusicDatabase* db) {
    Song_t s;

    printf("\nДобавление песни:\n");
    printf("Название: ");
    input_string(s.title, sizeof(s.title));

    printf("Автор: ");
    input_string(s.author, sizeof(s.author));

    printf("Жанр: ");
    input_string(s.genre, sizeof(s.genre));

    printf("Год: ");
    scanf("%u", &s.year);
    getchar();

    printf("Длительность (сек): ");
    scanf("%u", &s.duration_sec);
    getchar();

    add_song(db, s);
    printf("Песня добавлена!\n");
}

void menu_delete_song(MusicDatabase* db) {
    printf("Введите ID: ");
    unsigned id;
    scanf("%u", &id);
    getchar();
    delete_song(db, id);
}

void menu_edit_song(MusicDatabase* db) {
    printf("Введите ID: ");
    unsigned id;
    scanf("%u", &id);
    getchar();
    edit_song(db, id);
}

void menu_print_all(const MusicDatabase* db) {
    print_all(db);
}

void menu_sort(MusicDatabase* db) {
    printf("\n----- Сортировка -----\n");
    printf("1 — По названию\n");
    printf("2 — По автору\n");
    printf("3 — По жанру\n");
    printf("0 — Назад\n");
    printf("Ваш выбор: ");

    int c;
    scanf("%d", &c);
    getchar();

    switch (c) {
        case 1: sort_by_title(db); break;
        case 2: sort_by_author(db); break;
        case 3: sort_by_genre(db); break;
        case 0: return;
        default: printf("Неверный пункт!\n");
    }

    printf("Готово.\n");
}

void menu_save_to_file(const MusicDatabase* db) {
    char fname[128];

    printf("Введите имя файла (например: songs.txt): ");
    input_string(fname, sizeof(fname));

    save_to_file(db, fname);
}

void menu_load_from_file(MusicDatabase* db) {
    char fname[128];

    printf("Введите имя файла (например songs.txt): ");
    input_string(fname, sizeof(fname));

    load_from_file(db, fname);
}

void menu_find(MusicDatabase* db) {
    char key1[64], key2[64], key3[64];

    printf("\n===== Поиск песен =====\n");
    printf("Введите ключ №1 (или оставьте пустым): ");
    input_string(key1, sizeof(key1));

    printf("Введите ключ №2 (или оставьте пустым): ");
    input_string(key2, sizeof(key2));

    printf("Введите ключ №3 (или оставьте пустым): ");
    input_string(key3, sizeof(key3));

    search_songs(db, key1, key2, key3);
}

void run_menu(MusicDatabase* db) {
    while (1) {
        show_menu();
        int cmd;
        scanf("%d", &cmd);
        getchar();

        switch (cmd) {
            case 1: menu_add_song(db); break;
            case 2: menu_delete_song(db); break;
            case 3: menu_edit_song(db); break;
            case 4: menu_print_all(db); break;
            case 5: menu_sort(db); break;
            case 6: menu_save_to_file(db); break;
            case 7: menu_find(db); break;
            case 8: menu_load_from_file(db); break;
            case 0: printf("Выход.\n"); return;
            default: printf("Неверный пункт меню!\n");
        }
    }
}