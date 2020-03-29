//
// Created by giuseppe on 04/03/20.
//

#ifndef LABPROGRAMMAZIONE_PLAYER_H
#define LABPROGRAMMAZIONE_PLAYER_H

#include "entity.h"

#include <queue>

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

    std::vector<sf::Vector2i> queue;

    sf::Vector2f _2i_to_2f(sf::Vector2i change);

    bool reach_tile(sf::Vector2f tile_to_reach);
public:

    player(sf::RenderWindow* target, float vel, float gridX, float gridY);

    ~player();

    void drawPlayer(sf::RenderTarget* target);

    void move(sf::Vector2f pos) override;

    void handleInput();

    void setVelocity(float velocity);

    void setqueue(std::vector<sf::Vector2i> in);
};


#endif //LABPROGRAMMAZIONE_PLAYER_H
