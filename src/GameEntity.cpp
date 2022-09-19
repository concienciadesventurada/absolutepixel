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

			if (nullptr != m_colliders)
			{
				m_colliders->SetAbsolutePosition(x, y);
				m_colliders->SetDimensions(w, h);
			}
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

void GameEntity::AddCollider2D()
{
	m_colliders.push_back(new Collider2D());
}


TexturedRectangle& GameEntity::GetSprite()
{
	return *m_sprite;
}

Collider2D& GameEntity::GetCollider2D(size_t index)
{
	return *m_colliders[index];
}
