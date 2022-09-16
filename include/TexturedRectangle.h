#pragma once
#include <string>

// Third Party
#include <SDL2/SDL.h>

class TexturedRectangle {
public:
    // Constructor
    TexturedRectangle(SDL_Renderer* renderer, std::string filepath);
    // Destructor
    ~TexturedRectangle();

    void SetPosition(int x, int y);

    void SetDimensions(int w, int h);

    SDL_bool IsColliding(TexturedRectangle& obj);
        
    // Update every frame
    void Update();
    // Render
    void Render(SDL_Renderer* renderer);

private:
    inline SDL_Rect GetRectangle() const { return m_rectangle; }
    SDL_Rect m_rectangle;
    SDL_Texture* m_texture;
};