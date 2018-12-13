#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "bomb.h"
#include "socket.h"

#include "constants.h"

typedef struct              s_character {
    int                     x;
    int                     y;
    int                     current_direction;
    int                     life;
    SDL_Rect                screen_position;
    SDL_Surface             **surface;
}                           t_character;

typedef struct              s_character_node {
    t_character             *character;
    struct s_character_node *next;
}                           t_character_node;

t_character* create_character(int x, int y);
void moveCharacter(int **map, t_character *character, t_bomb_node *bomb_list, int direction);
void draw_characters_on_screen(SDL_Surface *screen, t_character_node **character_list, int **map);
//void moveCharacterTCP(int **map, t_player_infos *character, t_bomb_node *bomb_list, int direction);
//void draw_characters_on_screenTCP(SDL_Surface *screen, t_character_node **character_list, int **map, t_game *game, int test);
void add_character_to_list(t_character **character_list, int x, int y);

#endif