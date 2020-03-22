//
// Created by giuseppe on 14/03/20.
//

#ifndef LABPROGRAMMAZIONE_NODE_MAP_H
#define LABPROGRAMMAZIONE_NODE_MAP_H

//#include "A_Star.h"
#include "Graph.h"

static std::unordered_map<Tile*, std::vector<Tile*>> tiles_graph;

struct SquareGrid {
    static std::array<GridLocation, 4> DIRS;

    int width, height;
    std::unordered_set<GridLocation> walls;

    SquareGrid(int width_, int height_)
            : width(width_), height(height_) {}

    bool in_bounds(GridLocation id) const {
        return true;
    }

    bool passable(GridLocation id) const {
        return true;
    }

    std::vector<GridLocation> neighbors(GridLocation id) const {
        std::vector<GridLocation> results;
        //create a new tile to pass to the unordered_map
        Tile* _tile = new Tile(id, 11.f);
        std::vector<Tile*> neig_tile = tiles_graph.at(_tile);
        //if(passable && in_bounds) era una funzione per cercare i vicini, ma io l'ho implementata in modo diverso, e cioè
        //fornendo direttamente le grid che si possono passare e che sono dentro i confini di movimento
        for(auto itr : neig_tile)
            results.push_back(itr->location);
        //could be better to set vector size before, to be faster
        return results;
    }
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
    std::vector<Tile*> get_neighbor(Tile* tile);

    std::unordered_map<GridLocation, GridLocation> came_from;
    std::unordered_map<GridLocation, double> cost_so_far;

    SquareGrid grid = SquareGrid(117, 63);

public:
    friend class Tile;

    Node_map(sf::RenderWindow* window,  float gridX, float gridY);
    ~Node_map();

    void addTile();
    void create_Unordered_map();

    void saveTree(const std::string filename);
    void loadTree(const std::string filename);

    void aStar(GridLocation start, GridLocation goal);
    void update();
    void renderMap(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};
#endif //LABPROGRAMMAZIONE_NODE_MAP_H
