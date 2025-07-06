#include "Player.h"
#include <iostream>
#include "World.h"

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;
bool Player::end = false;


void Player::init() {
    rectangle.h = 50;
    rectangle.w = 50;
    rectangle.x = 100;
    rectangle.y = SCREEN_HEIGHT - rectangle.h - 50;
    velocity_Y = 0;
    onGround = true;
}

void Player::update(const Uint8* keystate, SDL_Rect& obstacle, SDL_Rect& goal) {
	static int broj_scena = 3;
    if (keystate[SDL_SCANCODE_LEFT])
        rectangle.x -= 5;
    if (keystate[SDL_SCANCODE_RIGHT])
        rectangle.x += 5;

    if (keystate[SDL_SCANCODE_SPACE] && onGround) {
        velocity_Y -= 12;
        onGround = false;
    }

    velocity_Y += 0.6f;
    rectangle.y += static_cast<int>(velocity_Y);

    if (rectangle.y + rectangle.h >= SCREEN_HEIGHT - 50) {
        rectangle.y = SCREEN_HEIGHT - rectangle.h - 50;
        velocity_Y = 0;
        onGround = true;
    }

    if (SDL_HasIntersection(&rectangle, &obstacle)) {
        std::cout << "GAME OVER: Udario si prepreku!\n";
        rectangle.x = 100;
        rectangle.y = SCREEN_HEIGHT - rectangle.h - 50;
        velocity_Y = 0;
        onGround = true;
    }

    if (SDL_HasIntersection(&rectangle, &goal)) {
        if (broj_scena > 0)
        {
            std::cout << "Idemo nova scena!\n";
			kreirajPozicije((3 - broj_scena));
            broj_scena--;
            rectangle.x = 50;
            rectangle.y = SCREEN_HEIGHT - rectangle.h - 50;
            velocity_Y = 0;
            onGround = true;
        }
        else {
            std::cout << "KRAJ IGRE: Stigao si do kraja!\n";
			Player::end = true;
        }
        
    }
}

void Player::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
    SDL_RenderFillRect(renderer, &rectangle);
}

