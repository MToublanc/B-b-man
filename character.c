#include "constants.h"
#include "character.h"
#include "bomb.h"

t_character* create_character(int x, int y)
{
	t_character *character = malloc(sizeof(*character));

	if (!character)
		error("Character create error");

    character->x = x;
    character->y = y;
    character->current_direction = DOWN;
	character->screen_position.x = character->x * BLOCK_SIZE;
	character->screen_position.y = character->y * BLOCK_SIZE - BLOCK_SIZE;
    character->surface = malloc(sizeof(SDL_Surface*) * 4);
    character->surface[DOWN] = IMG_Load("assets/sprites/bman-front.png");
    character->surface[LEFT] = IMG_Load("assets/sprites/bman-left.png");
    character->surface[UP] = IMG_Load("assets/sprites/bman-back.png");
    character->surface[RIGHT] = IMG_Load("assets/sprites/bman-right.png");

	return character;
}

void moveCharacter(int **map, t_character *character, t_bomb_node *bomb_list, int direction)
{
    switch(direction)
    {
        case UP:
            character->current_direction = UP;
            if ((character->y - 1 < 0) || (map[character->y - 1][character->x] != EMPTY))
                break;
            else if (is_bomb_at_position(bomb_list, character->x, character->y - 1))
                break;
            character->y--;
            character->screen_position.y = character->y * BLOCK_SIZE - BLOCK_SIZE;
            break;

        case DOWN:
            character->current_direction = DOWN;
            if ((character->y + 1 >= NB_BLOCK_HEIGHT) || (map[character->y + 1][character->x] != EMPTY))
                break;
            else if (is_bomb_at_position(bomb_list, character->x, character->y + 1))
                break;
            character->y++;
            character->screen_position.y = character->y * BLOCK_SIZE - BLOCK_SIZE;
            break;

        case LEFT:
            character->current_direction = LEFT;
            if ((character->x - 1 < 0) || (map[character->y][character->x - 1] != EMPTY))
                break;
            else if (is_bomb_at_position(bomb_list, character->x - 1, character->y))
                break;
            character->x--;
            character->screen_position.x = character->x * BLOCK_SIZE;
            break;

        case RIGHT:
            character->current_direction = RIGHT;
            if ((character->x + 1 >= NB_BLOCK_WIDTH) || (map[character->y][character->x + 1] != EMPTY))
                break;
            else if (is_bomb_at_position(bomb_list, character->x + 1, character->y))
                break;
            character->x++;
            character->screen_position.x = character->x * BLOCK_SIZE;
            break;
    }
}