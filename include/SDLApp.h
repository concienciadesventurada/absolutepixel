#ifndef SDLAPP_H
#define SDLAPP_H

#include <iostream>
#include <functional>


// Third Party
#include <SDL2/SDL.h>

class SDLApp {
public:
    // Constructor
    SDLApp(Uint32 subsystemsFlags, const char* title, int x, int y, int w, int h);

    // Destructor
    ~SDLApp();

    // Handle Events
    void SetEventCallback(std::function<void(void)> func);

    // Handle Updates
    void SetUpdateCallback(std::function<void(void)> func);

    // Handle Render
    void SetRenderCallback(std::function<void(void)> func);

    // Loop our application
    void RunLoop();

    // Frame cap - maximum render frame rate.
    void SetMaxFrameRate(int frameRate);

    // Retrive the renderer
    SDL_Renderer* GetRenderer() const;

    // Return mouse positions
    int GetMouseX();
    int GetMouseY();

    // Return window dimensions
    int GetWindowWidth();
    int GetWindowHeight();

    // Stop the main loop of our application
    void StopAppLoop();


private:
    // Pointer to our SDL Window
    SDL_Window* m_window = nullptr;

    // Pointer to our SDL renderer
    SDL_Renderer* m_renderer = nullptr;

    // Infinite loop for our application
    bool m_gameIsRunning = true;

    // Store frame cap
    int m_maxFrameRate;

    // Store mouse Coordinates by default
    int m_mouseX, m_mouseY;

    // Store width and height of window
    int m_width, m_height;

    // Store our callback functions
    std::function<void(void)> m_EventCallback;
    std::function<void(void)> m_UpdateCallback;
    std::function<void(void)> m_RenderCallback;
};


#endif // !SDLAPP_H
