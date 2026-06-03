#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void update() = 0;
    virtual void render(SDL_Renderer* r) = 0;
    

protected:

    int frame = 0;
    int xpos;
    int ypos;

};