//
// Created by giuseppe on 14/03/20.
//

#ifndef LABPROGRAMMAZIONE_NODE_MAP_H
#define LABPROGRAMMAZIONE_NODE_MAP_H

//#include "A_Star.h"
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


struct SimpleGraph
{
    std::unordered_map<char, std::vector<char> > edges;

    std::vector<char> neighbors(char id) {
        return edges[id];
    }
};
struct GridLocation
{
    int x, y;
};

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
    template <> struct hash<GridLocation> {
        typedef GridLocation argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const GridLocation& id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 4));
        }
    };
}

class Node_map;

class Tile
{
public:
    sf::RectangleShape shape;

public:
    Tile(float x, float y, float width, float heigth);
    sf::Vector2f getOrigin();

};

class Node_map
{
private:
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;
    sf::Font mouse_font;
    sf::Text mouse_text;

    sf::RenderWindow* window;

    float gridSizeX;
    float gridSizeY;
    std::vector<Tile*> tiles;

    bool checkIntersect(Tile* rect);

public:
    Node_map(sf::RenderWindow* window);
    ~Node_map();

    void addTile();
    void update();
    void render(sf::RenderTarget* target);
    friend class Tile;
};


#endif //LABPROGRAMMAZIONE_NODE_MAP_H
