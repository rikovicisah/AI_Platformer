// AI_Platformer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

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

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        drawGround();
        player.draw(renderer);

        SDL_RenderPresent(renderer);
		SDL_Delay(16); // ~60 FPS tj 1/60 frame dobije se latency 16.67 ms
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}

