#include "constants.h"
#include "game.h"

void menu()
{
    SDL_Surface *screen = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int playing = 1;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Bomberman", NULL);
    SDL_WM_SetCaption("SDL_Mixer", NULL);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    Mix_Chunk *start = NULL;
    start = Mix_LoadWAV( "assets/son/start.wav" );
    Mix_Music *music;
    music = Mix_LoadMUS("assets/son/menu.mp3");
    Mix_PlayMusic(music, -1);
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
                        Mix_PlayChannel(0, start, 0);
                        Mix_HaltMusic();
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
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}
