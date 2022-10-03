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
#include "GameState.h"
#include "KeyboardController.h"

// DOS PROBLEMAS DE DECLARACION EN EL KEYBOARD


// One possibility of creating as a global our app
SDLApp* app;

// Create two objects to render. Eventually, we will want some sort of factory to manage object creation in our App...
GameEntity* leftPaddle;
GameEntity* rightPaddle;
GameEntity* ball;

Sound* CollisionSound;
Sound* ScoreSound;

KeyboardController* playerLeft;
KeyboardController* playerRight;

GameState* gameState;

void HandleEvents() 
{
    SDL_Event event;

    // (1) Handle Input --- Start our event loop
    while (SDL_PollEvent(&event)) 
    {
        // Handle each specific event

        if (event.type == SDL_QUIT) 
        {
            app->StopAppLoop();
        }

        playerLeft->UpdateKeyboardEvent(event, leftPaddle, gameState);
        playerRight->UpdateKeyboardEvent(event, rightPaddle, gameState);


        //rightPaddle->GetCollider2D().IsColliding(leftPaddle->GetCollider2D())
        if (rightPaddle->GetBoxCollider2D(0).IsColliding(leftPaddle->GetBoxCollider2D(0)))
        {
            std::cout << "1: Is colliding\n";
            CollisionSound->PlaySound();
        }
        else {\
            std::cout << "1: Not colliding\n";
        }

        if (rightPaddle->GetBoxCollider2D(0).IsColliding(leftPaddle->GetBoxCollider2D(1)))
        {
            std::cout << "2: Is colliding\n";
            CollisionSound->PlaySound();
        }
        else {
            std::cout << "2: Not colliding\n";
        }

    }

}

// To keep track and update collisions
void HandleUpdate()
{
    // Actualizan los valores de la posicion de la pelota cada frame
    int ballXPosition = ball->GetSprite().GetPositionX();              
    int ballYPosition = ball->GetSprite().GetPositionY();

    // Detecta colision
    if (leftPaddle->GetBoxCollider2D(0).IsColliding(ball->GetBoxCollider2D(0)))
    {
        gameState->ballXDirection *= -1;
        CollisionSound->PlaySound();

        // Detect where the collision happend - 100 en vez del alto, pero para que sea exactamente la mitad, si no, cambiar el resto por 100
        int paddleMidPoint = leftPaddle->GetSprite().GetPositionY() + leftPaddle->GetSprite().GetHeight() / 2;
        if (paddleMidPoint > ballYPosition) 
        {
          gameState->ballYDirection = -1;
        }
        else if (paddleMidPoint <= ballYPosition)
        {
          gameState->ballYDirection = 1;
        }
    }
    if (rightPaddle->GetBoxCollider2D(0).IsColliding(ball->GetBoxCollider2D(0)))
    {
        gameState->ballXDirection *= -1;
        CollisionSound->PlaySound();
    }

    // BARRERAS DE LAS VENTANAS - SI CHOCA A LOS COSTADOS, SE SUMA AL MARCADOR
    if (ballXPosition > app->GetWindowWidth() + 100)  // Se encarga de que, la bola, de izquierda a derecha, registre la colision y trayectoria hascia la derecha
    {
        gameState->ballXDirection *= -1;
        gameState->leftScore++;

        ballXPosition = app->GetWindowWidth() / 2;
        ballYPosition = app->GetWindowHeight() / 2;

        ScoreSound->PlaySound();
/*         // TODO: Use ball dimensions instead of screen dimentions
        ballXPosition = app->GetWindowWidth() / ball->GetSprite().GetPositionX();
        ballYPosition = app->GetWindowHeight() / ball->GetSprite().GetPositionY(); */
    }
    if (ballXPosition < 0)
    {
        gameState->ballXDirection *= -1;
        gameState->rightScore++;

        ballXPosition = app->GetWindowWidth() / 2;
        ballYPosition = app->GetWindowHeight() / 2;

        ScoreSound->PlaySound();

    }
    
    if (ballYPosition > app->GetWindowHeight()) //X
    {
        gameState->ballYDirection *= -1;
    }
        if (ballYPosition < 0)
    {
        gameState->ballYDirection *= -1;
    }

    if (gameState->ballXDirection > 0)
    {
        ballXPosition += gameState->movementSpeed;
    }
    else
    {
        ballXPosition -= gameState->movementSpeed;
    }

    if (gameState->ballYDirection > 0)
    {
        ballYPosition += gameState->movementSpeed;
    }
    else
    {
        ballYPosition -= gameState->movementSpeed;
    }

    // TODO: RESET BALL IN THE CENTER AND DELAY IF A PLAYER SCORES 
    ball->SetPosition(ballXPosition, ballYPosition);

    static int currentTime = SDL_GetTicks();
    static int lastTime = SDL_GetTicks();

    if (currentTime > lastTime + 1000)
    {
      ScoreSound->StopSound();
      CollisionSound->StopSound();      
      lastTime = currentTime;
    }
    
}

void HandleRendering()
{
    // Render our objects
    leftPaddle->Render();
    rightPaddle->Render();
    ball->Render();

    // Rendering text after objects is a common practice
    DynamicText leftScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 12);
    DynamicText rightScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 12);

    std::string lScore = std::to_string(gameState->leftScore);
    std::string rScore = std::to_string(gameState->rightScore);    

    leftScore.DrawText(app->GetRenderer(), lScore, 0, 0, 16, 16);
    rightScore.DrawText(app->GetRenderer(), rScore, 624, 0, 16, 16);
    
}


int main(int argc, char* argv[]) 
{
    // Setup the SDLApp
    const char* title = "Pong";
    app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO, title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    app->SetMaxFrameRate(32);

    playerLeft = new KeyboardController(SDLK_w, SDLK_s);
    playerRight = new KeyboardController(SDLK_h, SDLK_j);

    // Create any objects in our scene
    leftPaddle = new GameEntity(app->GetRenderer());
    leftPaddle->AddTexturedRectangleComponent("./assets/leftPaddle.bmp");
    leftPaddle->AddBoxCollider2D();
    leftPaddle->SetPosition(32, 220);
    leftPaddle->SetDimensions(16, 64);

    rightPaddle = new GameEntity(app->GetRenderer());
    rightPaddle->AddTexturedRectangleComponent("./assets/rightPaddle.bmp");
    rightPaddle->AddBoxCollider2D();
    rightPaddle->SetPosition(592, 220);
    rightPaddle->SetDimensions(16, 64);

    ball = new GameEntity(app->GetRenderer());
    ball->AddTexturedRectangleComponent("./assets/ball.bmp");
    ball->AddBoxCollider2D();
    ball->SetPosition(app->GetWindowWidth() / 2, app->GetWindowHeight() / 2);
    ball->SetDimensions(16, 16);

    // Setup sounds
    CollisionSound = new Sound("./assets/sfx/bruh.wav"); //
    CollisionSound->SetupDevice();  // TODO: Refactor. Now I have to instance a sound each rightPaddlee.

    ScoreSound = new Sound("./assets/sfx/Score.wav");
    
    // Set up game state
    gameState = new GameState;
    gameState->movementSpeed = 5.0f;
    gameState->ballSpeed = 2.5f;
    gameState->ballXDirection = 1;
    gameState->ballYDirection = 1;

    gameState->leftScore = 0;
    gameState->rightScore = 0;

    // Set callback functions
    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdate);
    app->SetRenderCallback(HandleRendering);

    // Run our application until terminated
    app->RunLoop();

    // Clean up our application
    delete app;
    delete leftPaddle;
    delete rightPaddle;
    delete ball;
    delete CollisionSound;
    delete ScoreSound;

    return 0;
}
