#include "Collider2D.h"

SDL_Rect& Collider2D::GetColliderBoundingBox()
{
        return m_colliderRectangle;
}

SDL_bool Collider2D::IsColliding(Collider2D& collider)
{
        const SDL_Rect temp = collider.m_colliderRectangle;
        return SDL_HasIntersection(&m_colliderRectangle, &temp);  
}

void Collider2D::SetAbsolutePosition(int x, int y)
{
        m_colliderRectangle.x = x;
        m_colliderRectangle.y = y;
}

void Collider2D::SetDimensions(int w, int h)
{
        m_colliderRectangle.w = w;
        m_colliderRectangle.h = h;
}

int Collider2D::GetPositionX()
{
        return m_colliderRectangle.x;
}

int Collider2D::GetPositionY()
{
        return m_colliderRectangle.y;
}

void Update()
{

}

void Render()
{

}