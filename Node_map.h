//
// Created by giuseppe on 14/03/20.
//

#ifndef LABPROGRAMMAZIONE_NODE_MAP_H
#define LABPROGRAMMAZIONE_NODE_MAP_H

#include "Graph.h"

namespace std {
/* implement hash function so we can put GridLocation(VECTOR2I) into an unordered_set */
    template <> struct hash<sf::Vector2i> {
        typedef sf::Vector2i argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const sf::Vector2i& id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 4));
        }
    };
}

static std::unordered_map<Tile*, std::vector<Tile*>> tiles_graph;
static std::unordered_set<sf::Vector2i> grid_in_map;
static std::unordered_set<sf::Vector2i> grid_out_map;
static std::unordered_set<sf::Vector2i> all_grid;

static std::vector<sf::Vector2i> neighbors(sf::Vector2i id)  {
    std::vector<sf::Vector2i> results;

    Tile *_tile = new Tile(id);
    std::vector<Tile *> neig_tile = tiles_graph.at(_tile);

    std::cout << "SQUAREGRID::CREATING VECTOR NEIGHBORS FROM STATIC FUNCTION" << std::endl;

    for (auto itr : neig_tile) {
        results.push_back(itr->location);
        std::cout << itr->location.x << "--" << itr->location.y << std::endl;
    }

    return results;
}

template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
            std::greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

static double cost(sf::Vector2i from_node, sf::Vector2i to_node) {
    if(grid_out_map.find(to_node) == grid_out_map.end())
        return 1;
    return 10000;
}

struct SquareGrid {
    int width, height;

    SquareGrid(int width_, int height_)
            : width(width_), height(height_) {}

    std::vector<sf::Vector2i> neighbors(sf::Vector2i id) const {
        std::vector<sf::Vector2i> results;

        Tile* _tile = new Tile(id);
        std::vector<Tile*> neig_tile = tiles_graph.at(_tile);

        std::cout << "SQUAREGRID::CREATING VECTOR NEIGHBORS FROM SQUAREGRID" << std::endl;

        for(auto itr : neig_tile) {
            results.push_back(itr->location);
            std::cout << itr->location.x << "--" << itr->location.y << std::endl;
        }
        //TODO COntrolla che funziona il ciclo
        return results;
    }
};

struct GridWithWeights: SquareGrid {

    GridWithWeights(int w, int h): SquareGrid(w, h)
    {
        std::cout << "GRIDWITHWEIGHT:: CREATED WITH W=" << w << " AND H=" << h<< std::endl;
    }

    double cost(sf::Vector2i from_node, sf::Vector2i to_node) const {
        if(grid_out_map.find(to_node) == grid_out_map.end())
            return 1;
        return 10000;
    }
};

class Node_map
{
private:
    //Mouse info, to put tile
    sf::RenderWindow* window;

    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;
    sf::Font mouse_font;
    sf::Text mouse_text;

    //Definition of grid and vector of all tile dynamically updated
    float gridSizeX;
    float gridSizeY;
    std::vector<Tile*> tiles;

    //Look in vector tiles and get the neighbors of any existing tile
    bool checkIntersect(Tile* rect);
    std::vector<Tile*> get_neighbor(Tile* tile);

    //Graph and maps that A* need
    std::unordered_map<sf::Vector2i, sf::Vector2i> came_from;
    std::unordered_map<sf::Vector2i, double> cost_so_far;
    GridWithWeights* grid;

public:
    friend class Tile;

    Node_map(sf::RenderWindow* window,  float gridX, float gridY);
    ~Node_map();

    //Map functions
    void addTile();
    void saveTree(const std::string& filename);
private:
    void create_static_data();
    void loadTree(const std::string filename);

    //A star functions
    double heuristic(sf::Vector2i a, sf::Vector2i b);
public:
    template<typename Location, typename Graph>
    void aStar_tile(Graph graph, Location start, Location goal);

    //Accessors
    Tile* gridToTile(sf::Vector2i grid);//prende fornisce un puntatore a una tile esistente, altrimenti nullptr

    //Draw & update functions
    void update();
    void renderMap(sf::RenderTarget* target);
    void renderMouse(sf::RenderTarget* target);

    void func();
};
#endif //LABPROGRAMMAZIONE_NODE_MAP_H
