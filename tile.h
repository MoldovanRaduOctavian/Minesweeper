#pragma once

#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NSHOW 0
#define SHOW 1
#define FLAG 2


typedef struct tile
{
    int value;
    int state;
    int clickable;
    int left_clicked_last_frame;
    int right_clicked_last_frame;
    SDL_Rect rect;
} tile;

tile* CreateTile(int value, int state, SDL_Rect rect);
int HoverTile(tile* tile);
int LeftClickedTile(tile* tile);
int RightClickedTile(tile* tile);
void BlitTile(tile* tile, SDL_Renderer* renderer);
void HandleTile(tile* tile);


#endif // TILE_H
