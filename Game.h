#ifndef LABPROGRCLION_GAME_H
#define LABPROGRCLION_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include "player.h"

class Game
{
private:
    sf::RenderWindow* window;
    sf::Event event;

    player* hero;


public:
    Game();
    ~Game();

    void updatePos();
    void update();
    void render();

    void run();
};


#endif //LABPROGRCLION_GAME_H