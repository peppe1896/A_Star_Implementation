//
// Created by giuseppe on 04/03/20.
//

#ifndef LABPROGRAMMAZIONE_ENTITY_H
#define LABPROGRAMMAZIONE_ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SFML/System.hpp"

class entity {

public:
    virtual void move(sf::Vector2f pos) = 0;


};


#endif //LABPROGRAMMAZIONE_ENTITY_H
