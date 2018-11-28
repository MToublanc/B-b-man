#include "constants.h"
#include "game.h"
#include "bomb.h"
#include "character.h"
#include "map.h"

void game(SDL_Surface *screen)
{
    SDL_Event event;
    int playing = 1, i = 0, j = 0;
    int **map = load_map();

    t_bomb_node *bomb_list = NULL;
    t_character *character = create_character(4, 1);

    if (!map)
        exit(EXIT_FAILURE);

    while (playing)
    {
        while (SDL_PollEvent(&event))
        {
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
                            moveCharacter(map, character, bomb_list, UP);
                            break;
                        case SDLK_DOWN:
                            moveCharacter(map, character, bomb_list, DOWN);
                            break;
                        case SDLK_RIGHT:
                            moveCharacter(map, character, bomb_list, RIGHT);
                            break;
                        case SDLK_LEFT:
                            moveCharacter(map, character, bomb_list, LEFT);
                            break;
                        case SDLK_SPACE:
                            add_bomb_to_list(&bomb_list, character->x, character->y);
                            break;
                    }
                    break;
            }
        }
        draw_map(map, screen);
        draw_bombs_on_screen(screen, &bomb_list);
        SDL_BlitSurface(
            character->surface[character->current_direction],
            NULL,
            screen,
            &character->screen_position
        );
        SDL_Flip(screen);
    }
    for (i = 0 ; i < 4 ; i++)
        SDL_FreeSurface(character->surface[i]);
    free_map(map);
}
