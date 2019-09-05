#include "constants.h"
#include "bomb.h"
#include "character.h"

void create_thread_args(int **map, t_bomb *bomb, t_args *args)
{
    args->map = map;
    args->bomb = bomb;
}

t_bomb* create_bomb(int x, int y)
{
	t_bomb *bomb = malloc(sizeof(*bomb));
    Mix_Chunk *drop = NULL;
   
    drop = Mix_LoadWAV( "assets/son/drop_bomb.wav" );
    Mix_PlayChannel(1, drop, 0);
	if (!bomb)
		error("Bomb create error");

    bomb->x = x;
    bomb->y = y;
    bomb->timer = SDL_GetTicks();
	bomb->screen_position.x = bomb->x * BLOCK_SIZE;
	bomb->screen_position.y = bomb->y * BLOCK_SIZE;
    bomb->surface = IMG_Load("assets/sprites/bomb.png");

	return bomb;
    Mix_FreeChunk(drop);
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

void set_sprites_for_explosion(t_args *args, int sprite)
{
    args->map[args->bomb->y][args->bomb->x] = sprite;
    if (args->map[args->bomb->y - 1][args->bomb->x] != SOLID_BLOCK)
        args->map[args->bomb->y - 1][args->bomb->x] = sprite;
    if (args->map[args->bomb->y + 1][args->bomb->x] != SOLID_BLOCK)
        args->map[args->bomb->y + 1][args->bomb->x] = sprite;
    if (args->map[args->bomb->y][args->bomb->x + 1] != SOLID_BLOCK)
        args->map[args->bomb->y][args->bomb->x + 1] = sprite;
    if (args->map[args->bomb->y][args->bomb->x - 1] != SOLID_BLOCK)
        args->map[args->bomb->y][args->bomb->x - 1] = sprite;
}

int draw_explosion_on_screen(t_args *args)
{
    int i = 0, j = 0;
    unsigned int currentTime = 0, prevTime = SDL_GetTicks();
    Mix_Chunk *explosion = NULL;
    explosion = Mix_LoadWAV( "assets/son/explosion_bomb.wav" );
    set_sprites_for_explosion(args, FLAMES);

    while (true)
    {
        currentTime = SDL_GetTicks();
        if ((currentTime - prevTime) > 500) {
            set_sprites_for_explosion(args, EMPTY);
            free(args);
            Mix_PlayChannel(-1, explosion, 0);
            return 1;
            Mix_FreeChunk(explosion);
        }
    }

    return 0;
}

void draw_bombs_on_screen(SDL_Surface *screen, t_bomb_node **bomb_list, int **map)
{    
    int i = 0;
    t_bomb_node *current = *bomb_list;
    unsigned int currentTime = SDL_GetTicks();
    SDL_Thread *thread = NULL;
    t_args *args = malloc(sizeof(*args));

    while (current != NULL)
    {
        SDL_BlitSurface(current->bomb->surface, NULL, screen, &current->bomb->screen_position);
        if (currentTime - current->bomb->timer > 2000) {
            create_thread_args(map, current->bomb, args);
            thread = SDL_CreateThread(draw_explosion_on_screen, args);
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

