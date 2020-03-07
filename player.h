//
// Created by giuseppe on 04/03/20.
//

#ifndef LABPROGRAMMAZIONE_PLAYER_H
#define LABPROGRAMMAZIONE_PLAYER_H

#include "entity.h"

class player : public entity
{
private:
    void check_bound();

    sf::Vector2f position;

    void initPlayer();

    sf::RectangleShape player_sprite;

    sf::RenderWindow* windw;
    sf::Vector2f window_size;


public:

    player(sf::RenderWindow* target);

    ~player();

    void drawPlayer(sf::RenderTarget* target);

    void move(sf::Vector2f pos) override;

    void handleInput();

};


#endif //LABPROGRAMMAZIONE_PLAYER_H
