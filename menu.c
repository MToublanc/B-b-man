#include "constants.h"
#include "game.h"

void menu()
{
    SDL_Surface *screen = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int playing = 1;

    SDL_Init(SDL_INIT_VIDEO);

    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Bomberman", NULL);

    menu = IMG_Load("assets/images/menu.png");
    positionMenu.x = 0;
    positionMenu.y = 0;

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
                    case SDLK_j: // Join
                        game(screen);
                        break;
                    case SDLK_h: // Host
                        game(screen);
                        break;
                    case SDLK_q: //Quit
                        playing = 0;
                        break;
                }
                break;
        }
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, screen, &positionMenu);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(menu);
    SDL_FreeSurface(screen);
    SDL_Quit();
}
