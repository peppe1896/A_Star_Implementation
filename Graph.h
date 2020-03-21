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


class Tile;

struct GridLocation
{
    int x;
    int y;
};

struct TileGraph
{
    std::unordered_map<Tile*, std::vector<Tile*> > edges;

    std::vector<Tile*> neighbors(Tile* id) {
        return edges[id];
    }
};

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

template<typename Location, typename Graph>
void dijkstra_search
        (Graph graph,
         Location start,
         Location goal,
         std::unordered_map<Location, Location>& came_from,
         std::unordered_map<Location, double>& cost_so_far)
{
    PriorityQueue<Location, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        Location current = frontier.get();

        if (current == goal) {
            break;
        }

        for (Location next : graph.neighbors(current)) {
            double new_cost = cost_so_far[current] + graph.cost(current, next);
            if (cost_so_far.find(next) == cost_so_far.end()
                || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                came_from[next] = current;
                frontier.put(next, new_cost);
            }
        }
    }
}

class Tile
{
public:
    Tile(float x, float y, float width, float heigth, int peso = 1);
    Tile(GridLocation in, float gridSize, int peso = 1);
    Tile(int x, int y, float gridSize, int peso = 1);
    sf::Vector2f getPosition();
    sf::RectangleShape shape;
    sf::Texture tex;
    GridLocation location{};
    std::string id;

    int weight;
    void setColor(sf::Color colorchar);

    bool operator==(Tile* a);
    bool operator!=(Tile* a);
};
#endif //LABPROGRAMMAZIONE_GRAPH_H
