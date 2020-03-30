//
// Created by giuseppe on 04/03/20.
//

#ifndef LABPROGRAMMAZIONE_PLAYER_H
#define LABPROGRAMMAZIONE_PLAYER_H

#include "Node_map.h"
#include "Observer.h"
#include "entity.h"


class player : public entity, public Observer
{
private:
    Node_map* mappa;

    void check_bound();

    sf::RectangleShape player_sprite;

    sf::RenderWindow* windw;
    sf::Vector2f window_size;

    float velocity;
    float gridSizeX;
    float gridSizeY;

    sf::Vector2f* position;

public:
    player(sf::RenderWindow* target, float vel, float gridX, float gridY, Node_map* map_to_pass);
    virtual ~player();

    void drawPlayer(sf::RenderTarget* target);
    void move(sf::Vector2f pos) override;
    void handleInput();
    void setVelocity(float velocity);

    //AUTOMATIC COMPONENT
private:
    std::vector<sf::Vector2f> queue;
    sf::Vector2f* actual_goal;

    void move_player();
    bool go_to_next;
    void change_tile();
    void create_queue();
public:
    void updateAutoPosition();

    //Observer methods
    void attach() override;
    void detach() override;
    void update_observer() override;
};


#endif //LABPROGRAMMAZIONE_PLAYER_H
