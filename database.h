#ifndef MUSICDB_DATABASE_H
#define MUSICDB_DATABASE_H

typedef struct {
    char title[64];
    char author[64];
    char genre[64];
    unsigned int id;
    unsigned int year;
    unsigned int duration_sec;
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

void print_song(const Song_t* song);
void print_all(const MusicDatabase* db);

void sort_by_title(MusicDatabase* db);
void sort_by_author(MusicDatabase* db);
void sort_by_genre(MusicDatabase* db);

void search_songs(const MusicDatabase* db,
                  const char* key1,
                  const char* key2,
                  const char* key3);

#endif //MUSICDB_DATABASE_H