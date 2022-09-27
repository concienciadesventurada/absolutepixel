#ifndef DYNAMICTEXT_H
#define DYNAMICTEXT_H

#include <iostream>
#include <string>

// Third Party
#include <SDL2/SDL_ttf.h>

class DynamicText
{
    public:
        // Constructor
        DynamicText(std::string fontFilePath, size_t fontSize);

        // Destructor
        ~DynamicText();      

        // Function to draw the text passed
        void DrawText(SDL_Renderer* renderer, std::string stringText, int x, int y, int w, int h);

    private:
        // Rect, texture and surface in which we draw the font/text to
        SDL_Rect m_rectangle;
        SDL_Texture* m_texture;
        SDL_Surface* m_surface;

        // The font to be used.
        TTF_Font* m_Font;

        // Font to ensure SDL2_ttf is initialized once.
        static bool s_ttfInitialized;

};

#endif