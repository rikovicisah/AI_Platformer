#pragma once
#include <SDL.h>


struct Player {
    SDL_Rect rectangle;
    float velocity_Y;
    bool onGround;

    void init();
    void update(const Uint8* keystate, SDL_Rect& obstacle, SDL_Rect& goal);
    void draw(SDL_Renderer* renderer);
};
