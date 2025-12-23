#ifndef MUSICDB_MENU_H
#define MUSICDB_MENU_H

#include "database.h"

void show_menu();

void run_menu(MusicDatabase* db);

void menu_add_song(MusicDatabase* db);
void menu_delete_song(MusicDatabase* db);
void menu_edit_song(const MusicDatabase* db);
void menu_print_all(const MusicDatabase* db);
void menu_sort(const MusicDatabase* db);
void menu_find(const MusicDatabase* db);
void menu_save_to_file(const MusicDatabase* db);
void menu_load_from_file(MusicDatabase* db);

#endif