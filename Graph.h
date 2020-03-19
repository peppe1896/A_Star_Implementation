//
// Created by giuseppe on 18/03/20.
//

#ifndef LABPROGRAMMAZIONE_GRAPH_H
#define LABPROGRAMMAZIONE_GRAPH_H

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

class Tile
{
public:
    Tile(float x, float y, float width, float heigth);
    sf::Vector2f getPosition();
    sf::RectangleShape shape;
    sf::Texture tex;
    GridLocation location{};
    std::string id;

    GridLocation position_on_grill();
    void setColor(sf::Color color);

    bool operator==(Tile* a);
    bool operator!=(Tile* a);
};
#endif //LABPROGRAMMAZIONE_GRAPH_H
