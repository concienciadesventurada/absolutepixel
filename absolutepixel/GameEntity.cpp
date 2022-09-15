#include "GameEntity.h"

GameEntity::GameEntity()
{
	m_sprite = nullptr;
}

GameEntity::GameEntity(SDL_Renderer* renderer, std::string spritepath)
{
	m_renderer = renderer;
	m_sprite = new TexturedRectangle(m_renderer, spritepath);
}

GameEntity::~GameEntity()
{
}

void GameEntity::Update()
{
}

void GameEntity::Render()
{
	if (nullptr != m_sprite)
	{
		m_sprite->Render(m_renderer);
	}
}
