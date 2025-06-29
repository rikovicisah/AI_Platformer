// AI_Platformer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Rect obstacle = { 400, SCREEN_HEIGHT - 100, 50, 50 };
SDL_Rect goal = { SCREEN_WIDTH, SCREEN_HEIGHT - 100, 50, 50 };


struct Player 
{
    SDL_Rect rectangle;
    float velocity_Y = 0;
    bool onGround = true;


    void init()
    {
        rectangle.h = 50;
        rectangle.w = 50;
        rectangle.x = 100;
        rectangle.y = SCREEN_HEIGHT - rectangle.h - 50;
    }

    void update(const Uint8* keystate) 
    {
        //moving left - right
        if (keystate[SDL_SCANCODE_LEFT])
            rectangle.x -= 5;
        if (keystate[SDL_SCANCODE_RIGHT])
            rectangle.x += 5;


        //jumping
        if (keystate[SDL_SCANCODE_SPACE] && onGround)
        {
            velocity_Y -= 12;
            onGround = false;
        }
            

        //gravity
        velocity_Y += .6f;
        rectangle.y += static_cast<int>(velocity_Y);


        //colision with the ground
        if (rectangle.y + rectangle.h >= SCREEN_HEIGHT - 50)
        {
            rectangle.y = SCREEN_HEIGHT - rectangle.h - 50;
            velocity_Y = 0;
            onGround = true;
        }


		//colission with the obstacle then reset player position
        if (SDL_HasIntersection(&rectangle, &obstacle)) {
            std::cout << "GAME OVER: Udario si prepreku!\n";
            rectangle.x = 100;
            rectangle.y = SCREEN_HEIGHT - rectangle.h - 50;
            velocity_Y = 0;
            onGround = true;
        }

		//colission with the goal
        if(SDL_HasIntersection(&rectangle, &goal)) {
            std::cout << "CILJ: Stigao si do cilja!\n";
            rectangle.x = 100;
            rectangle.y = SCREEN_HEIGHT - rectangle.h - 50;
            velocity_Y = 0;
            onGround = true;
		}

    }

    void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
        SDL_RenderFillRect(renderer, &rectangle);
    }
};


void drawGround() {
    SDL_Rect ground = { 0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, 50 };
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &ground);
}

void drawObstacle() {
	SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255); // red color for the obstacle
    SDL_RenderFillRect(renderer, &obstacle);
}

void drawGoal() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green color for the goal
    SDL_RenderFillRect(renderer, &goal);
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        //std::cout<< "SDL init failed" << SDL_GetError() << std::endl;
        SDL_Log("Desila se greska %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Isah's AI game",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cout << "Window creation failed : " << SDL_GetError() << std::endl;
        return 1;
    }


	//-1 znaci da se koristi bilo koji renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Player player;
    player.init();

    bool running = true;
    SDL_Event event;

    while (running) {
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        player.update(keystate);
        std::cout << "Udaljenost: " << player.rectangle.x << "\r";


        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        drawGround();
        drawObstacle();
		//drawGoal();
        player.draw(renderer);

        SDL_RenderPresent(renderer);
		SDL_Delay(16); // ~60 FPS tj 1/60 frame dobije se latency 16.67 ms
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}

