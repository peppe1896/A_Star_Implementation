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
    int x, y;
};

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
    template <> struct hash<sf::Vector2i> {
        typedef sf::Vector2i argument_type;
        typedef std::size_t result_type;
        std::size_t operator()(const sf::Vector2i& id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 4));
        }
    };
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

//STAVO PROVANDO A TOGLIERE IL TIPO LOCATION, IN MODO DA NON DOVER USARE I
/*
template<typename Graph>
void a_star_search
        (Graph graph,
         sf::Vector2i start,
         sf::Vector2i goal,
         std::unordered_map<sf::Vector2i, sf::Vector2i>& came_from,
         std::unordered_map<sf::Vector2i, double>& cost_so_far)
{
    PriorityQueue<sf::Vector2i, double> frontier;
    frontier.put(start, 0);

    //std::unordered_map<Location, Location> came_from;
    //std::unordered_map<Location, double> cost_so_far;

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        sf::Vector2i current = frontier.get();

        if (current.x == goal.x && current.y == goal.y) {
            break;
        }

        for (sf::Vector2i next : graph.neighbors(current)) {
            double new_cost = cost_so_far[current] + graph.cost(current, next);
            if (cost_so_far.find(next) == cost_so_far.end()
                || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }
}
*/
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
