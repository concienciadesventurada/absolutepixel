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

// One possibility of creating as a global our app
SDLApp* app;

// Create two objects to render. Eventually, we will want some sort of factory to manage object creation in our App...
GameEntity* leftPaddle;
GameEntity* rightPaddle;
GameEntity* ball;

Sound* CollisionSound;
Sound* ScoreSound;

GameState* gameState;

void HandleEvents() 
{
    SDL_Event event;

    // (1) Handle Input --- Start our event loop
    while (SDL_PollEvent(&event)) {
        // Handle each specific event

        if (event.type == SDL_QUIT) {
            app->StopAppLoop();
        }

        if (event.type == SDL_KEYDOWN)
        {
            // When a key is pressed, will retrieve the paddle's positions
            int leftPaddleX = leftPaddle->GetSprite().GetPositionX();
            int leftPaddleY = leftPaddle->GetSprite().GetPositionY();

            int rightPaddleX = rightPaddle->GetSprite().GetPositionX();
            int rightPaddleY = rightPaddle->GetSprite().GetPositionY();

            if (event.key.keysym.sym == SDLK_w)
            {   
                leftPaddleY -= gameState->movementSpeed;
                leftPaddle->SetPosition(leftPaddleX, leftPaddleY);
            }
            else if (event.key.keysym.sym == SDLK_s)
            {
                leftPaddleY += gameState->movementSpeed;    
                leftPaddle->SetPosition(leftPaddleX, leftPaddleY);
            }

            else if (event.key.keysym.sym == SDLK_UP)
            {   
                rightPaddleY -= gameState->movementSpeed;
                rightPaddle->SetPosition(rightPaddleX, rightPaddleY);
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                rightPaddleY += gameState->movementSpeed;
                rightPaddle->SetPosition(rightPaddleX, rightPaddleY);
            }
        }

          //rightPaddle->GetCollider2D().IsColliding(leftPaddle->GetCollider2D())
            if (rightPaddle->GetBoxCollider2D(0).IsColliding(leftPaddle->GetBoxCollider2D(0)))
            {
                std::cout << "1: Is colliding\n";
                CollisionSound->PlaySound();
            }
            else {
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
    // Setting collider dimensions - Esta las deja las colisiones chicas de 16x16, no se xq y tampoco en q momento, pero se ponen automaticas 
    // y funcionan sin esta declaracion, la dejo pa irme a la segura si luego la necesito cuando refactorice el sist de colisiones

    /* leftPaddle->GetBoxCollider2D(0).SetDimensions(leftPaddle->GetSprite().GetWidth(), leftPaddle->GetSprite().GetWidth());
    rightPaddle->GetBoxCollider2D(0).SetDimensions(rightPaddle->GetSprite().GetWidth(), rightPaddle->GetSprite().GetWidth( ));
    ball->GetBoxCollider2D(0).SetDimensions(ball->GetSprite().GetWidth(), ball->GetSprite().GetWidth( ));*/

    // Detectan la colision

    if (leftPaddle->GetBoxCollider2D(0).IsColliding(ball->GetBoxCollider2D(0)))
    {
        gameState->ballXDirection *= -1;
        CollisionSound->PlaySound();
    }
    if (rightPaddle->GetBoxCollider2D(0).IsColliding(ball->GetBoxCollider2D(0)))
    {
        gameState->ballXDirection *= -1;
        CollisionSound->PlaySound();
    }


    // Actualizan los valores de la posicion de la pelota cada frame
    int ballXPosition = ball->GetSprite().GetPositionX();
    int ballYPosition = ball->GetSprite().GetPositionY();

    
    // BARRERAS DE LAS VENTANAS - SI CHOCA A LOS COSTADOS, SE SUMA AL MARCADOR
    if (ballXPosition > app->GetWindowWidth())  // Se encarga de que, la bola, de izquierda a derecha, registre la colision y trayectoria hascia la derecha
    {
        gameState->ballXDirection *= -1;
        gameState->leftScore++;

        ballXPosition = app->GetWindowWidth() / 2;
        ballYPosition = app->GetWindowHeight() / 2;
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


/*     leftPaddle->Update();
    rightPaddle->Update();

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
    leftPaddle->SetPosition(app->GetMouseX(), app->GetMouseY());
    leftPaddle->SetDimensions(128, 128);

    rightPaddle->SetPosition(posX, posY);
    rightPaddle->SetDimensions(128, 128);

    leftPaddle->GetBoxCollider2D(1).SetDimensions(leftPaddle->GetSprite().GetWidth(), leftPaddle->GetSprite().GetHeight() / 2);
    
    Vector2D dims = leftPaddle->GetBoxCollider2D(0).SetBoundingBoxAuto(ResourceManager::GetInstance().GetSurface("./assets/leftPaddle_still.bmp"),0xFF,0x00,0xFF);

    int newXPos = dims.x + app->GetMouseX(); 
    int newYPos = dims.y + app->GetMouseY();

    leftPaddle->GetBoxCollider2D(0).SetAbsolutePosition(newXPos, newYPos);
 */
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