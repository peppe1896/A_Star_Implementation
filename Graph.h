//
// Created by giuseppe on 18/03/20.
//

#ifndef LABPROGRAMMAZIONE_GRAPH_H
#define LABPROGRAMMAZIONE_GRAPH_H

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


struct GridLocation //preferisco usare sf::Vector2i
{
    int x, y;
};


//======================================================================================================================

class Tile
{
public:
    Tile(float x, float y, float width, float heigth, int peso = 1);
    Tile(sf::Vector2i in, float gridSize = 11.f, int peso = 1);
    Tile(int x, int y, float gridSize = 11.f, int peso = 1);
    sf::Vector2f getPosition();
    sf::RectangleShape shape;
    sf::Texture tex;
    sf::Vector2i location{};
    std::string id;

    int weight;
    void setColor(sf::Color colortile);

    bool operator==(Tile* a);
    bool operator!=(Tile* a);
};

#endif //LABPROGRAMMAZIONE_GRAPH_H
