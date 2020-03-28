#ifndef LABPROGRCLION_GAME_H
#define LABPROGRCLION_GAME_H

#include "player.h"
#include "Node_map.h"


class Game
{
private:
    //Frame
    sf::RenderWindow* window;
    sf::VideoMode vMode;
    sf::Event event{};

    //Mappa
    Node_map* mappa;

    //Game Character
    player* hero;

    //Background
    sf::RectangleShape background;
    sf::Texture background_texture;

    //Di quanti pixel spostare la mappa verso dx e verso sud?
    float offsetx;
    float offsety;
    float gridSize_x;
    float gridSize_y;

    sf::Vector2i* goal;
    sf::Vector2i* start;

public:
    Game();
    ~Game();

    void update();
    void render(sf::RenderTarget* target);

    void run();
};


#endif //LABPROGRCLION_GAME_H