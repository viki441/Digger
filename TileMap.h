#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "Constants.h"
#include "TextureManager.h"
#include "Direction.h"

#include <queue>
#include <unordered_map>
#include <vector>


enum class TileType //fix this with capital letters
{
    Empty = 0,
    DugV = 1,
    DugH = 2,
    DugFull = 3,
    Emerald = 4
};

struct Tile 
{
    TileType type;
    bool walkable;
};

struct Node
{
    int x, y;
};


class TileMap 
{
public:
    //INIT THINGS
    TileMap(int level, TextureManager* textures, int OY);
    void assignTiles(const std::string& filepath);


    //CHANGING
    void update();
    void render(SDL_Renderer* r);
    SDL_Texture* findCurrent(int row, int col);

    int dig(int gridX, int gridY, Direction direction);
    void setTile(int gridX, int gridY, TileType tile, bool walkable);

    //CHECKING
    bool isWalkable(int gridX, int gridY) const;
    const int getEmeraldsLeft() const;
    const std::string evaluateLevel(const int level);

    //ENEMY
    Direction findDirectionBFS(int ex, int ey, int px, int py) const;

    ~TileMap();

private:
    
    
    //EVALUATIONS


private:

    Tile tiles[Constants::ROWS][Constants::COLS];

    SDL_Texture* background;

    SDL_Texture* dugH;
    SDL_Texture* dugV;
    SDL_Texture* dugFull;
    SDL_Texture* emerald;

    int offsetY;
    int emeraldsLeft = 151; // too big unless user has custom level
};