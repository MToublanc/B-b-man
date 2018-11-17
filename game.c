#include "constants.h"
#include "game.h"

void game(SDL_Surface* screen)
{
    SDL_Surface *bomberman[4] = {NULL};
    SDL_Surface *explodable_block = NULL, *empty = NULL, *solid_block = NULL, *currentBMan = NULL;
    SDL_Rect position, playerPosition;
    SDL_Event event;

    int playing = 1, i = 0, j = 0;
    int map[NB_BLOCK_WIDTH][NB_BLOCK_HEIGHT] = {
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2},
        {2, 1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1, 2},
        {2, 0, 2, 1, 0, 1, 1, 1, 1, 0, 1, 2, 0, 2},
        {2, 1, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 1, 2},
        {2, 1, 1, 1, 2, 0, 1, 1, 0, 2, 1, 1, 1, 2},
        {2, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 2},
        {2, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 2},
        {2, 1, 1, 1, 2, 0, 1, 1, 0, 2, 1, 1, 1, 2},
        {2, 1, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 1, 2},
        {2, 0, 2, 1, 0, 1, 1, 1, 1, 0, 1, 2, 0, 2},
        {2, 1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1, 2},
        {2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
        };

    explodable_block = IMG_Load("assets/sprites/explodable-block.png");
    empty = IMG_Load("assets/sprites/empty.png");
    solid_block = IMG_Load("assets/sprites/solid-block.png");
    bomberman[DOWN] = IMG_Load("assets/sprites/bman-front.png");
    bomberman[LEFT] = IMG_Load("assets/sprites/bman-left.png");
    bomberman[UP] = IMG_Load("assets/sprites/bman-back.png");
    bomberman[RIGHT] = IMG_Load("assets/sprites/bman-right.png");

    currentBMan = bomberman[DOWN];

    playerPosition.x = 4;
    playerPosition.y = 1;

    while (playing)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                playing = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        playing = 0;
                        break;
                    case SDLK_UP:
                        currentBMan = bomberman[UP];
                        moveCharacter(map, &playerPosition, UP);
                        break;
                    case SDLK_DOWN:
                        currentBMan = bomberman[DOWN];
                        moveCharacter(map, &playerPosition, DOWN);
                        break;
                    case SDLK_RIGHT:
                        currentBMan = bomberman[RIGHT];
                        moveCharacter(map, &playerPosition, RIGHT);
                        break;
                    case SDLK_LEFT:
                        currentBMan = bomberman[LEFT];
                        moveCharacter(map, &playerPosition, LEFT);
                        break;
                }
                break;
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

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
        position.x = playerPosition.x * BLOCK_SIZE;
        position.y = playerPosition.y * BLOCK_SIZE - BLOCK_SIZE;
        SDL_BlitSurface(currentBMan, NULL, screen, &position);
        SDL_Flip(screen);
    }
    for (i = 0 ; i < 4 ; i++)
        SDL_FreeSurface(bomberman[i]);
    SDL_FreeSurface(explodable_block);
    SDL_FreeSurface(empty);
    SDL_FreeSurface(solid_block);
}

void moveCharacter(int map[][NB_BLOCK_HEIGHT], SDL_Rect *pos, int direction)
{
    switch(direction)
    {
        case UP:
            if ((pos->y - 1 < 0) || (map[pos->y - 1][pos->x] != EMPTY))
                break;
            pos->y--;
            break;

        case DOWN:
            if ((pos->y + 1 >= NB_BLOCK_HEIGHT) || (map[pos->y + 1][pos->x] != EMPTY))
                break;
            pos->y++;
            break;

        case LEFT:
            if ((pos->x - 1 < 0) || (map[pos->y][pos->x - 1] != EMPTY))
                break;
            pos->x--;
            break;

        case RIGHT:
            if ((pos->x + 1 >= NB_BLOCK_WIDTH) || (map[pos->y][pos->x + 1] != EMPTY))
                break;
            pos->x++;
            break;
    }
}
