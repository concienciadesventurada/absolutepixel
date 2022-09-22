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
	void AddBoxCollider2D();

	//  Retrieve components
	TexturedRectangle& GetSprite();
	BoxCollider2D& GetBoxCollider2D(size_t index);

	// Note: Sets the position of our game entity
	//       This operates by moving all of the
	//       Components position as well so they are
	//       updated.   
	void SetPosition(int x, int y); 
	// Sets all of the components to a specified dimension
	void SetDimensions(int w, int h); 

private:
	TexturedRectangle* m_sprite;
	SDL_Renderer* m_renderer;

	std::vector<BoxCollider2D*> m_colliders;
};

#endif // !GAMEOBJECT_H

// Modified constructors to later pass components