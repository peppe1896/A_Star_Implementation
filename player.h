//
// Created by giuseppe on 04/03/20.
//

#ifndef LABPROGRAMMAZIONE_PLAYER_H
#define LABPROGRAMMAZIONE_PLAYER_H

#include "entity.h"
#include <queue>
#include "AutomaticControl.h"

class player : public entity
{
private:
    void check_bound();

    sf::Vector2f position;

    void initPlayer(float vel, float gridX, float gridY);

    sf::RectangleShape player_sprite;

    sf::RenderWindow* windw;
    sf::Vector2f window_size;

    float velocity;

    AutomaticControl* control;

public:
    player(sf::RenderWindow* target, float vel, float gridX, float gridY);
    ~player();

    void drawPlayer(sf::RenderTarget* target);

    void move(sf::Vector2f pos) override;

    void handleInput();

    void setVelocity(float velocity);

    sf::Vector2f getPosition();

    class AutomaticControl;
};


#endif //LABPROGRAMMAZIONE_PLAYER_H
