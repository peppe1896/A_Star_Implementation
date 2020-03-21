//
// Created by giuseppe on 14/03/20.
//

#include <sstream>
#include <fstream>
#include "Node_map.h"
#include "Graph.h"


Node_map::Node_map(sf::RenderWindow* window, float gridX, float gridY)
{
    //mouse text & font
    if (!mouse_font.loadFromFile("/home/giuseppe/Progetti/Lab_Progr_2/Assets/Fonts/mouse_font.ttf"))
        std::cerr << "ERROR::NODE_MAP::COULD NOT LOAD FONT FOR MOUSE";
    mouse_text.setFont(mouse_font);
    mouse_text.setString("MOUSE POS");
    mouse_text.setFillColor(sf::Color::White);
    this->window = window;
    mousePosGrid = sf::Mouse::getPosition();
    mouse_text.setCharacterSize(16);

    gridSizeX = gridX;//19.f
    gridSizeY = gridY;//10.f
}

void Node_map::update()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*window);
    this->mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    this->mousePosGrid =
            sf::Vector2i(
                    static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSizeX),
                    static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSizeY)
            );

}

void Node_map::render(sf::RenderTarget* target)
{
    mouse_text.setPosition(this->mousePosView.x, this->mousePosView.y - 10);
    std::stringstream ss;
    ss << this->mousePosGrid.x << " " << this->mousePosGrid.y;
    mouse_text.setString(ss.str());
    target->draw(mouse_text);

    //Render mappa
    renderMap(target);
}

bool Node_map::checkIntersect(Tile* _tile) {
    for(auto itr : tiles)
            if(itr->getPosition() == _tile->getPosition())
                return true;
    return false;
}

void Node_map::addTile()
{
    Tile* _tile = new Tile(static_cast<float>(mousePosGrid.x) * gridSizeX, static_cast<float>(mousePosGrid.y) * gridSizeY, gridSizeX, gridSizeY);

    if (!checkIntersect(_tile))
    {
        tiles.push_back(_tile);
    }

}

Node_map::~Node_map()
{
    for(auto itr : tiles)
        delete itr;
}

void Node_map::renderMap(sf::RenderTarget *target)
{
    for(auto itr : tiles)
        target->draw(itr->shape);
}

void Node_map::saveTree(const std::string filename)
{
    std::ofstream out_file;

    out_file.open(filename);
    int numtiles = tiles.size();
    if(out_file.is_open())
    {
        out_file << numtiles << std::endl;

        for(auto itr : tiles)
            out_file << itr->shape.getPosition().x/gridSizeX << " " << itr->shape.getPosition().y/gridSizeY  << std::endl;
    }
}

void Node_map::loadTree(const std::string filename)
{
    std::ifstream in_file;

    in_file.open(filename);

    if(in_file.is_open())
    {
        int numtiles;

        in_file >> numtiles;

        for (int i = 1; i < numtiles; ++i)
        {
            float tempx;
            float tempy;
            in_file >> tempx >> tempy;
            tiles.push_back(new Tile(tempx*gridSizeX,tempy*gridSizeY, gridSizeX,gridSizeY));
        }
    }

    //Creo l'unordered map da dare al grafo
    create_Unordered_map();

    std::cout << "Size Graph (Bytes): " << tiles_graph.size();
}

void Node_map::create_Unordered_map()
{
    for(auto itr : tiles)
    {
        std::pair<Tile*,std::vector<Tile*>> pair(itr,get_neighbor(itr));
        tiles_graph.emplace(pair);
    }
}

std::vector<Tile *> Node_map::get_neighbor(Tile* _tile)
{
    Tile* N = new Tile(_tile->location.x, _tile->location.y - 1, gridSizeX);
    Tile* S = new Tile(_tile->location.x, _tile->location.y + 1, gridSizeX);
    Tile* E = new Tile(_tile->location.x + 1, _tile->location.y, gridSizeX);
    Tile* W = new Tile(_tile->location.x - 1, _tile->location.y, gridSizeX);

    std::vector<Tile*> temp_vector;

    for(auto itr : tiles)
        if(*itr == _tile)
            if(checkIntersect(N))
                temp_vector.push_back(N);

            if(checkIntersect(S))
                temp_vector.push_back(S);

            if(checkIntersect(E))
                temp_vector.push_back(E);

            if(checkIntersect(W))
                temp_vector.push_back(W);

    return temp_vector;
}

//====================================================================================================================//

Tile::Tile(float x, float y, float width, float heigth)
{
    shape.setSize(sf::Vector2f(width, heigth));
    shape.setPosition(x,y);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(0.f);
    shape.setOutlineColor(sf::Color::Blue);

    id = std::to_string(static_cast<int>(x/11.f)) + std::to_string(static_cast<int>(y/11.f));

    location.x = static_cast<int>(x/11.f);
    location.y = static_cast<int>(y/11.f);

    //std::cout << "x = " << location.x << " y = " << location.y << std::endl;
    //std::cout << "ID = " << id << std::endl;
}

sf::Vector2f Tile::getPosition()
{
    return shape.getPosition();
}

void Tile::setColor(sf::Color color)
{
    shape.setFillColor(color);
}

bool Tile::operator==(Tile *a)
{
    return id == a->id;
}

bool Tile::operator!=(Tile *a)
{
    return id != a->id;
}

Tile::Tile(GridLocation in, float gridSize)
{
    shape.setSize(sf::Vector2f(gridSize, gridSize));
    shape.setPosition(in.x * static_cast<int>(gridSize),in.y * static_cast<int>(gridSize));
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(0.f);
    shape.setOutlineColor(sf::Color::Blue);

    id = std::to_string(in.x) + std::to_string(in.y);

    location.x = in.x;
    location.y = in.y;

    //std::cout << "x = " << location.x << " y = " << location.y << std::endl;
    //std::cout << "ID = " << id << std::endl;
}

Tile::Tile(int x, int y, float gridSize)
{
    shape.setSize(sf::Vector2f(gridSize, gridSize));
    shape.setPosition(x * static_cast<int>(gridSize),y * static_cast<int>(gridSize));
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(0.f);
    shape.setOutlineColor(sf::Color::Blue);

    id = std::to_string(x) + std::to_string(y);

    location.x = x;
    location.y = y;

    //std::cout << "x = " << location.x << " y = " << location.y << std::endl;
    //std::cout << "ID = " << id << std::endl;
}
