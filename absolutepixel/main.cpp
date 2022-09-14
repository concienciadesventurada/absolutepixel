// C++ Standard Libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>
// Third Party
#include <SDL.h> 

#include "TexturedRectangle.h"
#include "AnimatedSprite.h"


int main(int argc, char* argv[]) {
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window = nullptr;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " <<
            SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    AnimatedSprite animatedSprite(renderer, "assets/player_idle-walking.bmp");
    AnimatedSprite tim(renderer, "assets/tim_idle.bmp");
    animatedSprite.Draw(200, 200, 128, 128);
    tim.Draw(300, 200, 128, 128);


    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while (gameIsRunning) {
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while (SDL_PollEvent(&event)) {
            // Handle each specific event
            if (event.type == SDL_QUIT) {
                gameIsRunning = false;
            }
        }
        // (2) Handle Updates

        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Do our drawing
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

        static int frameNumber = 0; // Counter to choose which frame we're on.

        animatedSprite.PlayFrame(0, 0, 32, 32, frameNumber);
        animatedSprite.Render(renderer);
        tim.PlayFrame(128, 0, 32, 32, frameNumber);
        tim.Render(renderer);
        frameNumber++;
        if (frameNumber > 8) {
            frameNumber = 0;
        }


        // Finally show what we've drawn
        SDL_RenderPresent(renderer);

        SDL_Delay(150);
    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);

    // our program.
    SDL_Quit();
    return 0;
}