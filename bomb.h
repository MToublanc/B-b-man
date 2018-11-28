#ifndef _BOMB_H
#define _BOMB_H

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

t_bomb* create_bomb(int x, int y);
void add_bomb_to_list(t_bomb_node **bomb_list, int x, int y);
void draw_bombs_on_screen(SDL_Surface* screen, t_bomb_node **bomb_list);
int is_bomb_at_position(t_bomb_node* bomb_list, int x, int y);
void remove_bomb_by_index(t_bomb_node **head, int n);

#endif