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

// Create two objects tso render. Eventually, we will want some sort of factory to manage object creation in our App...
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
        if (event.button.button == SDL_BUTTON_LEFT) 
        {   //tim->GetCollider2D().IsColliding(player->GetCollider2D())
            if (tim->GetCollider2D(0).IsColliding(player->GetCollider2D(0)))
            {
                std::cout << "1: Is colliding\n";
            }
            else {
                std::cout << "1: Not colliding\n";
            }

            if (tim->GetCollider2D(0).IsColliding(player->GetCollider2D(1)))
            {
                std::cout << "2: Is colliding\n";
            }
            else {
                std::cout << "2: Not colliding\n";
            }

        }

    }
}

// To keep track and update collisions
void HandleUpdate()
{
    player->Update();
    tim->Update();

    // Primera caja de colisiones, cuerpo completo
    player->GetCollider2D(0).SetAbsolutePosition(player->GetSprite().GetPositionX(), player->GetSprite().GetPositionY());
    player->GetCollider2D(0).SetDimensions(player->GetSprite().GetWidth(), player->GetSprite().GetHeight());

    // Segunda caja de colisiones
    player->GetCollider2D(1).SetAbsolutePosition(player->GetSprite().GetPositionX(),
                                           player->GetSprite().GetPositionY()+player->GetSprite().GetHeight()/2);
    player->GetCollider2D(1).SetDimensions(player->GetSprite().GetWidth(),
                                             player->GetSprite().GetHeight()/2);
    
    tim->GetCollider2D(0).SetAbsolutePosition(tim->GetSprite().GetPositionX(), tim->GetSprite().GetPositionY());
    tim->GetCollider2D(0).SetDimensions(tim->GetSprite().GetWidth(), tim->GetSprite().GetHeight());
}

void HandleRendering()
{
    // Set draw positions and size
    player->GetSprite().SetPosition(app->GetMouseX(), app->GetMouseY());
    player->GetSprite().SetDimensions(128, 128);

    // DVD Screensaver effect.

    static int posX = 0, posY = 0;
    static bool up = true, right = true;

    if (up)
    {
        --posY; // If the "modern" way, --posY, 
    }
    else
    {
        ++posY;
    }

    if (right)
    {
        ++posX;
    }
    else
    {
        --posX;
    }

    if (posX > app->GetWindowWidth())
    {
        right = false;
    }
    else if (posX < 0)
    {
        right = true;
    }

    if (posY < 0)
    {
        up = false;
    }
    else if (posY > app->GetWindowHeight())
    {
        up = true;
    }

    tim->GetSprite().SetPosition(posX, posY);
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
    app->SetMaxFrameRate(4);

    // Create any objects in our scene
    player = new GameEntity(app->GetRenderer());
    player->AddTexturedRectangleComponent("./assets/player_still.bmp");
    // Adds colliders
    player->AddCollider2D();
    player->AddCollider2D();

    tim = new GameEntity(app->GetRenderer());
    tim->AddTexturedRectangleComponent("./assets/tim_still.bmp", 255, 255, 255);
    tim->AddCollider2D();

    // Set callback functions
    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdate);
    app->SetRenderCallback(HandleRendering);

    // Run our application until terminated
    app->RunLoop();

    // Clean up our application
    delete app;
    delete player;
    delete tim;

    return 0;
}