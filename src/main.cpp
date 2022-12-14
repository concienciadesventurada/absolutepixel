#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "SDLApp.h"
#include "TexturedRectangle.h"
#include "AnimatedSprite.h"
#include "GameEntity.h"
#include "Vector2D.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "DynamicText.h"

// One possibility of creating as a global our app
SDLApp* app;

// Create two objects tso render. Eventually, we will want some sort of factory to manage object creation in our App...
GameEntity* player;
GameEntity* tim;

Sound* CollisionSound;

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
            if (tim->GetBoxCollider2D(0).IsColliding(player->GetBoxCollider2D(0)))
            {
                std::cout << "1: Is colliding\n";
                CollisionSound->PlaySound();
            }
            else {
                std::cout << "1: Not colliding\n";
            }

            if (tim->GetBoxCollider2D(0).IsColliding(player->GetBoxCollider2D(1)))
            {
                std::cout << "2: Is colliding\n";
                CollisionSound->PlaySound();
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

    // Set draw positions and size
    player->SetPosition(app->GetMouseX(), app->GetMouseY());
    player->SetDimensions(128, 128);

    tim->SetPosition(posX, posY);
    tim->SetDimensions(128, 128);

    player->GetBoxCollider2D(1).SetDimensions(player->GetSprite().GetWidth(), player->GetSprite().GetHeight() / 2);
    
    Vector2D dims = player->GetBoxCollider2D(0).SetBoundingBoxAuto(ResourceManager::GetInstance().GetSurface("./assets/player_still.bmp"),0xFF,0x00,0xFF);

    int newXPos = dims.x + app->GetMouseX(); 
    int newYPos = dims.y + app->GetMouseY();

    player->GetBoxCollider2D(0).SetAbsolutePosition(newXPos, newYPos);
/* 
    // Primera caja de colisiones, cuerpo completo
    player->GetCollider2D(0).SetAbsolutePosition(player->GetSprite().GetPositionX(), player->GetSprite().GetPositionY());
    player->GetCollider2D(0).SetDimensions(player->GetSprite().GetWidth(), player->GetSprite().GetHeight());

    // Segunda caja de colisiones
    player->GetCollider2D(1).SetAbsolutePosition(player->GetSprite().GetPositionX(), player->GetSprite().GetPositionY()+player->GetSprite().GetHeight()/2);
    player->GetCollider2D(1).SetDimensions(player->GetSprite().GetWidth(), player->GetSprite().GetHeight()/2);
    
    tim->GetCollider2D(0).SetAbsolutePosition(tim->GetSprite().GetPositionX(), tim->GetSprite().GetPositionY());
    tim->GetCollider2D(0).SetDimensions(tim->GetSprite().GetWidth(), tim->GetSprite().GetHeight());
 */

}

void HandleRendering()
{
    // Render our objects
    player->Render();
    tim->Render();

    // Rendering text after objects is a common practice
    DynamicText text1("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 12);
    text1.DrawText(app->GetRenderer(), "Mira Chico Migrana, soy el logo del dvd", 0, 0, 640, 128);

    DynamicText text2("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 12);
    text2.DrawText(app->GetRenderer(), "No ql no", app->GetMouseX(), app->GetMouseY(), 128, 64);
}


int main(int argc, char* argv[]) 
{
    // Setup the SDLApp
    const char* title = "SDL2 Abstraction";
    app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO, title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    app->SetMaxFrameRate(4);

    // Create any objects in our scene
    player = new GameEntity(app->GetRenderer());
    player->AddTexturedRectangleComponent("./assets/player_still.bmp");
    // Adds colliders
    player->AddBoxCollider2D();
    player->AddBoxCollider2D();

    tim = new GameEntity(app->GetRenderer());
    tim->AddTexturedRectangleComponent("./assets/tim_still.bmp", 255, 255, 255);
    tim->AddBoxCollider2D();

    // Setup sounds
    CollisionSound = new Sound("./assets/sfx/bruh.wav"); //
    CollisionSound->SetupDevice();  // TODO: Refactor. Now I have to instance a sound each time.

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
    delete CollisionSound;

    return 0;
}