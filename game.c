#include "constants.h"
#include "game.h"
#include "bomb.h"
#include "character.h"
#include "map.h"

void game(SDL_Surface *screen)
{
    SDL_Event event;
    bool playing = true;
    int i = 0, j = 0;
    int **map = load_map();

    t_bomb_node *bomb_list = NULL;
    t_character_node *character_list = NULL; 
    
    add_character_to_list(&character_list, 4, 1);

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
                            moveCharacter(map, character_list->character, bomb_list, UP);
                            break;
                        case SDLK_DOWN:
                            moveCharacter(map, character_list->character, bomb_list, DOWN);
                            break;
                        case SDLK_RIGHT:
                            moveCharacter(map, character_list->character, bomb_list, RIGHT);
                            break;
                        case SDLK_LEFT:
                            moveCharacter(map, character_list->character, bomb_list, LEFT);
                            break;
                        case SDLK_SPACE:
                            add_bomb_to_list(&bomb_list, character_list->character->x, character_list->character->y);
                            break;
                    }
                    break;
            }
        }
        draw_map(map, screen);
        draw_bombs_on_screen(screen, &bomb_list, map);
        if (character_list != NULL) {
            draw_characters_on_screen(screen, &character_list, map);
        } else {
            playing = false;
        } 
        SDL_Flip(screen);
    }
    SDL_Delay(500);
    free_map(map);
}
