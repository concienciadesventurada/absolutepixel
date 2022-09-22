#include "GameEntity.h"
#include "Collider2D.h"

GameEntity::GameEntity()
{
	m_sprite = nullptr;
}

GameEntity::GameEntity(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	m_sprite = nullptr;
}

// Destroy previous sprites and collisions to prevent memory leaks.
GameEntity::~GameEntity()
{
	if (nullptr != m_sprite)
	{
		delete m_sprite;
	}

	for (int i = 0; i < m_colliders.size(); ++i)	// TODO: Make auto&
	{
		delete m_colliders[i];
	}

}

// Update the positions and dimentions so it coincides with the sprite component
void GameEntity::Update()
{
/* 		if (nullptr != m_sprite)
		{
			int x = m_sprite->GetPositionX();
			int y = m_sprite->GetPositionY();
			int w = m_sprite->GetWidth();
			int h = m_sprite->GetHeight();

		} */
}

void GameEntity::Render()
{
	if (nullptr != m_sprite)
	{
		m_sprite->Render(m_renderer);
	}

	for (int i = 0; i < m_colliders.size(); ++i)	// Make auto&
	{
		if (nullptr != m_colliders[i])
		{
			SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawRect(m_renderer, &m_colliders[i]->GetColliderBoundingBox());
		}
	}

}

void GameEntity:: AddTexturedRectangleComponent(std::string spritepath)
{
	m_sprite = new TexturedRectangle(m_renderer, spritepath);
}

void GameEntity::AddTexturedRectangleComponent(std::string spritepath, int redColorKey, int greenColorKey, int blueColorKey)
{
	m_sprite = new TexturedRectangle(m_renderer, spritepath, redColorKey, greenColorKey, blueColorKey);

}

void GameEntity::AddBoxCollider2D()
{
	m_colliders.push_back(new BoxCollider2D());
}


TexturedRectangle& GameEntity::GetSprite()
{
	return *m_sprite;
}

BoxCollider2D& GameEntity::GetBoxCollider2D(size_t index)
{
	return *m_colliders[index];
}

// Sets all of the components to a specified dimension
void GameEntity::SetPosition(int x, int y)
{
    if	(nullptr!=m_sprite)
	{
        m_sprite->SetPosition(x,y);
    }
    
	for	(int i=0; i < m_colliders.size();i++)
	{
        if	(nullptr != m_colliders[i])
		{
            m_colliders[i]->SetAbsolutePosition(x, y);
        }
    }
}
void GameEntity::SetDimensions(int w, int h)
{
    if	(nullptr != m_sprite)
	{
        m_sprite->SetDimensions(w, h);
    }
    for	(int i=0; i < m_colliders.size();i++)
	{
        if	(nullptr != m_colliders[i])
		{
            m_colliders[i]->SetDimensions(w, h);
        }
    }
}