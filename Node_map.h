//
// Created by giuseppe on 14/03/20.
//

#ifndef LABPROGRAMMAZIONE_NODE_MAP_H
#define LABPROGRAMMAZIONE_NODE_MAP_H

#include "Graph.h"
#include <iostream>
using namespace std;

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

static std::unordered_map<sf::Vector2i, std::vector<sf::Vector2i>> tiles_graph;

static std::unordered_set<sf::Vector2i> grid_in_map;
static std::unordered_set<sf::Vector2i> grid_out_map;
static std::unordered_set<sf::Vector2i> all_grid;

static std::vector<sf::Vector2i> queue_player;

template<typename T>
class PQComparisor
{
public:
    PQComparisor() = default;
    bool operator()(const T & a, const T &b)
    {
        //std::cout << "\nCompare\n";
        if(a.first > b.first)
            return true;
        else
            return std::tie(a.second.x,a.second.y) > std::tie(b.second.x, b.second.y);
    }

};

template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;

    std::priority_queue<PQElement, std::vector<PQElement>,
            PQComparisor<PQElement>> elements;

    inline bool empty() const
    {
        return elements.empty();
    }

    inline void put(T item, priority_t priority)
    {
        elements.emplace(priority, item);
    }

    T get()
    {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

static sf::Vector2f mousePosView;
static sf::Vector2i mousePosGrid;

class Node_map
{
private:
    //Mouse info, to put tile
    sf::RenderWindow* window;

    sf::RectangleShape start_goal_box;
    sf::Font mouse_font;
    sf::Text mouse_text;
    sf::Text start_, goal_;

    std::string locationMappa;

    //Definition of grid and vector of all tile dynamically updated
    float gridSizeX;
    float gridSizeY;
    std::vector<Tile*> tiles;

    //Look in vector tiles and get the neighbors of any existing tile
    bool checkIntersect(Tile* rect);
    std::vector<sf::Vector2i> get_neighbor(sf::Vector2i in);

    //Graph and maps that A* need
    std::unordered_map<sf::Vector2i, sf::Vector2i> came_from;
    std::unordered_map<sf::Vector2i, double> cost_so_far;

    sf::Vector2i* start;
    sf::Vector2i* goal;

    Tile* get_tile(sf::Vector2i in);

public:
    friend class Tile;

    Node_map(sf::RenderWindow* window,  float gridX, float gridY, std::string& location_mappa);
    ~Node_map();

    //Map functions
    void addTile();
    void saveTree();
private:
    void create_static_data();
    bool loadTree();

    //A star functions
    double heuristic(sf::Vector2i a, sf::Vector2i b);
public:
    void aStar_tile(sf::Vector2i start, sf::Vector2i goal);

    //Draw & update functions
    void update();
    void renderMap(sf::RenderTarget* target);
    void renderMouse(sf::RenderTarget* target);

    void setStart();
    void setGoal();
private:
    void call_astar();
    void reset_tile();
public:
    std::vector<sf::Vector2i> reconstruct_path();
    bool take_that;
};
#endif //LABPROGRAMMAZIONE_NODE_MAP_H
