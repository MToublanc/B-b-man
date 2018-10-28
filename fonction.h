//fonction.h

#include<stdio.h>
#include<stdlib.h>

#include<SDL/SDL.H>
#include<SDL_image/SDL_image.H>
#include<SDL_ttf/SDL_ttf.h>
#include<SDL/SDL_getenv.H>
//#include<FMOD/fmod.h>

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define LARGEUR_FENETRE        704
#define HAUTEUR_FENETRE        704

void jouer(SDL_Surface* ecran);
#endif

