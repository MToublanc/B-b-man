#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_getenv.h>

#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

    #define BLOCK_SIZE          64
    #define NB_BLOCK_WIDTH      14
    #define NB_BLOCK_HEIGHT     14
    #define LARGEUR_FENETRE     BLOCK_SIZE * NB_BLOCK_WIDTH
    #define HAUTEUR_FENETRE     BLOCK_SIZE * NB_BLOCK_HEIGHT
    #define MENU_PATH           "assets/images/menu.png"

    enum {HAUT, BAS, GAUCHE, DROITE};
    enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};
    enum sprites {EXPLODABLE_BLOCK, EMPTY, SOLID_BLOCK};
    enum characterDirections {UP, DOWN, LEFT, RIGHT};

#endif

