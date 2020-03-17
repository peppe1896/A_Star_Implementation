//
// Created by giuseppe on 04/03/20.
//

#include <iostream>
#include "player.h"

player::player(sf::RenderWindow* target, float vel, float gridX, float gridY)
{
    windw = target;
    window_size.x = static_cast<float>(windw->getSize().x);
    window_size.y = static_cast<float>(windw->getSize().y);
    initPlayer(vel, gridX, gridY);
}

player::~player()
{

}

void player::initPlayer(float vel, float gridX, float gridY)
{
    //Imposto vettore posizione
    position.x = window_size.x / 2 + player_sprite.getSize().x / 2;
    position.y = window_size.y / 2 + player_sprite.getSize().y / 2;

    //Disegno rectangle shape
    player_sprite.setFillColor(sf::Color::Red);
    player_sprite.setSize(sf::Vector2f(gridX + 10.f,gridY));
    player_sprite.setOutlineThickness(0.f);
    player_sprite.setOutlineColor(sf::Color::Red);

    player_sprite.setPosition(position);

    setVelocity(vel);
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
            position.y -= velocity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            position.y += velocity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            position.x -= velocity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            position.x += velocity;
    }
    //Questa parte andrebbe rimossa per evitare

    check_bound(); //aggiorna il vettore position se tocca l'esterno

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
/*
void player::put_in_grill()
{

}
*/

