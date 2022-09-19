#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

#include "TexturedRectangle.h"
#include "Collider2D.h"

class GameEntity
{
public:
	// Constructors
	GameEntity();
	GameEntity(SDL_Renderer* renderer);
	
	// Destructors
	~GameEntity();

	// Update method called every loop
	void Update();
	
	// Render the Game Entity (in the render portion)
	void Render();
	
	// Adding components
	void AddTexturedRectangleComponent(std::string spritepath);
	void AddTexturedRectangleComponent(std::string spritepath, int redColorKey, int greenColorKey, int blueColorKey);
	void AddCollider2D();

	//  Retrieve components
	TexturedRectangle& GetSprite();
	Collider2D& GetCollider2D(size_t index);

private:
	TexturedRectangle* m_sprite;
	SDL_Renderer* m_renderer;

	std::vector<Collider2D*> m_colliders;
};

#endif // !GAMEOBJECT_H

// Modified constructors to later pass components