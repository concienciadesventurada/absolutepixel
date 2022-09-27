#include "DynamicText.h"

bool DynamicText::s_ttfInitialized = false;

// Text usually is an expensive operation since it changes constantly, so the process
// of allocating, rendering, changing and deleting is.

DynamicText::DynamicText(std::string fontFilePath, size_t fontSize)
{

    if(!s_ttfInitialized && TTF_Init() == -1)
    {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else
    {
        //std::cout << "SDL text system is ready to go\n";
        // Initialize TTF system once in a singleton pattern design.
        s_ttfInitialized = true;
    }

    m_Font = TTF_OpenFont(fontFilePath.c_str(), fontSize);
    
    if (m_Font == nullptr)
    {
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }

}

DynamicText::~DynamicText()
{
    // Destroys textured text
    SDL_DestroyTexture(m_texture);

    // Close font subsystem
    TTF_CloseFont(m_Font);
}

void DynamicText::DrawText(SDL_Renderer* renderer, std::string stringText, int x, int y, int w, int h)
{
    // Pixels from our text
    m_surface = TTF_RenderText_Solid(m_Font, stringText.c_str(), {255, 255, 255});

    // Setup textured text
    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);

    // Free surface once uploaded to texture
    SDL_FreeSurface(m_surface);

    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
    
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);

    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
    }

}