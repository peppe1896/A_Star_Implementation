//
// Created by giuseppe on 14/03/20.
//

#include <sstream>
#include <fstream>
#include "Node_map.h"

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

    //Necessari 2GridSize, uno per x, e uno per Y
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
    //REMOVE LATER!!!
    mouse_text.setPosition(this->mousePosView.x, this->mousePosView.y - 10);
    //mouse_text.setCharacterSize(16);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouse_text.setString(ss.str());
    target->draw(mouse_text);

    renderMap(target);
}



bool Node_map::checkIntersect(Tile* rect) {
    for(auto itr : tiles)
            if(itr->getPosition() == rect->getPosition())
                return true;
    return false;
}

void Node_map::addTile()
{
    Tile* _tile = new Tile(static_cast<float>(mousePosGrid.x) * gridSizeX, static_cast<float>(mousePosGrid.y) * gridSizeY, gridSizeX, gridSizeY);

    if (checkIntersect(_tile))
        std::cout << "ERROR::TILE GIA' PRESENTE" << std::endl;
    else
    {
        tiles.push_back(_tile);
        std::cout << "AGGIUNTA TILE IN /" << _tile->getPosition().x << "\\|//" << _tile->getPosition().y << "\\"<< std::endl;
    }
    //std::cout << tiles.size() <<std::endl;
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
            out_file << itr->shape.getPosition().x << " " << itr->shape.getPosition().y  << " " << std::endl;
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

        std::cout << "NUMERO DI TILES: " << numtiles;

        for (int i = 1; i < numtiles; ++i)
        {
            float tempx;
            float tempy;
            in_file >> tempx >> tempy;
            tiles.push_back(new Tile(tempx,tempy, gridSizeX,gridSizeY));
        }
    }
}
//======================================================================================================================

Tile::Tile(float x, float y, float width, float heigth)
{
    shape.setSize(sf::Vector2f(width, heigth));
    shape.setPosition(x,y);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(0.f);
    shape.setOutlineColor(sf::Color::Blue);
}

//Praticamente una shortcut di getPosition() di shape
sf::Vector2f Tile::getPosition()
{
    return shape.getPosition();
}

void Tile::setColor(sf::Color color)
{
    shape.setFillColor(color);
}
