#include "constants.h"
#include "bomb.h"

t_bomb* create_bomb(int x, int y)
{
	t_bomb *bomb = malloc(sizeof(*bomb));

	if (!bomb)
		error("Bomb create error");

    bomb->x = x;
    bomb->y = y;
    bomb->timer = SDL_GetTicks();
	bomb->screen_position.x = bomb->x * BLOCK_SIZE;
	bomb->screen_position.y = bomb->y * BLOCK_SIZE;
    bomb->surface = IMG_Load("assets/sprites/bomb.png");

	return bomb;
}

void add_bomb_to_list(t_bomb_node **bomb_list, int x, int y)
{
	t_bomb_node *new_node = malloc(sizeof(*new_node));
    t_bomb *new_bomb = create_bomb(x, y);

	new_node->bomb = new_bomb;
	new_node->next = *bomb_list;
	*bomb_list = new_node;
}

void remove_bomb_by_index(t_bomb_node **head, int n) {
    int i = 0;
    t_bomb_node *current = (*head);
    t_bomb_node *node_to_remove = NULL;

    if (n == 0) {
        free(*head);
        *head = NULL;
        return NULL;
    }

    for (i = 0; i < n - 1; i++)
        current = current->next;

    node_to_remove = current->next;
    current->next = node_to_remove->next;
    free(node_to_remove);
}

void draw_bombs_on_screen(SDL_Surface *screen, t_bomb_node **bomb_list)
{    
    int i = 0;
    t_bomb_node *current = *bomb_list;
    unsigned int currentTime = SDL_GetTicks();

    while (current != NULL) {
        SDL_BlitSurface(current->bomb->surface, NULL, screen, &current->bomb->screen_position);
        if (currentTime - current->bomb->timer > 2000) {
            remove_bomb_by_index(bomb_list, i);
        }
        current = current->next;
        i++;
    }
}

int is_bomb_at_position(t_bomb_node *bomb_list, int x, int y)
{
    if (bomb_list == NULL)
        return 0;
    
    t_bomb_node *current = bomb_list;

    while (current != NULL) {
        if (current->bomb->x == x && current->bomb->y == y)
            return 1;
        current = current->next;
    }
    free(current);

    return 0;  
}

