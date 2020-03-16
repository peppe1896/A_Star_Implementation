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
    mouse_text.setPosition(15.f,15.f);
    mouse_text.setFillColor(sf::Color::White);
    this->window = window;
    mousePosGrid = sf::Mouse::getPosition();
    //mouseCoordinates = target->mapPixelToCoords(mousePosGrid);

    gridSize = 100.f;

}

void Node_map::update()
{

    /*std::string strx = "x: " + mousePosInt.x;
    std::string stry = " || y: " + mousePosInt.y;


    mousePosGrid = sf::Mouse::getPosition(target);
    mouseCoordinates = target->mapPixelToCoords(mousePosGrid);
    //mouse_text.setString(strx + stry);
    mouse_text.setPosition(0.f,0.f);
    mouse_text.setFillColor(sf::Color::White);
    std::cout << mouseCoordinates.x << " -- " << mouseCoordinates.y << std::endl;
*/
    //
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*window);
    this->mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    this->mousePosGrid =
            sf::Vector2i(
                    static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
                    static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize)
            );
    std::cout << mousePosGrid.x << " -- " << mousePosGrid.y << " || Posizione in griglia" <<std::endl;
    std::cout << std::endl;
    std::cout << mousePosWindow.x << " -- " << mousePosWindow.y << " || Posizione in  window" << std::endl;
    std::cout << std::endl;
    std::cout << mousePosScreen.x << " -- " << mousePosScreen.y << " || Posizione nello schermo" <<std::endl;

}

void Node_map::render(sf::RenderTarget* target)
{
    //REMOVE LATER!!!
    //sf::Text mouseText;
    mouse_text.setPosition(this->mousePosView.x, this->mousePosView.y - 10);
    //mouseText.setFont(this->font);
    mouse_text.setCharacterSize(16);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouse_text.setString(ss.str());
    //target->draw(mouseText);
    target->draw(mouse_text);

}
