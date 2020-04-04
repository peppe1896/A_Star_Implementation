//
// Created by giuseppe on 14/03/20.
//

#ifndef LABPROGRAMMAZIONE_NODEMAP_H
#define LABPROGRAMMAZIONE_NODEMAP_H

#include "Graph.h"
#include <iostream>
#include "Subject.h"
#include <list>

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

class nodeMap : public Subject
{
private:
    std::unordered_map<sf::Vector2i, std::vector<sf::Vector2i>> tilesGraph;

    std::unordered_set<sf::Vector2i> gridInMap;
    std::unordered_set<sf::Vector2i> gridOutMap;
    std::unordered_set<sf::Vector2i> allGrid;

    //Mouse info, to put tile
    sf::RenderWindow* window;

    sf::RectangleShape boxStartGoal;
    sf::RectangleShape boxMousePos;
    sf::Font mouseFont;
    sf::Text mouseText;
    sf::Text startText, goalText;

    std::string locationMappa;

    //Definition of grid and vector of all tile dynamically updated
    float gridSizeX;
    float gridSizeY;
    std::vector<Tile*> tiles;

    //Look in vector tiles and get the neighbors of any existing tile
    bool checkIntersect(Tile* rect);
    std::vector<sf::Vector2i> getNeighbor(sf::Vector2i in);

    //Graph and maps that A* need
    std::unordered_map<sf::Vector2i, sf::Vector2i> cameFrom;
    std::unordered_map<sf::Vector2i, double> costSoFar;

    sf::Vector2i* start;
    sf::Vector2i* goal;

    Tile* getTile(sf::Vector2i in);
    std::list<Observer*> observers;

public:
    nodeMap(sf::RenderWindow* window, float gridX, float gridY, std::string& location_mappa);
    ~nodeMap();

    //Map functions
    void addTile();
    void saveTree();

    std::vector<sf::Vector2i> queue_player;
private:
    void createStaticData();
    bool loadTree();

    //A star functions
    double heuristic(sf::Vector2i a, sf::Vector2i b);
public:
    void aStarTile();

    //Draw & update functions
    void update();
    void renderMap(sf::RenderTarget* target);
    void renderMouse(sf::RenderTarget* target);

    void setStart();
    void setGoal();
private:
    void callAstar();
    void resetTile();
public:
    std::vector<sf::Vector2i> reconstructPath();

    //Observer methods
    void notify() override;
    void addObserver(Observer* o) override;
    void remObserver(Observer* o) override;

    //TESTING METHODS
    void setStart_test(sf::Vector2i start_position = sf::Vector2i(61,7));
    void setGoal_test(sf::Vector2i goal_position = sf::Vector2i(90,15));
    std::list<Observer*> getObservers();
};
#endif //LABPROGRAMMAZIONE_NODEMAP_H
