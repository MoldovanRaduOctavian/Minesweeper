#include "tile.h"

tile* CreateTile(int value, int state, SDL_Rect rect)
{
    tile* t = (tile*)malloc(sizeof(tile));
    t->value = value;
    t->state = state;
    t->clickable = 1;
    t->left_clicked_last_frame = 0;
    t->right_clicked_last_frame = 0;
    t->rect = rect;

    return t;
}


int HoverTile(tile* tile)
{
    int mx, my;
    SDL_GetMouseState(&mx, &my);

    if (mx > tile->rect.x && mx < (tile->rect.x + tile->rect.w) &&
        my > tile->rect.y && my < (tile->rect.y + tile->rect.h))
            return 1;

    return 0;
}

int LeftClickedTile(tile* tile)
{
    int rez = 0;

    if (HoverTile(tile) && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && !tile->left_clicked_last_frame)
        rez = 1;

    tile->left_clicked_last_frame = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
    return rez;
}

int RightClickedTile(tile* tile)
{
    int rez = 0;

    if (HoverTile(tile) && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) && !tile->right_clicked_last_frame)
        rez = 1;

    tile->right_clicked_last_frame = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
    return rez;
}

void BlitTile(tile* tile, SDL_Renderer* renderer)
{
    char s[30];
    SDL_Surface* tile_surface;
    SDL_Texture* tile_texture;

    if (tile->state == NSHOW)
        strcpy(s, "unrevealed_tile.png");
    else if (tile->state == SHOW)
        sprintf(s, "%d_tile.png", tile->value);
    else if (tile->state == FLAG)
        strcpy(s, "flag_tile.png");

    tile_surface = IMG_Load(s);
    tile_texture = SDL_CreateTextureFromSurface(renderer, tile_surface);

    SDL_RenderCopy(renderer, tile_texture, NULL, &tile->rect);

    SDL_FreeSurface(tile_surface);
    SDL_DestroyTexture(tile_texture);
}
