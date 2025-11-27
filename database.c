#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_database(MusicDatabase* db) {
    db->capacity = 10;
    db->count = 0;
    db->songs = (Song_t*)malloc(db->capacity * sizeof(Song_t));
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
        Song_t* temp = (Song_t*)realloc(db->songs, new_capacity * sizeof(Song_t));

        if (temp == NULL) {
            printf("Error, can't allocate memory!\n");
            return;
        }
        db->songs = temp;
        db->capacity = new_capacity;
    }
}

void add_song(MusicDatabase* db, Song_t song) {
    if (db == NULL) return;

    ensure_capacity(db);
    song.id = db->count + 1;
    db->songs[db->count++] = song;
}

void delete_song(MusicDatabase* db, const unsigned int id) {
    if (id == 0 || id > db->count) return;

    for (size_t i = id - 1; i < db->count - 1; i++) {
        db->songs[i] = db->songs[i + 1];
    }
    db->count--;
}

void edit_song(const MusicDatabase* db, const unsigned int id) {
    if (id == 0 || id > db->count) {
        printf("Error: Wrong id.\n");
        return;
    }

    Song_t* s = &db->songs[id - 1];

    printf("\nРедактирование песни (ID %u)\n", s->id);
    printf("1: Название:      %s\n", s->title);
    printf("2: Автор:         %s\n", s->author);
    printf("3: Жанр:          %s\n", s->genre);
    printf("4: Год:           %u\n", s->year);
    printf("5: Длительность:  %u сек\n", s->duration_sec);
    printf("0: Отмена\n");

    printf("Выберите поле для изменения: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    void input_string(char* buf, size_t size);

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
            printf("Отмена!\n");
            break;
        default:
            printf("Неверный выбор!\n");
    }
    printf("Изменения сохранены.\n");
}

void input_string(char* buf, const size_t size) {
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = 0;
}

void print_song(const Song_t* song) {
    if (song == NULL) return;

    printf("[ID: %u] %s — %s\n", song->id, song->title, song->author);
    printf("Жанр: %s\n", song->genre);
    printf("Год: %u\n", song->year);
    printf("Длительность: %u сек\n", song->duration_sec);
    printf("--------------------------------------\n");
}

void print_all(const MusicDatabase* db) {
    if (db == NULL || db->songs == 0) {
        printf("Error. Database is empty!\n");
        return;
    }

    printf("\n======== Содержимое фонотеки ========\n\n");
    for (int i = 0; i < db->count; i++) {
        print_song(&db->songs[i]);
    }

    printf("======== Конец списка ========\n");
}

