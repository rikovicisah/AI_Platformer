#include "World.h"
#include <random>
#include <iostream>

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

void drawScene(SDL_Renderer* renderer, bool end) {
	//obstacle.x = rand() % (SCREEN_WIDTH - obstacle.w); // Randomize obstacle position between 0 and SCREEN_WIDTH - obstacle.w
    if(end) drawGoal(renderer);
    drawGround(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    drawObstacle(renderer);
}

void kreirajPozicije(int i) {
    // Randomize the position of the obstacle and goal
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, SCREEN_WIDTH - obstacle.w);
    obstacle.x = dis(gen);
    
    // Ensure goal is not too close to the obstacle
    while (abs(goal.x - obstacle.x) < 100) {
        goal.x = dis(gen);
    }
	std::clog << "Obstacle position: " << obstacle.x << ", Goal position: " << goal.x << std::endl;
	scene_positions[i] = obstacle.x;

}
