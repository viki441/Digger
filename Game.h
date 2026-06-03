#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Text.h"

class Game 
{
public:
    Game(int level);
    ~Game();
    bool init();
    int run();
    void clean();

private:
    bool isRunning = true;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    TextureManager* textures = nullptr;
    TileMap* map = nullptr;
    Player* player = nullptr;
    Text* text = nullptr;
    //Enemy* enemy = nullptr;
    EnemyManager* enemies = nullptr;

    int points = 0;
    int level;
    void handleEvents();
    void update();
    void render();
};