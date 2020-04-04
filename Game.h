#ifndef LABPROGRCLION_GAME_H
#define LABPROGRCLION_GAME_H

#include "player.h"
#include "nodeMap.h"
class Game
{
protected:
    //Frame
    sf::RenderWindow* window;
    sf::VideoMode vMode;
    sf::Event event{};

    //Mappa
    nodeMap* mappa;
    std::string indirizzoMappa;

    //Background
    sf::RectangleShape background;
    sf::Texture background_texture;

    //Di quanti pixel spostare la mappa verso dx e verso sud?
    float scaleX , scaleY;
    float offsetX, offsetY;
    float gridSizeX, gridSizeY;

    player* hero;

public:
    Game(int config = 64);
    virtual ~Game();

    void update();
    void render(sf::RenderTarget* target);

    void run();

    //Testing
    nodeMap* getMap() const;
    player* getPlayer() const;
};


#endif //LABPROGRCLION_GAME_H