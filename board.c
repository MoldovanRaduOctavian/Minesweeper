#include "board.h"

void CreateBoard(tile* board[][16])
{
    int i, j, aux1, aux2, nb, k, l;
    SDL_Rect rect = {0, 0, 0, 0};
    srand(time(0));

    for (i=0; i<16; i++)
        for (j=0; j<16; j++)
            {
                rect.y = i * 30;
                rect.x = j * 30;
                rect.w = 30;
                rect.h = 30;
                board[i][j] = CreateTile(0, NSHOW, rect);
            }

    for (i=1; i<=40; i++)
    {
        aux1 = rand() % 16;
        aux2 = rand() % 16;
        board[aux1][aux2]->value = 9;
    }

     for (i=0; i<16; i++)
    {
        for (j=0; j<16; j++)
            printf("%d ", board[i][j]->value);
        printf("\n");
    }

    printf("\n\n");

    for (i=0; i<16; i++)
        for (j=0; j<16; j++)
        {

            if (board[i][j]->value != 9)
                {
                    nb = 0;
                    for (k=-1; k<=1; k++)
                        for (l=-1; l<=1; l++)
                            if (i+k >= 0 && i+k < 16 && j+l >= 0 && j+l < 16)
                                if (board[i+k][j+l]->value == 9)
                                    nb++;
                    board[i][j]->value = nb;
                }
        }


    for (i=0; i<16; i++)
    {
        for (j=0; j<16; j++)
            printf("%d ", board[i][j]->value);
        printf("\n");
    }
}

void RecursiveRevealTile(tile* board[][16], int pozy, int pozx)
{
    int i, j;
    if (board[pozy][pozx]->state == NSHOW)
      {
         if (board[pozy][pozx]->value != 9)
           {
                board[pozy][pozx]->state = SHOW;
                if (board[pozy][pozx]->value == 0)
                    for (i=-1; i<=1; i++)
                        for (j=-1; j<=1; j++)
                            if (pozy+i >= 0 && pozy+i < 16 && pozx+j >= 0 && pozx+j < 16)
                                RecursiveRevealTile(board, pozy+i, pozx+j);
           }
         else
            for (i=0; i<16; i++)
                for (j=0; j<16; j++)
                    board[i][j]->state = SHOW;
      }
      //printf("r\n");

}

void BlitBoard(tile* board[][16], SDL_Renderer* renderer)
{
    int i, j;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (i=0; i<16; i++)
        for (j=0; j<16; j++)
            BlitTile(board[i][j], renderer);
    //SDL_Delay(30);

}

int CheckLoseBoard(tile* board[][16])
{
    for (int i=0; i<16; i++)
        for (int j=0; j<16; j++)
            if (board[i][j]->value == 9 && board[i][j]->state == SHOW)
                return 1;
    return 0;
}

int CheckWinBoard(tile* board[][16])
{
    for (int i=0; i<16; i++)
        for (int j=0; j<16; j++)
            if ((board[i][j]->value != 9 && board[i][j]->state != SHOW) ||
                (board[i][j]->value == 9 && board[i][j]->state != FLAG))
                return 0;

    return 1;
}

void HandleBoard(tile* board[][16], SDL_Renderer* renderer)
{
    int relevant_click = 0, win, lose;

    win = CheckWinBoard(board);
    lose = CheckLoseBoard(board);

    if (!win && !lose)
    {
         for (int i=0; i<16; i++)
                for (int j=0; j<16; j++)
            {
                    if (LeftClickedTile(board[i][j]) && board[i][j]->state == NSHOW && board[i][j]->clickable == 1)
                    {
                        RecursiveRevealTile(board, i, j);
                        relevant_click = 1;
                    }

                    else if (RightClickedTile(board[i][j]) && board[i][j]->state != SHOW && board[i][j]->clickable == 1)
                    {
                        board[i][j]->state = (board[i][j]->state == NSHOW)?FLAG:NSHOW;
                        relevant_click = 1;
                    }

            }

            if (relevant_click)
                BlitBoard(board, renderer);
    }

    else if (win)
    {
        SDL_Color text_color = {0, 0xff, 0, 0};
        SDL_Rect text_rect = {100, 100, 300, 300};
        TTF_Font* font = TTF_OpenFont("ARCADECLASSIC.TTF", 20);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, "You won!", text_color);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text_surface);
        TTF_CloseFont(font);

    }

    else if (lose)
    {
        SDL_Color text_color = {0xff, 0, 0xff, 0};
        SDL_Rect text_rect = {100, 100, 300, 300};
        TTF_Font* font = TTF_OpenFont("ARCADECLASSIC.TTF", 20);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, "You lost!", text_color);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text_surface);
        TTF_CloseFont(font);
    }


}
