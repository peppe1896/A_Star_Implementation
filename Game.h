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
    //Frame
    sf::RenderWindow* window;
    sf::VideoMode vMode;
    sf::Event event;

    //Game Character
    player* hero;

    //Background
    sf::RectangleShape background;
    sf::Texture background_texture;

public:
    Game();
    ~Game();

    void update();
    void render(sf::RenderTarget* target);


    sf::VideoMode getVideoMode();
    void run();
};


#endif //LABPROGRCLION_GAME_H