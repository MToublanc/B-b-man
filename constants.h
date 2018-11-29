#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_getenv.h>
#include <SDL/SDL_mixer.h>

#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

    #define BLOCK_SIZE          64
    #define NB_BLOCK_WIDTH      14
    #define NB_BLOCK_HEIGHT     14
    #define WINDOW_WIDTH        BLOCK_SIZE * NB_BLOCK_WIDTH
    #define WINDOW_HEIGHT       BLOCK_SIZE * NB_BLOCK_HEIGHT

    enum sprites {EXPLODABLE_BLOCK, EMPTY, SOLID_BLOCK};
    enum characterDirections {UP, DOWN, LEFT, RIGHT};

#endif

