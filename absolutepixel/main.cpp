#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "SDLApp.h"
#include "TexturedRectangle.h"
#include "AnimatedSprite.h"
#include "GameEntity.h"

// One possibility of creating as a global our app
SDLApp* app;

// Create two objects to render. Eventually, we will want some sort of factory to manage object creation in our App...
GameEntity* player;
GameEntity* tim;

void HandleEvents() 
{
    SDL_Event event;

    // (1) Handle Input --- Start our event loop
    while (SDL_PollEvent(&event)) {
        // Handle each specific event

        if (event.type == SDL_QUIT) {
            app->StopAppLoop();
        }

        // Detect collision from our two shapes if mouse
        // button is pressed
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (tim->GetSprite().IsColliding(player->GetSprite())) 
            {
                std::cout << "Is colliding\n";
            }
            else {
                std::cout << "Not colliding\n";
            }
        }

    }
}

void HandleRendering()
{
    // Set draw positions and size
    player->GetSprite().SetPosition(100, 100);
    player->GetSprite().SetDimensions(128, 128);
    tim->GetSprite().SetPosition(app->GetMouseX(), app->GetMouseY());
    tim->GetSprite().SetDimensions(128, 128);

    // Render our objects
    player->Render();
    tim->Render();
}


int main(int argc, char* argv[]) 
{
    // Setup the SDLApp
    const char* title = "SDL2 Abstraction";
    app = new SDLApp(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);

    // Create any objects in our scene
    player = new GameEntity(app->GetRenderer(), "assets/player_still.bmp");
    tim = new GameEntity(app->GetRenderer(), "assets/tim_still.bmp");

    // Set callback functions
    app->SetEventCallback(HandleEvents);
    app->SetRenderCallback(HandleRendering);

    // Run our application until terminated
    app->RunLoop();

    // Clean up our application
    delete app;
    delete player;
    delete tim;

    return 0;
}