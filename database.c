#include "database.h"
#include <stdlib.h>
#include <stdio.h>

void init_database(MusicDatabase* db) {
    db->capacity = 10;
    db->count = 0;
    db->songs = (Song_t*)malloc(db->capacity * sizeof(Song_t));
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