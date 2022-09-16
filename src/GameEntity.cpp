#include "GameEntity.h"
#include "Collider2D.h"

GameEntity::GameEntity()
{
	m_sprite = nullptr;
}

GameEntity::GameEntity(SDL_Renderer* renderer, std::string spritepath)
{
	m_renderer = renderer;
	m_sprite = new TexturedRectangle(m_renderer, spritepath);
	m_collider = new Collider2D();
}

// Destroy previous sprites and collisions to prevent memory leaks.
GameEntity::~GameEntity()
{
	if (nullptr != m_sprite)
	{
		delete m_sprite;
	}
	if (nullptr != m_collider)
	{
		delete m_collider;
	}
}

// Update the positions and dimentions so it coincides with the sprite component
void GameEntity::Update()
{
		if (nullptr != m_sprite)
		{
			int x = m_sprite->GetPositionX();
			int y = m_sprite->GetPositionY();
			int w = m_sprite->GetWidth();
			int h = m_sprite->GetHeight();

			if (nullptr != m_collider)
			{
				m_collider->SetAbsolutePosition(x, y);
				m_collider->SetDimensions(w, h);
			}
		}
}

void GameEntity::Render()
{
	if (nullptr != m_sprite)
	{
		m_sprite->Render(m_renderer);
	}
	if (nullptr != m_collider)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(m_renderer, &m_collider->GetColliderBoundingBox());
	}
}

TexturedRectangle& GameEntity::GetSprite()
{
	return *m_sprite;
}

Collider2D& GameEntity::GetCollider2D()
{
	return *m_collider;
}
