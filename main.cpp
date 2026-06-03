#include "Game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    int level = 1;
    while (level < 5)
    {
        try
        {
            Game game(level);

            if (!game.init()) {
                return -1;
            }

            level += game.run();
            game.clean();

   
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    }
    
    return 0;
}