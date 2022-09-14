#ifndef RESOURCE_MANAGER_H
#define	RESOURCE_MANAGER_H
#include <vector>
#include <unordered_map>

// Third Party
#include "SDL.h"

class ResourceManager
{
private:
	ResourceManager();
	ResourceManager(ResourceManager const&); // Make sure it is not able to be created
	ResourceManager operator=(ResourceManager const&);	// Avoid copy assingment operator

	std::unordered_map<std::string, SDL_Surface*> m_surfaces;	// UN_MAP que utiliza como key la ruta de la imagen a cargar.

public:
	static ResourceManager& GetInstance();	// Retorna una referencia a algún RM.

	SDL_Surface* GetSurface(std::string filepath);	// Retrieves a particular instance

};


#endif // !RESOURCE_MANAGER_H
