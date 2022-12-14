#include "SDLApp.h"

#include <iostream>

SDLApp::SDLApp(Uint32 subsystemsFlags, const char* title, int x, int y, int w, int h)
{
    m_width = w;
    m_height = h;

    // Default value
    m_maxFrameRate = 60;

    // Initialize the video subsystem.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized: " <<
            SDL_GetError();
    }
    else {
        std::cout << "SDL video system is ready to go\n";
    }
    
    m_window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

SDLApp::~SDLApp()
{
    // Destroy our m_window
    SDL_DestroyWindow(m_window);
    // Quit our SDL application
    SDL_Quit();
}

void SDLApp::SetEventCallback(std::function<void(void)> func)
{
    m_EventCallback = func;
}

void SDLApp::SetUpdateCallback(std::function<void(void)> func)
{
    m_UpdateCallback = func;
}

void SDLApp::SetRenderCallback(std::function<void(void)> func)
{
    m_RenderCallback = func;
}

void SDLApp::RunLoop()
{
    while (m_gameIsRunning)
    {
        Uint32 start = SDL_GetTicks();

        Uint32 buttons;
        buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);

        // (1) Handle events first
        // User specifies what to do in the events callback
        m_EventCallback();

        // (2) Then handle updates
        m_UpdateCallback();

        // (3) Then handle our rendering
        // Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);

        // Do our drawing
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // What the user specifies to happen during the rendering
        // stage in this callback function
        m_RenderCallback();

        // Finally show what we've drawn
        SDL_RenderPresent(m_renderer);

        // Frame capping in milliseconds
        Uint32 elapsedTime = SDL_GetTicks() - start;
        if (elapsedTime < m_maxFrameRate)
        {
            SDL_Delay(m_maxFrameRate - elapsedTime);
        }
        
    }

}

void SDLApp::SetMaxFrameRate(int frameRate)
{
    m_maxFrameRate = frameRate;
}

SDL_Renderer* SDLApp::GetRenderer() const
{
	return m_renderer;
}

int SDLApp::GetMouseX()
{
	return m_mouseX;
}

int SDLApp::GetMouseY()
{
	return m_mouseY;
}

int SDLApp::GetWindowWidth()
{
    return m_width;
}

int SDLApp::GetWindowHeight()
{
    return m_height;
}

void SDLApp::StopAppLoop()
{
    m_gameIsRunning = false;
}
