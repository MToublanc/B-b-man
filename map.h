#ifndef _MAP_H
#define _MAP_H

void draw_map(int **map, SDL_Surface *screen);
int **load_map();
void free_map(int **map);

#endif