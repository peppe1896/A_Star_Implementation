//
// Created by giuseppe on 04/03/20.
//

#include <iostream>
#include "player.h"

player::player(sf::RenderWindow* target, float vel, float gridX, float gridY, nodeMap* map_to_pass, float auto_, float manual_)
{

    windows = target;
    windowSize.x = static_cast<float>(windows->getSize().x);
    windowSize.y = static_cast<float>(windows->getSize().y);
    //Imposto vettore posizione
    position.x = windowSize.x / 2 + playerSprite.getSize().x / 2;
    position.y = windowSize.y / 2 + playerSprite.getSize().y / 2;

    //Disegno rectangle shape
    gridSizeX = gridX;
    gridSizeY = gridY;
    playerSprite.setFillColor(sf::Color::Black);
    playerSprite.setSize(sf::Vector2f(gridSizeX, gridSizeY));
    playerSprite.setOutlineThickness(1.f);
    playerSprite.setOutlineColor(sf::Color::Green);

    playerSprite.setPosition(position);

    setVelocity(vel);

    mappa = map_to_pass;

    actual_goal = nullptr;
    attach();

    autoMoveMultipler = auto_;
    manualMoveMultipler = manual_;

    autoVelocityX = velocity * autoMoveMultipler;
    autoVelocityY = velocity * autoMoveMultipler;
}

player::~player()
{
    detach();
}

void player::move(sf::Vector2f pos)
{
    playerSprite.setPosition(pos);
}

void player::move_(sf::Vector2f pos)
{
    position = pos;
}

void player::drawPlayer(sf::RenderTarget* target)
{
    target->draw(playerSprite);
}

void player::handleInput()
{
    if(!sf::Mouse::isButtonPressed((sf::Mouse::Right)))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            position.y -= velocity * manualMoveMultipler;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            position.y += velocity * manualMoveMultipler;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            position.x -= velocity * manualMoveMultipler;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            position.x += velocity * manualMoveMultipler;
    }

    updateAutoPosition();

    checkBound();

    playerSprite.setPosition(position);
}

void player::checkBound()
{
    //Ferma il player entro i confini della window
    //BLOCCA RIGHT
    if (position.x >= windowSize.x - playerSprite.getSize().x)
        position.x = windowSize.x - playerSprite.getSize().x;

    //BLOCCA DOWN
    if (position.y > windowSize.y - playerSprite.getSize().y)
        position.y = windowSize.y - playerSprite.getSize().y;

    //BLOCCA LEFT
    if (position.x <= 0.f)
        position.x = 0.f;

    //BLOCCA UP
    if (position.y <= 0.f)
        position.y = 0.f;
}

void player::setVelocity(float velocity)
{
    this->velocity = velocity;
}

//======================================================================================================================

void player::updateAutoPosition()
{
    if(!queue.empty())
    {
        if(actual_goal == nullptr)
        {
            actual_goal = &queue.front();
            std::cout << "Actual goal = " << actual_goal->x << " " << actual_goal->y << std::endl;
        }
        movePlayer();
    }
    else
    {
        actual_goal = nullptr;
    }

}

void player::movePlayer()
{
    if(actual_goal != nullptr)
    {
        if (position.x == actual_goal->x && position.y == actual_goal->y)
        {
            actual_goal = nullptr;
            queue.erase(queue.begin());
            actual_goal = &queue.front();
        }

        if(position.x <= static_cast<float>(actual_goal->x) + (3 * autoMoveMultipler) || position.x <= static_cast<float>(actual_goal->x) - (3 * autoMoveMultipler))
        {
            autoVelocityX = 1.f;
            if (position.x < static_cast<float>(actual_goal->x))
            {
                position.x += (autoVelocityX);
            }
            if (position.x > static_cast<float>(actual_goal->x))
            {
                position.x -= (autoVelocityX);
            }
        }
        else
        {
            autoVelocityX = velocity * autoMoveMultipler;

            if (position.x < static_cast<float>(actual_goal->x))
            {
                position.x += (autoVelocityX);
            }
            if (position.x > static_cast<float>(actual_goal->x))
            {
                position.x -= (autoVelocityX);
            }
        }
        if(position.y <= static_cast<float>(actual_goal->y) + (3 * autoMoveMultipler) || position.y <= static_cast<float>(actual_goal->y) - (3 * autoMoveMultipler))
        {
            autoVelocityY = 1.f;
            if (position.y < static_cast<float>(actual_goal->y))
            {
                position.y += (autoVelocityY);
            }
            if (position.y > static_cast<float>(actual_goal->y))
            {
                position.y -= (autoVelocityY);
            }
        }
        else
        {
            autoVelocityY = velocity * autoMoveMultipler;

            if (position.y < static_cast<float>(actual_goal->y))
            {
                position.y += (autoVelocityY);
            }
            if (position.y > static_cast<float>(actual_goal->y))
            {
                position.y -= (autoVelocityY);
            }
        }

    }
}

void player::createQueue()
{
    for(auto itr : mappa->queue_player)
        queue.emplace_back(static_cast<float>(itr.x * gridSizeX), static_cast<float>(itr.y * gridSizeY));

}

void player::attach()
{
    mappa->addObserver(this);
}

void player::detach()
{
    mappa->remObserver(this);
}

void player::update_observer()
{
    queue.clear();
    createQueue();
}

void player::create_queue_test(std::vector<sf::Vector2f> mappa_queue)
{
    queue.clear();

    for(auto itr : mappa_queue)
        queue.emplace_back(static_cast<float>(itr.x * gridSizeX), static_cast<float>(itr.y * gridSizeY));
}


