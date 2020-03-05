//
// Created by giuseppe on 04/03/20.
//

#ifndef LABPROGRAMMAZIONE_PLAYER_H
#define LABPROGRAMMAZIONE_PLAYER_H

#include "entity.h"

class player : public entity
{
private:
    sf::Vector2f position;

    void initPlayer();

    sf::RectangleShape player_sprite;

public:
    player();

    virtual ~player();

    void reach(); //Va implementata nelle altre entità

    void drawPlayer(sf::RenderTarget* target);

    void move(sf::Vector2f pos) override;

    void handleInput();

};


#endif //LABPROGRAMMAZIONE_PLAYER_H
