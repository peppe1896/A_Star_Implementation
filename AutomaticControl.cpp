//
// Created by giuseppe on 30/03/20.
//

#include "AutomaticControl.h"

void AutomaticControl::updateAutoPosition()
{
    if(queue != nullptr && !queue->empty())
    {
        move_player();

        if(go_to_next)
            change_tile();
    }
}

AutomaticControl::AutomaticControl(player* hero)
{
    queue = &queue_player;
    actual_goal = &queue->front();
    go_to_next = false;

    hero_ = hero;
}

void AutomaticControl::move_player()
{
    if(!go_to_next && actual_goal != nullptr)
    {
        if(hero_->getPosition().x < static_cast<float>(actual_goal->x))
            hero_->move(sf::Vector2f(hero_->getPosition().x + 2.f, hero_->getPosition().y));

        if(hero_->getPosition().x > static_cast<float>(actual_goal->x))
            hero_->move(sf::Vector2f(hero_->getPosition().x - 2.f, hero_->getPosition().y));

        if(hero_->getPosition().y < static_cast<float>(actual_goal->y))
            hero_->move(sf::Vector2f(hero_->getPosition().x, hero_->getPosition().y + 2.f));

        if(hero_->getPosition().y > static_cast<float>(actual_goal->y))
            hero_->move(sf::Vector2f(hero_->getPosition().x, hero_->getPosition().y - 2.f));

        if(hero_->getPosition().x == actual_goal->x && hero_->getPosition().y == actual_goal->y)
        {
            go_to_next = true;
        }
    }
}

void AutomaticControl::change_tile()
{
    actual_goal = nullptr;
    queue->erase(queue->begin());
    actual_goal = &queue->front();
    go_to_next = false;
}
