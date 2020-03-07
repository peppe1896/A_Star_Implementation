//
// Created by giuseppe on 04/03/20.
//

#include <iostream>
#include "player.h"

player::player(sf::RenderWindow* target)
{
    windw = target;
    window_size.x = static_cast<float>(windw->getSize().x);
    window_size.y = static_cast<float>(windw->getSize().y);
    initPlayer();
}

player::~player()
{

}

void player::initPlayer()
{
    //Imposto vettore posizione
    position.x = 150.f;
    position.y = 150.f;

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

void player::handleInput()
{
    if(sf::Mouse::isButtonPressed((sf::Mouse::Right))) {
        //se premi tasto dx del mouse puoi muovere il player con WASD
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            position.y -= 5.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            position.y += 5.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            position.x -= 5.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            position.x += 5.f;
    }
    //Questa parte andrebbe rimossa per evitare

    check_bound(); //aggiorna il vettore position se tocca l'esterno

    player_sprite.setPosition(position);

}

void player::check_bound()
{
    if (position.x >= window_size.x - player_sprite.getSize().x)
        position.x = window_size.x - player_sprite.getSize().x;

    if (position.y > window_size.y - player_sprite.getSize().y)
        position.y = window_size.y - player_sprite.getSize().y;

    if (position.x <= 0.f)
        position.x = 0.f;

    if (position.y <= 0.f)
        position.y = 0.f;
}
/*
void player::put_in_grill()
{

}
*/

