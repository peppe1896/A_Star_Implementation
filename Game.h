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
    sf::Event event;

    //Mappa
    Node_map* mappa;

    //Game Character
    player* hero;

    //Background
    sf::RectangleShape background;
    sf::Texture background_texture;
    bool show_bck;

public:
    Game();
    ~Game();

    void update();
    void render(sf::RenderTarget* target);

    void run();
};


#endif //LABPROGRCLION_GAME_H