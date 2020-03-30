//
// Created by giuseppe on 30/03/20.
//

#include "AutomaticControl.h"
/*
void AutomaticControl::updateAutoPosition()
{
    if(queue != nullptr && !queue->empty())
    {
        move_player();

        if(go_to_next)
            change_tile();
    }
}

AutomaticControl::AutomaticControl(sf::Vector2f* position_hero)
{
    position = position_hero;
    queue = &queue_player;
    actual_goal = &queue->front();
    go_to_next = false;
}

void AutomaticControl::move_player()
{
    if(!go_to_next && actual_goal != nullptr)
    {
        if(position->x < static_cast<float>(actual_goal->x))
            position->x += position->x + 2.f;

        if(position->x > static_cast<float>(actual_goal->x))
            position->y -= 2.f;

        if(position->y < static_cast<float>(actual_goal->y))
            position->y += 2.f;

        if(position->y > static_cast<float>(actual_goal->y))
            position->y -= 2.f;

        if(position->x == actual_goal->x && position->y == actual_goal->y)
            go_to_next = true;
    }
}

void AutomaticControl::change_tile()
{
    actual_goal = nullptr;
    queue->erase(queue->begin());
    actual_goal = &queue->front();
    go_to_next = false;
}
*/