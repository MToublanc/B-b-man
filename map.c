#include "constants.h"
#include "map.h"

// int map_view[NB_BLOCK_WIDTH][NB_BLOCK_HEIGHT] = {
//     {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
//     {2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2},
//     {2, 1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1, 2},
//     {2, 0, 2, 1, 0, 1, 1, 1, 1, 0, 1, 2, 0, 2},
//     {2, 1, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 1, 2},
//     {2, 1, 1, 1, 2, 0, 1, 1, 0, 2, 1, 1, 1, 2},
//     {2, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 2},
//     {2, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 2},
//     {2, 1, 1, 1, 2, 0, 1, 1, 0, 2, 1, 1, 1, 2},
//     {2, 1, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 1, 2},
//     {2, 0, 2, 1, 0, 1, 1, 1, 1, 0, 1, 2, 0, 2},
//     {2, 1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1, 2},
//     {2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2},
//     {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
// };

int **load_map()
{
    FILE *file = NULL;
    char *line = NULL;
    int **map = NULL;
    int i = 0, j = 0;

    map = malloc(NB_BLOCK_WIDTH * sizeof(int *));
    for (i = 0; i < NB_BLOCK_WIDTH; i++) 
        map[i] = malloc(NB_BLOCK_HEIGHT * sizeof(int));

    file = fopen("lvl.txt", "r");

    line = malloc(NB_BLOCK_WIDTH * NB_BLOCK_HEIGHT + 1 * sizeof(char));

    if (file == NULL || map == NULL || line == NULL)
        exit(EXIT_FAILURE);

    fgets(line, NB_BLOCK_WIDTH * NB_BLOCK_HEIGHT + 1, file);

    for (i = 0 ; i < NB_BLOCK_WIDTH ; i++)
    {
        for (j = 0 ; j < NB_BLOCK_HEIGHT ; j++)
        {
            switch (line[(i * NB_BLOCK_WIDTH) + j])
            {
                case '0':
                    map[i][j] = 0;
                    break;
                case '1':
                    map[i][j] = 1;
                    break;
                case '2':
                    map[i][j] = 2;
                    break;
            }
        }
    }
    fclose(file);

    return map;
}

void draw_map(int **map, SDL_Surface *screen)
{
    int i, j;
    SDL_Rect position;
    SDL_Surface *explodable_block = NULL, *empty = NULL, *solid_block = NULL;

    explodable_block = IMG_Load("assets/sprites/explodable-block.png");
    empty = IMG_Load("assets/sprites/empty.png");
    solid_block = IMG_Load("assets/sprites/solid-block.png");

    for (i = 0 ; i < NB_BLOCK_WIDTH ; i++)
    {
        for (j = 0 ; j < NB_BLOCK_HEIGHT ; j++)
        {
            position.x = j * BLOCK_SIZE;
            position.y = i * BLOCK_SIZE;

            switch(map[i][j])
            {
                case EXPLODABLE_BLOCK:
                    SDL_BlitSurface(explodable_block, NULL, screen, &position);
                    break;
                case EMPTY:
                    SDL_BlitSurface(empty, NULL, screen, &position);
                    break;
                case SOLID_BLOCK:
                    SDL_BlitSurface(solid_block, NULL, screen, &position);
                    break;
            }
        }
    }
}

void free_map(int **map)
{
    int i = 0;
    for (i = 0; i < NB_BLOCK_WIDTH; i++)
       free(map[i]);   
    free(map);
}