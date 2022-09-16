#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::ResourceManager(ResourceManager const&)
{

}

ResourceManager ResourceManager::operator=(ResourceManager const& rhs)
{
    //TO DO: Although it is not necessary in a singleton.
    return *this;
}

// Instantiate exactly 1 instances of this class in a Singleton desing pattern
ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager* s_instance = new ResourceManager;
    return *s_instance;
}

SDL_Surface* ResourceManager::GetSurface(std::string filepath)
{
    // Looking through m_surfaces as an unordered_map and check if a file exists
    // If it does, returns the associated surface. ** For the future: globally unique identifiers.

    auto search = m_surfaces.find(filepath); // Busca el filepath en el unordered_map

    if (search != m_surfaces.end()) // SI NO existe:
    {
        return m_surfaces[filepath];    // Crea [] el espacio en memoria
    }
    else // Allocate el archivo en memoria
    {
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        m_surfaces.insert(std::make_pair(filepath, surface));   // Crea un par de acuerdo a las keys

        return m_surfaces[filepath];    // Lo añade al mapa

    }

    return nullptr;

}
