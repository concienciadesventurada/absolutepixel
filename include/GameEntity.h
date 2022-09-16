#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "TexturedRectangle.h"

class GameEntity
{
public:
	GameEntity();

	GameEntity(SDL_Renderer* renderer, std::string spritepath);

	~GameEntity();

	void Update();
	
	void Render();
	
	TexturedRectangle& GetSprite()
	{
		return *m_sprite;
	}

private:
	TexturedRectangle* m_sprite;
	SDL_Renderer* m_renderer;
};

#endif // !GAMEOBJECT_H