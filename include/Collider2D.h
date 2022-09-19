#ifndef COLLIDER_2D_H
#define COLLIDER_2D_H

#include "TexturedRectangle.h"

// Third Party
#include <SDL2/SDL.h>

class Collider2D
{
public:
    Collider2D();

    ~Collider2D();

    SDL_Rect& GetColliderBoundingBox();

    // Detect collision
    SDL_bool IsColliding(Collider2D& collider);   

    // Absolute coordinates of the window to calculate collision
    void SetAbsolutePosition(int x, int y) ;

    void SetDimensions(int w, int h);

    // Retrieve positions.
    int GetPositionX();
    int GetPositionY();

    // Just to standarize the API and make things easier along the way
    void Update();
    void Render();

private:
    SDL_Rect* m_colliderRectangle;

};

#endif