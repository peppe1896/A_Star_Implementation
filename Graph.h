//
// Created by giuseppe on 18/03/20.
//

#ifndef LABPROGRAMMAZIONE_GRAPH_H
#define LABPROGRAMMAZIONE_GRAPH_H

struct TileGraph
{
    std::unordered_map<std::string, std::vector<std::string> > edges;

    std::vector<std::string> neighbors(std::string id) {
        return edges[id];
    }
};

class Tile
{
public:
    Tile(float x, float y, float width, float heigth);
    sf::Vector2f getPosition();
    sf::RectangleShape shape;
    sf::Texture tex;

    std::string id;

    void setColor(sf::Color color);
};
#endif //LABPROGRAMMAZIONE_GRAPH_H
