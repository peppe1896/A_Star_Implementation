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

    float auto_move_multipler;
    float manual_move_multipler;

    float velocity;
    float autovelocity;
    float gridSizeX;
    float gridSizeY;

    sf::Vector2f* position;

public:
    player(sf::RenderWindow* target, float vel, float gridX, float gridY, Node_map* map_to_pass, float auto_multipler = 4.f, float manual_multipler = 5.f);
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
    void create_queue();
public:
    void updateAutoPosition();

    //Observer methods
    void attach() override;
    void detach() override;
    void update_observer() override;

    //For tests
    sf::Vector2f getPosition() {return *position;}
    void create_queue_test(std::vector<sf::Vector2i> mappa_queue);
    std::vector<sf::Vector2f> getQueue() {return queue;}
};


#endif //LABPROGRAMMAZIONE_PLAYER_H
