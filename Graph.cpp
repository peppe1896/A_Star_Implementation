//
// Created by giuseppe on 21/03/20.
//
#include "Graph.h"

Tile::Tile(float x, float y, float width, float heigth, int peso)
{
    shape.setSize(sf::Vector2f(width, heigth));
    shape.setPosition(x,y);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(0.f);
    shape.setOutlineColor(sf::Color::Blue);

    id = std::to_string(static_cast<int>(x/11.f)) + std::to_string(static_cast<int>(y/11.f));

    location.x = static_cast<int>(x/11.f);
    location.y = static_cast<int>(y/11.f);

    weight = peso;
    //std::cout << "x = " << location.x << " y = " << location.y << std::endl;
    //std::cout << "ID = " << id << std::endl;
}

Tile::Tile(GridLocation in, float gridSize, int peso)
{
    shape.setSize(sf::Vector2f(gridSize, gridSize));
    shape.setPosition(in.x * static_cast<int>(gridSize),in.y * static_cast<int>(gridSize));
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(0.f);
    shape.setOutlineColor(sf::Color::Blue);

    id = std::to_string(in.x) + std::to_string(in.y);

    location.x = in.x;
    location.y = in.y;

    weight = peso;
    //std::cout << "x = " << location.x << " y = " << location.y << std::endl;
    //std::cout << "ID = " << id << std::endl;
}

Tile::Tile(int x, int y, float gridSize, int peso)
{
    shape.setSize(sf::Vector2f(gridSize, gridSize));
    shape.setPosition(x * static_cast<int>(gridSize),y * static_cast<int>(gridSize));
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(0.f);
    shape.setOutlineColor(sf::Color::Blue);

    id = std::to_string(x) + std::to_string(y);

    location.x = x;
    location.y = y;

    weight = peso;
    //std::cout << "x = " << location.x << " y = " << location.y << std::endl;
    //std::cout << "ID = " << id << std::endl;
}

sf::Vector2f Tile::getPosition()
{
    return shape.getPosition();
}

void Tile::setColor(sf::Color color)
{
    shape.setFillColor(color);
}

bool Tile::operator==(Tile *a)
{
    return id == a->id;
}

bool Tile::operator!=(Tile *a)
{
    return id != a->id;
}