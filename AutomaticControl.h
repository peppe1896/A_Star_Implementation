//
// Created by giuseppe on 30/03/20.
//

#ifndef LABPROGRAMMAZIONE_AUTOMATICCONTROL_H
#define LABPROGRAMMAZIONE_AUTOMATICCONTROL_H

#include "Game.h"

class AutomaticControl
{
private:
    std::vector<sf::Vector2i>* queue;
    sf::Vector2i* actual_goal;
    void move_player();
    bool go_to_next;
    player* hero_;

    void change_tile();

public:
    AutomaticControl(player* player);
    void updateAutoPosition();
};


#endif //LABPROGRAMMAZIONE_AUTOMATICCONTROL_H
