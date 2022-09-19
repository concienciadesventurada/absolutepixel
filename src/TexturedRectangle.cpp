#include <string>
#include "TexturedRectangle.h"
#include "ResourceManager.h"

// Third Party
#include <SDL2/SDL.h>

// Constructor
TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, std::string filepath) 
{
    SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath);
    m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);
//    SDL_FreeSurface(retrieveSurface); // EJERCICIO: Crear un m�todo que libere la memoria
    InitDefaults();
}

TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey)
{
    SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath);

    SDL_SetColorKey(retrieveSurface, SDL_FALSE, SDL_MapRGB(retrieveSurface->format, redColorKey, greenColorKey, blueColorKey));

    m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);
//    SDL_FreeSurface(retrieveSurface); // EJERCICIO: Crear un m�todo que libere la memoria
    InitDefaults();

    m_redColorKey = redColorKey;
    m_greenColorKey = greenColorKey;
    m_blueColorKey = blueColorKey;
}

void TexturedRectangle::InitDefaults()
{
    m_rectangle.x = 0;  // Defaults to render if no parameterers passed.
    m_rectangle.y = 0;
    m_rectangle.w = 32;
    m_rectangle.h = 32;

    m_redColorKey = 0xFF;   // Defaults if no color key parameters provided.
    m_greenColorKey = 0x00;
    m_blueColorKey = 0xFF;
}


// Destructor
TexturedRectangle::~TexturedRectangle() {
    SDL_DestroyTexture(m_texture);
}

void TexturedRectangle::SetPosition(int x, int y)
{
    m_rectangle.x = x;
    m_rectangle.y = y;
}

void TexturedRectangle::SetDimensions(int w, int h)
{
    m_rectangle.w = w;
    m_rectangle.h = h;
}

int TexturedRectangle::GetPositionX()
{
    return m_rectangle.x;
}

int TexturedRectangle::GetPositionY()
{
    return m_rectangle.y;
}

int TexturedRectangle::GetWidth()
{
    return m_rectangle.w;
}

int TexturedRectangle::GetHeight()
{
    return m_rectangle.h;
}

void TexturedRectangle::Update() {

}

void TexturedRectangle::Render(SDL_Renderer* renderer)
{   
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}

