#pragma once
#include "Entity.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "Direction.h"



class Player : public Entity
{
public:

    Player(TextureManager* textures, int x, int y);

    ~Player() override
    {
        SDL_DestroyTexture(current);
        SDL_DestroyTexture(up);
        SDL_DestroyTexture(down);
        SDL_DestroyTexture(left);
        SDL_DestroyTexture(right);
        current = nullptr;
        up = nullptr;
        down = nullptr;
        left = nullptr;
        right = nullptr;
    }


    void handleInput(const Uint8* keys);
    virtual void update() override;
    void changeAnimation(Direction direction);
    virtual void render(SDL_Renderer* r) override;


    const int getGridX() const;
    const int getGridY() const;
    const int getX() const;
    const int getY() const;

    const Direction getDiretion() const;
    


private:
    SDL_Texture* current;
    SDL_Texture* up;
    SDL_Texture* down;
    SDL_Texture* left;
    SDL_Texture* right;


    // grid position (logic)
    int gridX;
    int gridY;

    //the regular x and y for cosmetics
  

    Direction direction = Direction::NONE;
    int framecount = 4;

  
};