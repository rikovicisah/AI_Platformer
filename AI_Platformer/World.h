#pragma once
#include <SDL.h>

extern SDL_Rect obstacle;
extern SDL_Rect goal;
static int scene_positions[3] = { 0, 0, 0 };


void drawGround(SDL_Renderer* renderer, int screenWidth, int screenHeight);
void drawObstacle(SDL_Renderer* renderer);
void drawGoal(SDL_Renderer* renderer); 
void drawScene(SDL_Renderer* renderer, bool end=false);
void kreirajPozicije(int i);
