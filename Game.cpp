#include "Game.h"
#include "Constants.h"
#include <iostream>
#include <string>

Game::Game(int level)
    :level(level)
{}


bool Game::init() 
{


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL init failed\n";
        return false;
    }

    window = SDL_CreateWindow(
        "Digger Clone",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Constants::GAME_WIDTH, Constants::GAME_HEIGHT + Constants::MAP_OFFSET_Y,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cout << "Window failed\n";
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        std::cout << "Renderer failed\n";
        return false;
    }


    textures = new TextureManager(renderer);
    textures->loadAllInMap("C:\\Users\\vikik\\source\\repos\\newDigger\\assets\\images\\allTextures.txt");
   
    map = new TileMap(level, textures, Constants::MAP_OFFSET_Y);
    player = new Player(textures, 64, 564);
    text = new Text(textures, 0,0);
    //enemy = new Enemy(textures);
    enemies = new EnemyManager(textures);


    return true;
}

int Game::run() {
    Uint32 frameStart;
    int frameTime;

    while (isRunning) 
    {
        frameStart = SDL_GetTicks();

        update();
        handleEvents();
       
        render();

        frameTime = SDL_GetTicks() - frameStart;

        if (Constants::DELTA_TIME > frameTime)
            SDL_Delay(Constants::DELTA_TIME - frameTime);

        //all sorts of outcomes:
        /*
        emeralds collected,
        enemies destroyed,
        game over from enemy
        game over from bag
        */

        if (map->getEmeraldsLeft() == 0) //or enemies destroyed
        {
            return 1;
        }
    }
    return 0;
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false; break;
    default: break;
    }
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    player->handleInput(keystate);
}

void Game::update() {
   
    points += 25 * map->dig(player->getX(), player->getY(), player->getDiretion());
    player->update();
    //enemy->update();
    //enemy->update(*map, player->getGridX(), player->getGridY());
    for (int i = 0; i < enemies->getCurrentCount(); i++)
    {       
        enemies->getCurrentEnemy(i)->update();
        enemies->getCurrentEnemy(i)->update(*map, player->getGridX(), player->getGridY());
        enemies->updateTime();
    }
   
    
    //std::cout << "Points: " << points << std::endl;
    //map->update();
}

void Game::render() {

    
    SDL_RenderClear(renderer);
    map->render(renderer);
    player->render(renderer);
    //enemy->render(renderer);
    for (int i = 0; i < enemies->getCurrentCount(); i++)
    {
        enemies->getCurrentEnemy(i)->render(renderer);
    }


    text->render(renderer, 0, 0, std::to_string(points));
    // draw game objects here

    SDL_RenderPresent(renderer);
}

void Game::clean() 
{  
    delete textures; textures = nullptr;
    delete map; map = nullptr;
    delete player; player = nullptr;
    delete text; text = nullptr;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Game::~Game()
{
    clean();
}