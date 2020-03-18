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
#include "Graph.h"

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
    std::unordered_map<Tile*, std::vector<Tile*>> tiles_graph;

    TileGraph graph;

    bool checkIntersect(Tile* rect);
    std::vector<Tile*> get_neighbor(Tile* tile);

public:
    friend class Tile;

    Node_map(sf::RenderWindow* window,  float gridX, float gridY);
    ~Node_map();

    void addTile();
    void remTile();

    void saveTree(const std::string filename);
    void loadTree(const std::string filename);

    void update();
    void renderMap(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);

};


#endif //LABPROGRAMMAZIONE_NODE_MAP_H
