#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_database(MusicDatabase* db) {
    db->capacity = 10;
    db->count = 0;
    db->songs = malloc(db->capacity * sizeof(Song_t));
}

void free_database(MusicDatabase* db) {
    if (db == NULL) return;

    free(db->songs);
    db->songs = NULL;
    db->count = 0;
    db->capacity = 0;
}

void ensure_capacity(MusicDatabase* db) {
    if (db->count >= db->capacity) {
        const int new_capacity = db->capacity * 2;
        Song_t* temp = realloc(db->songs, new_capacity * sizeof(Song_t));

        if (!temp) {
            printf("Ошибка выделения памяти!\n");
            return;
        }

        db->songs = temp;
        db->capacity = new_capacity;
    }
}

void add_song(MusicDatabase* db, Song_t song) {
    ensure_capacity(db);
    song.id = db->count + 1;
    db->songs[db->count++] = song;
}

void delete_song(MusicDatabase* db, const unsigned int id) {
    if (id == 0 || id > db->count) return;

    for (int i = id - 1; i < db->count - 1; i++) {
        db->songs[i] = db->songs[i + 1];
    }

    db->count--;
}

void edit_song(const MusicDatabase* db, const unsigned int id) {
    if (id == 0 || id > db->count) {
        printf("Ошибка: неверный ID!\n");
        return;
    }

    Song_t* s = &db->songs[id - 1];

    printf("\nРедактирование песни (ID %u)\n", s->id);
    printf("1 — Название:      %s\n", s->title);
    printf("2 — Автор:         %s\n", s->author);
    printf("3 — Жанр:          %s\n", s->genre);
    printf("4 — Год:           %u\n", s->year);
    printf("5 — Длительность:  %u сек\n", s->duration_sec);
    printf("0 — Отмена\n");

    printf("Ваш выбор: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1:
            printf("Новое название: ");
            input_string(s->title, sizeof(s->title));
            break;
        case 2:
            printf("Новый автор: ");
            input_string(s->author, sizeof(s->author));
            break;
        case 3:
            printf("Новый жанр: ");
            input_string(s->genre, sizeof(s->genre));
            break;
        case 4:
            printf("Новый год: ");
            scanf("%u", &s->year);
            getchar();
            break;
        case 5:
            printf("Новая длительность: ");
            scanf("%u", &s->duration_sec);
            getchar();
            break;
        case 0:
            printf("Отмена.\n");
            return;
        default:
            printf("Неверный выбор!\n");
            return;
    }

    printf("Изменения сохранены.\n");
}

void input_string(char* buf, const size_t size) {
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = 0;
}

void print_song(const Song_t* song) {
    printf("[ID %u] %s — %s\n", song->id, song->title, song->author);
    printf("Жанр: %s | Год: %u | Длительность: %u сек\n",
           song->genre, song->year, song->duration_sec);
    printf("--------------------------------------\n");
}

void print_all(const MusicDatabase* db) {
    if (!db || db->count == 0) {
        printf("База данных пуста.\n");
        return;
    }

    printf("\n======= Список песен =======\n\n");

    for (int i = 0; i < db->count; i++)
        print_song(&db->songs[i]);

    printf("======= Конец списка =======\n");
}

// Сортировки
int compare_title(const void* a, const void* b) {
    return strcmp(((Song_t*)a)->title, ((Song_t*)b)->title);
}
int compare_author(const void* a, const void* b) {
    return strcmp(((Song_t*)a)->author, ((Song_t*)b)->author);
}

int compare_genre(const void* a, const void* b) {
    return strcmp(((Song_t*)a)->genre, ((Song_t*)b)->genre);
}
void sort_by_title(const MusicDatabase* db) {
    qsort(db->songs, db->count, sizeof(Song_t), compare_title);
}

void sort_by_author(const MusicDatabase* db) {
    qsort(db->songs, db->count, sizeof(Song_t), compare_author);
}
void sort_by_genre(const MusicDatabase* db) {
    qsort(db->songs, db->count, sizeof(Song_t), compare_genre);
}

// Сохранение базы в файл (txt)
void save_to_file(const MusicDatabase* db, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Ошибка: не удалось открыть файл!\n");
        return;
    }

    for (int i = 0; i < db->count; i++) {
        const Song_t* s = &db->songs[i];
        fprintf(f, "%u;%s;%s;%s;%u;%u\n",
                s->id, s->title, s->author, s->genre, s->year, s->duration_sec);
    }

    fclose(f);
    printf("База сохранена в файл: %s\n", filename);
}

void load_from_file(MusicDatabase* db, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Ошибка: не удалось открыть файл %s!\n", filename);
        return;
    }

    char line[256];

    db->count = 0;  // перезаписываем базу

    while (fgets(line, sizeof(line), f)) {
        Song_t s;
        char title[64], author[64], genre[64];
        unsigned int id, year, duration;

        // формат строки:
        // id;title;author;genre;year;duration
        if (sscanf(line, "%u;%63[^;];%63[^;];%63[^;];%u;%u",
                   &id, title, author, genre, &year, &duration) == 6)
        {
            strncpy(s.title, title, sizeof(s.title));
            strncpy(s.author, author, sizeof(s.author));
            strncpy(s.genre, genre, sizeof(s.genre));
            s.year = year;
            s.duration_sec = duration;
            s.id = db->count + 1;

            add_song(db, s);
        }
    }

    fclose(f);
    printf("База успешно загружена из файла: %s\n", filename);
}

void search_songs(const MusicDatabase* db,
                  const char* key1,
                  const char* key2,
                  const char* key3)
{
    if (!db || db->count == 0) {
        printf("База данных пуста.\n");
        return;
    }

    printf("\n===== Результаты поиска =====\n\n");

    int found = 0;

    for (int i = 0; i < db->count; i++) {
        const Song_t* s = &db->songs[i];

        int ok = 1;

        // Проверки только если ключи не пустые
        if (key1 && strlen(key1) > 0) {
            if (!strstr(s->title, key1) &&
                !strstr(s->author, key1) &&
                !strstr(s->genre, key1))
                ok = 0;
        }

        if (key2 && strlen(key2) > 0) {
            if (!strstr(s->title, key2) &&
                !strstr(s->author, key2) &&
                !strstr(s->genre, key2))
                ok = 0;
        }

        if (key3 && strlen(key3) > 0) {
            if (!strstr(s->title, key3) &&
                !strstr(s->author, key3) &&
                !strstr(s->genre, key3))
                ok = 0;
        }

        if (ok) {
            print_song(s);
            found = 1;
        }
    }

    if (!found) printf("Ничего не найдено.\n");

    printf("===== Конец поиска =====\n");
}
