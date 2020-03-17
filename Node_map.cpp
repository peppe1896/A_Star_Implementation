//
// Created by giuseppe on 14/03/20.
//

#include <sstream>
#include "Node_map.h"

Node_map::Node_map(sf::RenderWindow* window)
{
    //mouse text & font
    if(!mouse_font.loadFromFile("/home/giuseppe/Progetti/Lab_Progr_2/Assets/Fonts/mouse_font.ttf"))
        std::cerr << "ERROR::NODE_MAP::COULD NOT LOAD FONT FOR MOUSE";
    mouse_text.setFont(mouse_font);
    mouse_text.setString("MOUSE POS");
    mouse_text.setFillColor(sf::Color::White);
    this->window = window;
    mousePosGrid = sf::Mouse::getPosition();
    mouse_text.setCharacterSize(16);

    //Necessari 2GridSize, uno per x, e uno per Y
    gridSizeX = 21.f;
    gridSizeY = 11.f;

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

    for(const auto itr : tiles)
        target->draw(itr->shape);

}

bool Node_map::checkIntersect(Tile* rect) {
    for(auto itr : tiles)
    {
            if(itr->getOrigin() == rect->getOrigin())
                return true;
    }
    return false;
}

void Node_map::addTile()
{
    auto* tile = new Tile(static_cast<float>(mousePosGrid.x), static_cast<float>(mousePosGrid.y), gridSizeX, gridSizeY);
    if (checkIntersect(tile))
    {
        std::cout << "ERROR::TILE già presente" << std::endl;
    }
    else
    {
        tiles.push_back(tile);
        std::cout << "AGGIUNTA TILE IN " << tile->getOrigin().x << "||" << tile->getOrigin().x << std::endl;
    }
    //std::cout << tiles.size() <<std::endl;
}

Node_map::~Node_map()
{
    for(auto itr : tiles)
        delete itr;
}


//======================================================================================================================

Tile::Tile(float x, float y, float width, float heigth)
{
    shape.setOrigin(sf::Vector2f(x,y));
    shape.setFillColor(sf::Color::Green);
    shape.setOutlineThickness(1.f);
    shape.setSize(sf::Vector2f(width, heigth));
}

sf::Vector2f Tile::getOrigin()
{
    return sf::Vector2f(shape.getOrigin());
}



