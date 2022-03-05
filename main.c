#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "tile.h"
#include "board.h"

#define BOMB 9

int values[20][20], revealed[20][20];

void GenerateValueTable(int a[][20], int b[][20])
{
    int i, j, nb, k, l;

    srand(time(0));

    for (i=1; i<=40; i++)
        a[rand() % 16][rand() % 16] = BOMB;

    for (i=0; i<16; i++)
        for (j=0; j<16; j++)
        {
            nb = 0;
            if (a[i][j] != BOMB)
                {
                    for (k=-1; k<=1; k++)
                        for (l=-1; l<=1; l++)
                            if (i+k >= 0 && i+k < 16 && j+l >= 0 && j+l < 16)
                                if (a[i+k][j+l] == BOMB)
                                    nb++;
                    a[i][j] = nb;
                }
        }

    for (i=0; i<16; i++)
        for (j=0; j<16; j++)
            b[i][j] = 0;
}

int main(int argv, char** argc)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //SDL_Rect rect = {0, 0, 30, 30};

    tile* test[16][16];
    CreateBoard(test);
    //RecursiveRevealTile(test, 8, 8);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    BlitBoard(test, renderer);


    while (1)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                break;


        HandleBoard(test, renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
