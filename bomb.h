#ifndef _BOMB_H
#define _BOMB_H

typedef struct s_character t_character;

typedef struct          s_bomb {
    int                 x;
    int                 y;
    unsigned int        timer;
    SDL_Rect            screen_position;
    SDL_Surface         *surface;
}                       t_bomb;

typedef struct          s_bomb_node {
    t_bomb              *bomb;
    struct s_bomb_node  *next;
}                       t_bomb_node;

typedef struct          s_args {
    int                 **map;
    t_bomb              *bomb;
}                       t_args;

t_bomb* create_bomb(int x, int y);
void add_bomb_to_list(t_bomb_node **bomb_list, int x, int y);
void draw_bombs_on_screen(SDL_Surface* screen, t_bomb_node **bomb_list, int **map);
int is_bomb_at_position(t_bomb_node* bomb_list, int x, int y);
void remove_bomb_by_index(t_bomb_node **head, int n);
void create_thread_args(int **map, t_bomb *bomb, t_args *args);
int draw_explosion_on_screen(t_args *args);

#endif