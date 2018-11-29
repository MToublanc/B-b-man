#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "bomb.h"

typedef struct          s_character {
    int                 x;
    int                 y;
    int                 current_direction;
    int                 life;
    SDL_Rect            screen_position;
    SDL_Surface         **surface;
}                       t_character;

t_character* create_character(int x, int y);
void moveCharacter(int **map, t_character *character, t_bomb_node *bomb_list, int direction);
void draw_character_on_screen(SDL_Surface *screen, t_character *character, int **map);

#endif