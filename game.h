#ifndef _GAME_H
#define _GAME_H

void game(SDL_Surface* ecran);
void moveCharacter(int carte[][NB_BLOCK_HEIGHT], SDL_Rect *pos, int direction);

#endif