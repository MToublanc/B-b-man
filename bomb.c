#include "constants.h"
#include "bomb.h"

t_bomb* create_bomb(int x, int y)
{
	t_bomb *bomb = malloc(sizeof(*bomb));

	if (!bomb)
		error("Bomb create error");

    bomb->x = x;
    bomb->y = y;
	bomb->screen_position.x = bomb->x * BLOCK_SIZE;
	bomb->screen_position.y = bomb->y * BLOCK_SIZE;
    bomb->surface = IMG_Load("assets/sprites/bomb.png");

	return bomb;
}

t_bomb_node* add_bomb_to_list(t_bomb_node* bomb_list, int x, int y)
{
	t_bomb_node *new_node = malloc(sizeof(*new_node));
    t_bomb *new_bomb = create_bomb(x, y);

	new_node->bomb = new_bomb;
	new_node->next = bomb_list;
	bomb_list = new_node;

	return bomb_list;
}

void draw_bombs_on_screen(SDL_Surface* screen, t_bomb_node* bomb_list)
{
    t_bomb_node *current = bomb_list;

    while (current != NULL) {
        SDL_BlitSurface(current->bomb->surface, NULL, screen, &current->bomb->screen_position);
        current = current->next;
    }
    free(current);
}

int is_bomb_at_position(t_bomb_node *bomb_list, int x, int y)
{
    t_bomb_node *current = bomb_list;

    while (current != NULL) {
        if (current->bomb->x == x && current->bomb->y == y)
            return 1;
        current = current->next;
    }

    free(current);
    return 0;  
}

