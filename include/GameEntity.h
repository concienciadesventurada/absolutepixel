#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "TexturedRectangle.h"
#include "Collider2D.h"

class GameEntity
{
public:
	// Constructors
	GameEntity();
	GameEntity(SDL_Renderer* renderer, std::string spritepath);
	
	// Destructors
	~GameEntity();

	// Update method called every loop
	void Update();
	
	// Render the Game Entity (in the render portion)
	void Render();
	
	TexturedRectangle& GetSprite();

	Collider2D& GetCollider2D();

private:
	TexturedRectangle* m_sprite;
	SDL_Renderer* m_renderer;

	Collider2D* m_collider;
};

#endif // !GAMEOBJECT_H