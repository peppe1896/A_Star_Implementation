//
// Created by giuseppe on 04/03/20.
//

#ifndef LABPROGRAMMAZIONE_PLAYER_H
#define LABPROGRAMMAZIONE_PLAYER_H

#include "nodeMap.h"
#include "Observer.h"
#include "entity.h"


class player : public entity, public Observer
{
private:
    nodeMap* mappa;

    void checkBound();

    sf::RectangleShape playerSprite;

    sf::RenderWindow* windows;
    sf::Vector2f windowSize;

    float autoMoveMultipler;
    float manualMoveMultipler;

    float velocity;
    float autoVelocityX;
    float autoVelocityY;
    float gridSizeX;
    float gridSizeY;

    sf::Vector2f position;

public:
    player(sf::RenderWindow* target, float vel, float gridX, float gridY, nodeMap* map_to_pass, float auto_multipler = 4.f, float manual_multipler = 5.f);
    virtual ~player();

    void drawPlayer(sf::RenderTarget* target);
    void move(sf::Vector2f pos) override;
    void move_(sf::Vector2f pos);
    void handleInput();
    void setVelocity(float velocity);

    //AUTOMATIC COMPONENT
private:
    std::vector<sf::Vector2f> queue;
    sf::Vector2f* actual_goal;

    void movePlayer();
    void createQueue();
public:
    void updateAutoPosition();

    //Observer methods
    void attach() override;
    void detach() override;
    void update_observer() override;

    //For tests
    sf::Vector2f getPosition() {return position;}
    void create_queue_test(std::vector<sf::Vector2f> mappa_queue);
    std::vector<sf::Vector2f> getQueue() {return queue;}
};


#endif //LABPROGRAMMAZIONE_PLAYER_H
