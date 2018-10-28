#include "fonction.h"


int main(int argc, char** argv)
{
    SDL_Surface *ecran = NULL, *menu = NULL, *texte = NULL;
    SDL_Rect positionMenu, positionClic, positionTxt;
    SDL_Event event;
    int continuer = 1;
    
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0,0,0};
    
    TTF_Font *policeBig = NULL;
    
    TTF_Init();
    police = TTF_OpenFont("police.ttf", 35);
    
    putenv("SDL_VIDEOCENTERED=1");
    SDL_Init(SDL_INIT_VIDEO);
    
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE  | SDL_DOUBLEBUF | SDL_NOFRAME);
    SDL_WM_SetCaption("MonMenu", NULL);
    
    menu = IMG_Load("Menu1.png");
    
    
    positionMenu.x = 0;
    positionMenu.y = 0;
    
    while(continuer)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case  SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                
                switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    //...
                    break;
            }
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    positionClic.x = event.button.x;
                    positionClic.y = event.button.y;
                    
                    if (event.button.x > 10 && event.button.x < 150 && event.button.y > 100 && event.button.y < 150)//bouton jouer
                    {
                        texte=TTF_RenderText_Blended(policeBig,"Bientôt disponible...", couleurNoire);
                        SDL_Flip(ecran);
                        
                        //jouer(ecran);
                    }
                    else (event.button.x > 10 && event.button.x < 150 && event.button.y > 200 && event.button.y < 250); //quitter
                    {
                        exit(0);
                    }
                }
        }
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        
        SDL_Flip(ecran);
    }
    
                        SDL_FreeSurface(menu);
                        
                        TTF_CloseFont(police);
                        TTF_Quit();
                        
                        SDL_FreeSurface(texte);
                        SDL_Quit();
                        
                        return EXIT_SUCCESS;
                        }

