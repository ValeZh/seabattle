#pragma once
#include "Forfirstclass.h"

#pragma warning( push )
#pragma warning( disable : 4996)

void printboard(int user = 1);
bool validate(int x, int y);
int put_ship(Ship* ship);
void random_ship(Ship* ship);
int put_opponent_ship(string& params, Ship* ship);
void empty_board();
void clean_board();
int shoot_ship(int x, int y, Ship* ship);
int end_game(Ship* ship);
void wait_enter();
bool xy_validate(char alf, int y);
int id_input(int armysize);
void validate_for_set(Ship* ships);
void play_validate(Bufferxy& bufxy);
int game_shoot(Bufferxy& bufxy, int shoot, int player = 5);

////////////////////////////////////f
// Game functions
////////////////////////////////////f

bool game_random(list<Ship*> ships);
bool game_coord(list<Ship*> ships);
bool game_infoship(list<Ship*> ships);
bool game_put1ship(list<Ship*> ships, int army_size);
bool game_rotate(list<Ship*> ships, int army_size);
bool game_share_to_opponent(list<Ship*> ships);
bool game_set_opose_ship(list<Ship*> oposite_ships);
bool game_random_opon(list<Ship*> oposite_ships);
bool game_setxy(Bufferxy& bufxy);
int game_find_op_ship(list<Ship*> oposite_ships, Bufferxy& bufxy);
int game_end(list<Ship*> oposite_ships);
bool game_put_ship_for2(list<Ship*> ships, int player);
void set_initial_ships(list<Ship*>& x);
void put_all_my_ships(list<Ship*> ships);
void set_oponent(list<Ship*> oposite_ships);
void change_allships(list<Ship*> ships, list<Ship*> oposite_ships, int army_size);
void for_one_comp(list<Ship*> ships, list<Ship*> oposite_ships, Bufferxy& bufxy);
void for_two_comp(list<Ship*> ships, list<Ship*> oposite_ships, Bufferxy& bufxy);
void play_with_different_comp(list<Ship*> ships, list<Ship*> oposite_ships, Bufferxy& bufxy);
