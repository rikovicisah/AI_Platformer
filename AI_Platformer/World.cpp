#include "World.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Rect obstacle = { 400, SCREEN_HEIGHT - 100, 50, 50 };
SDL_Rect goal = { SCREEN_WIDTH, SCREEN_HEIGHT - 100, 50, 50 };

void drawGround(SDL_Renderer* renderer, int screenWidth, int screenHeight) {
    SDL_Rect ground = { 0, screenHeight - 50, screenWidth, 50 };
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &ground);
}

void drawObstacle(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    SDL_RenderFillRect(renderer, &obstacle);
}

void drawGoal(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &goal);
}
