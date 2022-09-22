#ifndef TEXTUREDRECTANGLE_HPP
#define TEXTUREDRECTANGLE_HPP

#include <string>

// Third Party
#include <SDL2/SDL.h>

class TexturedRectangle {
public:
    // Constructor
    TexturedRectangle(SDL_Renderer* renderer, std::string filepath);
    // New constructor to parse SDL_SetColorKey / goes along with InitDefaults when not necessary
    TexturedRectangle(SDL_Renderer* renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey); 
    void InitDefaults();

    // Destructor
    ~TexturedRectangle();

    // Set position and dimensions
    void SetPosition(int x, int y);
    void SetDimensions(int w, int h);

    // Retrieve position coordinates.
    int GetPositionX();
    int GetPositionY();

    // Retrieve dimensions
    int GetWidth();
    int GetHeight();
        
    // Update every frame
    void Update();
    // Render
    void Render(SDL_Renderer* renderer);

private:
    inline SDL_Rect GetRectangle() const { return m_rectangle; }
    
    SDL_Rect m_rectangle;
    SDL_Texture* m_texture;

    int m_redColorKey, m_greenColorKey, m_blueColorKey;
};

#endif