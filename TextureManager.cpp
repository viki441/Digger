#include "TextureManager.h"
#include <fstream>

TextureManager::TextureManager(SDL_Renderer* r)
    :renderer(r)
{

}

bool TextureManager::loadAllInMap(const std::string& filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open())
        return false;

    std::string id, path;

    while (file >> id >> path)
    {
        if (!load(id, path))
        {
            SDL_Log("Failed loading texture: %s", id.c_str());
            return false;
        }
    }

    return true;
}

TextureManager::~TextureManager()
{
    clear();
}

bool TextureManager::load(const std::string& id,
    const std::string& path)
{
    SDL_Texture* texture =
        IMG_LoadTexture(renderer, path.c_str());

    if (!texture)
    {
        SDL_Log("Failed to load texture: %s",
            IMG_GetError());

        return false;
    }

    textures[id] = texture;

    return true;
}

SDL_Texture* TextureManager::get(
    const std::string& id)
{
    auto it = textures.find(id);

    if (it == textures.end())
    {
        return nullptr;
    }

    return it->second;
}

void TextureManager::clear()
{
    for (auto& pair : textures)
    {
        SDL_DestroyTexture(pair.second);
    }

    textures.clear();
}