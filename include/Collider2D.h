#ifndef COLLIDER_2D_H
#define COLLIDER_2D_H

#include "TexturedRectangle.h"
#include "Vector2D.h"

// Third Party
#include <SDL2/SDL.h>


class ICollider2D // I stands for Interface. Abstract class to be able to render convex forms
{
    public:
        virtual void Update() = 0;
        virtual void Render() = 0;  
};

class BoxCollider2D : public ICollider2D
{
    public:
    // Default constructor
    BoxCollider2D();
    // Destructor
    ~BoxCollider2D();

    // Retrieve bounding box rectangle
    SDL_Rect& GetColliderBoundingBox();
    // Set the collider position (def: top-left corner)
    SDL_bool IsColliding(BoxCollider2D& collider);

    // Absolute coordinates of the window to calculate collision
    void SetAbsolutePosition(int x, int y) ;

    void SetDimensions(int w, int h);

    // Sets the BB around the surface calculating min and max x and y values
    Vector2D SetBoundingBoxAuto(SDL_Surface* surface, Uint8 red, Uint8 green, Uint8 blue);

    void Update();
    void Render();

    private:
    SDL_Rect* m_colliderRectangle;

};

#endif