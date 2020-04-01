//
// Created by giuseppe on 04/03/20.
//

#include <iostream>
#include "player.h"

player::player(sf::RenderWindow* target, float vel, float gridX, float gridY, Node_map* map_to_pass, float auto_, float manual_)
{

    windw = target;
    window_size.x = static_cast<float>(windw->getSize().x);
    window_size.y = static_cast<float>(windw->getSize().y);
    //Imposto vettore posizione
    position.x = window_size.x / 2 + player_sprite.getSize().x / 2;
    position.y = window_size.y / 2 + player_sprite.getSize().y / 2;

    //Disegno rectangle shape
    gridSizeX = gridX;
    gridSizeY = gridY;
    player_sprite.setFillColor(sf::Color::Black);
    player_sprite.setSize(sf::Vector2f(gridSizeX,gridSizeY));
    player_sprite.setOutlineThickness(1.f);
    player_sprite.setOutlineColor(sf::Color::Green);

    player_sprite.setPosition(position);

    setVelocity(vel);

    mappa = map_to_pass;

    actual_goal = nullptr;
    attach();

    auto_move_multipler = auto_;
    manual_move_multipler = manual_;

    autovelocity_x = velocity * auto_move_multipler;
    autovelocity_y = velocity * auto_move_multipler;
}

player::~player()
{
    detach();
}

void player::move(sf::Vector2f pos)
{
    player_sprite.setPosition(pos);
}

void player::move_(sf::Vector2f pos)
{
    position = pos;
}

void player::drawPlayer(sf::RenderTarget* target)
{
    target->draw(player_sprite);
}

void player::handleInput()
{
    if(!sf::Mouse::isButtonPressed((sf::Mouse::Right)))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            position.y -= velocity * manual_move_multipler;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            position.y += velocity * manual_move_multipler;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            position.x -= velocity * manual_move_multipler;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            position.x += velocity * manual_move_multipler;
    }

    updateAutoPosition();

    check_bound();

    player_sprite.setPosition(position);
}

void player::check_bound()
{
    //Ferma il player entro i confini della window
    //BLOCCA RIGHT
    if (position.x >= window_size.x - player_sprite.getSize().x)
        position.x = window_size.x - player_sprite.getSize().x;

    //BLOCCA DOWN
    if (position.y > window_size.y - player_sprite.getSize().y)
        position.y = window_size.y - player_sprite.getSize().y;

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
        move_player();
    }
    else
    {
        actual_goal = nullptr;
    }

}

void player::move_player()
{
    if(actual_goal != nullptr)
    {
        if (position.x == actual_goal->x && position.y == actual_goal->y)
        {
            actual_goal = nullptr;
            queue.erase(queue.begin());
            actual_goal = &queue.front();
        }

        if(position.x <= static_cast<float>(actual_goal->x) + (3*auto_move_multipler) || position.x <= static_cast<float>(actual_goal->x) - (3*auto_move_multipler))
        {
            autovelocity_x = 1.f;
            if (position.x < static_cast<float>(actual_goal->x))
            {
                position.x += (autovelocity_x);
            }
            if (position.x > static_cast<float>(actual_goal->x))
            {
                position.x -= (autovelocity_x);
            }
        }
        else
        {
            autovelocity_x = velocity * auto_move_multipler;

            if (position.x < static_cast<float>(actual_goal->x))
            {
                position.x += (autovelocity_x);
            }
            if (position.x > static_cast<float>(actual_goal->x))
            {
                position.x -= (autovelocity_x);
            }
        }
        if(position.y <= static_cast<float>(actual_goal->y) + (3*auto_move_multipler) || position.y <= static_cast<float>(actual_goal->y) - (3*auto_move_multipler))
        {
            autovelocity_y = 1.f;
            if (position.y < static_cast<float>(actual_goal->y))
            {
                position.y += (autovelocity_y);
            }
            if (position.y > static_cast<float>(actual_goal->y))
            {
                position.y -= (autovelocity_y);
            }
        }
        else
        {
            autovelocity_y = velocity * auto_move_multipler;

            if (position.y < static_cast<float>(actual_goal->y))
            {
                position.y += (autovelocity_y);
            }
            if (position.y > static_cast<float>(actual_goal->y))
            {
                position.y -= (autovelocity_y);
            }
        }

    }
}

void player::create_queue()
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
    create_queue();
}

void player::create_queue_test(std::vector<sf::Vector2f> mappa_queue)
{
    queue.clear();

    for(auto itr : mappa_queue)
        queue.emplace_back(static_cast<float>(itr.x * gridSizeX), static_cast<float>(itr.y * gridSizeY));
}


