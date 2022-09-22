#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <string>

// Third Party
#include <SDL2/SDL.h>

class AnimatedSprite
{
public:
	// Constructor
	AnimatedSprite(SDL_Renderer*& renderer, std::string filepath);
	//Destructor
	~AnimatedSprite();

	// Draw Method
	void Draw(int x, int y, int w, int h);

	// Select and play a given frame
	void PlayFrame(int x, int y, int w, int h, int frame);

	// Update every frame
	void Update();

	// Render
	void Render(SDL_Renderer*& renderer);

private:
	SDL_Rect m_src;	// The one we are selecting
	SDL_Rect m_dst;	// Dimensions of its render
	SDL_Texture* m_texture;

};

#endif // !ANIMATED_SPRITE.H