#pragma once
#include <SDL.h>

extern SDL_Rect obstacle;
extern SDL_Rect goal;

void drawGround(SDL_Renderer* renderer, int screenWidth, int screenHeight);
void drawObstacle(SDL_Renderer* renderer);
void drawGoal(SDL_Renderer* renderer);
