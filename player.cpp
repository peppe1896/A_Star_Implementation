//
// Created by giuseppe on 04/03/20.
//

#include <iostream>
#include "player.h"

player::player()
{
    initPlayer();
}

player::~player()
{

}

void player::initPlayer()
{
    //Imposto vettore posizione
    position.x = 0.f;
    position.y = 0.f;

    //Disegno rectangle shape
    player_sprite.setFillColor(sf::Color::Red);
    player_sprite.setSize(sf::Vector2f(50.f,50.f));
    player_sprite.setOutlineThickness(1.f);
    player_sprite.setOutlineColor(sf::Color::Yellow);

    player_sprite.setPosition(position);
}

void player::move(sf::Vector2f pos)
{
    player_sprite.setPosition(pos);
}

void player::drawPlayer(sf::RenderTarget* target)
{
    target->draw(player_sprite);
}

void player::reach()
{
    std:out << "Commit di prova" << std::endl;
}

void player::handleInput()
{
    //if(!sf::Mouse::isButtonPressed((sf::Mouse::Right))) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        position.y -= 3.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        position.y += 3.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        position.x -= 3.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        position.x += 3.f;

    player_sprite.setPosition(position);
}


