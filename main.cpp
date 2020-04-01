#include "Game.h"
enum CONFIGURATIONS{CONF0 = 0, CONF1, CONF2 };

int main()
{
    //          SELECT A NUMBER FROM 0 TO 2
    //                    |
    //                    V
    Game* game = new Game(0);
    game->run();
}

