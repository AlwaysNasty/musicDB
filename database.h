#ifndef MUSICDB_DATABASE_H
#define MUSICDB_DATABASE_H

#include <stdlib.h>

typedef struct {
    char title[64];
    char author[64];
    char genre[64];
    unsigned int id;
} Song_t;

typedef struct {
    Song_t *songs;
    int count;
    int capacity;
} MusicDatabase;

void init_database(MusicDatabase* db);
void free_database(MusicDatabase* db);

void ensure_capacity(MusicDatabase* db);

void add_song(MusicDatabase* db, Song_t song);
void delete_song(MusicDatabase* db, unsigned int id);
void edit_song(const MusicDatabase* db, unsigned int id);

void input_string(char* buf, size_t size);
void print_song(const Song_t* song);
void print_all(const MusicDatabase* db);

int compare_title (const void* a, const void* b);
int compare_author (const void* a, const void* b);
int compare_genre (const void* a, const void* b);
void sort_by_title(const MusicDatabase* db);
void sort_by_author(const MusicDatabase* db);
void sort_by_genre(const MusicDatabase* db);

void save_to_file(const MusicDatabase* db, const char* filename);
void load_from_file(MusicDatabase* db, const char* filename);

void search_songs(const MusicDatabase* db,
                  const char* key1,
                  const char* key2,
                  const char* key3);

#endif //MUSICDB_DATABASE_H