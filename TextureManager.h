#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <unordered_map>

class TextureManager
{
public:
    TextureManager(SDL_Renderer* r);
    ~TextureManager();

    bool load(const std::string& id, const std::string& path);
    SDL_Texture* get(const std::string& id);
    void clear();
    bool loadAllInMap(const std::string& filepath);

private:
    SDL_Renderer* renderer;
    
    std::unordered_map<std::string, SDL_Texture*> textures;
};