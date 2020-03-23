//
// Created by giuseppe on 14/03/20.
//

#ifndef LABPROGRAMMAZIONE_NODE_MAP_H
#define LABPROGRAMMAZIONE_NODE_MAP_H

//#include "A_Star.h"
#include "Graph.h"

static std::unordered_map<Tile*, std::vector<Tile*>> tiles_graph;
static std::unordered_set<sf::Vector2i> grid_in_map;
static std::unordered_set<sf::Vector2i> grid_out_map;
static std::unordered_set<sf::Vector2i> all_grid;

struct SquareGrid {
    int width, height;

    SquareGrid(int width_, int height_)
            : width(width_), height(height_) {}

    std::vector<sf::Vector2i> neighbors(sf::Vector2i id) const {
        std::vector<sf::Vector2i> results;

        Tile* _tile = new Tile(id);
        std::vector<Tile*> neig_tile = tiles_graph.at(_tile);

        std::cout << "SQUAREGRID::CREATING VECTOR NEIGHBORS" << std::endl;

        for(auto itr : neig_tile) {
            results.push_back(itr->location);
            std::cout << itr->location.x << "--" << itr->location.y << std::endl;
        }
        //TODO COntrolla che funziona il ciclo
        return results;
    }
};
  /*  std::vector<sf::Vector2i> neighbors(sf::Vector2i id) const {
        std::vector<sf::Vector2i> results;
        //create a new tile to pass to the unordered_map
        Tile* _tile = new Tile(id);
        std::vector<Tile*> neig_tile = tiles_graph.at(_tile);
        //if(passable && in_bounds) era una funzione per cercare i vicini, ma io l'ho implementata in modo diverso, e cioè
        //fornendo direttamente le grid che si possono passare e che sono dentro i confini di movimento
        for(auto itr : neig_tile)
            results.push_back(itr->location);
        //could be better to set vector size before, to be faster
        return results;
    }
}
*/

struct GridWithWeights: SquareGrid {

    GridWithWeights(int w, int h): SquareGrid(w, h){}

    double cost(sf::Vector2i from_node, sf::Vector2i to_node) const {
        if(grid_out_map.find(to_node) == grid_out_map.end())
            return 1;
        return 10000;
    }
};

class Node_map
{
private:
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

    std::unordered_map<sf::Vector2i, sf::Vector2i> came_from;
    std::unordered_map<sf::Vector2i, double> cost_so_far;

    GridWithWeights* grid;

public:
    friend class Tile;

    Node_map(sf::RenderWindow* window,  float gridX, float gridY);
    ~Node_map();

    void addTile();
    void create_static_data();

    void saveTree(const std::string filename);
    void loadTree(const std::string filename);

    double heuristic(sf::Vector2i a,sf::Vector2i b);

    void aStar_tile(sf::Vector2i start, sf::Vector2i goal);

    void update();
    void renderMap(sf::RenderTarget* target);
    void renderMouse(sf::RenderTarget* target);
};
#endif //LABPROGRAMMAZIONE_NODE_MAP_H
