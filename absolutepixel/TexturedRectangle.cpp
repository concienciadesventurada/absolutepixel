#include <string>
#include "SDL.h"
#include "TexturedRectangle.h"
#include "ResourceManager.h"

// Constructor
TexturedRectangle::TexturedRectangle(SDL_Renderer*& renderer, std::string filepath) 
{
    SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface("assets/player_still.bmp");

    m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);
//    SDL_FreeSurface(retrieveSurface); // EJERCICIO: Crear un método que libere la memoria
}
// Destructor
TexturedRectangle::~TexturedRectangle() {
    SDL_DestroyTexture(m_texture);
}

void TexturedRectangle::SetRectangleProperties(int x, int y, int w, int h) {
    // Create a rectangle
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
}
// Copy Constructor..
// Copy assignment operator
void TexturedRectangle::Update() {

}

void TexturedRectangle::Render(SDL_Renderer*& renderer) {
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}