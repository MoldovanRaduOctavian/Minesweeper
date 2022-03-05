#pragma once

#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include <SDL2/SDL_ttf.h>

tile* board[16][16];

void CreateBoard(tile* board[][16]);
void RecursiveRevealTile(tile* board[][16], int pozx, int pozy);
void BlitBoard(tile* board[][16], SDL_Renderer* renderer);
int CheckWinBoard(tile* board[][16]);
int CheckLoseBoard(tile* board[][16]);
void HandleBoard(tile* board[][16], SDL_Renderer* renderer);

#endif // BOARD_H
