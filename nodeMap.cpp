//
// Created by giuseppe on 14/03/20.
//

#include <sstream>
#include <fstream>
#include "nodeMap.h"

nodeMap::nodeMap(sf::RenderWindow* window, float gridX, float gridY, std::string& location_mappa)
{
    //mouse text & font
    if (!mouseFont.loadFromFile("./Assets/Fonts/mouse_font.ttf"))
        std::cerr << "ERROR::NODE_MAP::COULD NOT LOAD FONT FOR MOUSE";
    mouseText.setFont(mouseFont);
    mouseText.setString("MOUSE POS");
    mouseText.setFillColor(sf::Color::White);
    this->window = window;
    mousePosGrid = sf::Mouse::getPosition();
    mouseText.setCharacterSize(16);

    gridSizeX = gridX;
    gridSizeY = gridY;

    locationMappa = location_mappa;

    if(!loadTree())
        std::cerr << "Mappa Non caricata!\nControlla i nomi dei file!\n";

    start = nullptr;
    goal = nullptr;

    boxStartGoal.setSize(sf::Vector2f(150.f, 60.f));
    boxStartGoal.setPosition(window->getSize().x - boxStartGoal.getSize().x - 6.f, 6.f);
    boxStartGoal.setFillColor(sf::Color(0, 0, 0, 180));
    boxStartGoal.setOutlineColor(sf::Color::Green);
    boxStartGoal.setOutlineThickness(2.f);

    boxMousePos.setSize(sf::Vector2f(300.f, 55.f));
    boxMousePos.setPosition(window->getSize().x / 2.f - boxMousePos.getSize().x / 2, 6.f);
    boxMousePos.setFillColor(sf::Color(0, 0, 0, 180));
    boxMousePos.setOutlineColor(sf::Color::Green);
    boxMousePos.setOutlineThickness(2.f);
    mouseText.setPosition(window->getSize().x / 2.f - boxMousePos.getSize().x / 2.f + 12.f, 20.f);

    startText.setFont(mouseFont);
    goalText.setFont(mouseFont);

    startText.setPosition(sf::Vector2f(boxStartGoal.getPosition().x + boxStartGoal.getSize().x / 2.f - 60.f
            , boxStartGoal.getPosition().y + boxStartGoal.getSize().y / 2.f - 20.f));

    goalText.setPosition(sf::Vector2f(boxStartGoal.getPosition().x + boxStartGoal.getSize().x / 2.f - 60.f
            , boxStartGoal.getPosition().y + boxStartGoal.getSize().y / 2.f));

    startText.setCharacterSize(13);
    goalText.setCharacterSize(13);
    startText.setFillColor(sf::Color::Red);
    goalText.setFillColor(sf::Color::Red);
    queue_player.clear();

}

void nodeMap::update()
{
    mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    mousePosGrid =
            sf::Vector2i(
                    static_cast<int>(mousePosView.x) / static_cast<int>(this->gridSizeX),
                    static_cast<int>(mousePosView.y) / static_cast<int>(this->gridSizeY)
            );

}

void nodeMap::renderMouse(sf::RenderTarget* target)
{
    //mouseText.setPosition(mousePosView.x + 40, mousePosView.y - 10);
    std::stringstream ss;
    ss << "POSITION (Pixel): " <<mousePosView.x << " <-> " << mousePosView.y << "\n"
            << "POSITION (Grill): "<< mousePosGrid.x << " <-> " << mousePosGrid.y;
    mouseText.setString(ss.str());
    mouseText.setFillColor(sf::Color::Red);
    target->draw(boxMousePos);
    target->draw(mouseText);

}

bool nodeMap::checkIntersect(Tile* _tile)
{
    for(auto itr : tiles)
            if(*itr == _tile)
                return true;
    return false;

}

void nodeMap::addTile()
{
    Tile* _tile = new Tile(static_cast<float>(mousePosGrid.x) * gridSizeX, static_cast<float>(mousePosGrid.y) * gridSizeY, gridSizeX, gridSizeY);

    if (!checkIntersect(_tile))
    {
        tiles.push_back(_tile);
        std::cout << "TILE ADDED!\n";
    } else
        std::cout << "Gia presente\n";
}

nodeMap::~nodeMap()
{
    for(auto itr : tiles)
        delete itr;

    tilesGraph.clear();
    gridInMap.clear();
    gridOutMap.clear();
    allGrid.clear();

    delete window;
    observers.clear();
    delete start;
    delete goal;

}

void nodeMap::renderMap(sf::RenderTarget *target) {
    std::stringstream ss1;
    std::stringstream ss2;

    if (start != nullptr) {
        target->draw(boxStartGoal);
        ss1 << "START: " << start->x << "<->" << start->y;
        startText.setString(ss1.str());
        target->draw(startText);
        if (goal != nullptr) {
            ss2 << "GOAL: " << goal->x << "<->" << goal->y;
            goalText.setString(ss2.str());
            target->draw(goalText);
        }
    }
/*ACTIVATE TO DRAW TILES OF THE GRAPH
    for (auto itr : tiles)
        if (itr->color != "blue")
            target->draw(itr->shape);
*/
}

void nodeMap::saveTree()
{
    std::ofstream out_file;

    out_file.open(locationMappa);
    int numtiles = tiles.size();
    if(out_file.is_open())
    {
        out_file << numtiles << std::endl;

        for(auto itr : tiles)
            out_file << itr->shape.getPosition().x/gridSizeX << " " << itr->shape.getPosition().y/gridSizeY  << " " << itr->weight << std::endl;
    }
}

bool nodeMap::loadTree()
{
    std::ifstream in_file;

    in_file.open(locationMappa);

    if(in_file.is_open())
    {
        int numtiles;

        in_file >> numtiles;

        for (int i = 1; i < numtiles; ++i)
        {
            float tempx;
            float tempy;
            int weig;
            in_file >> tempx >> tempy >> weig;
            tiles.push_back(new Tile(tempx*gridSizeX,tempy*gridSizeY, gridSizeX,gridSizeY, weig));
        }
        in_file.close();
        createStaticData();
        //std::cout << "Size Graph (Num Elements): " << tilesGraph.size() << std::endl;
        return true;
    }
    return false;
}

void nodeMap::createStaticData() {
    //CREATING I SETS PER LE TILE DENTRO E FUORI DALLA MAPPA

    for (auto itr : tiles) {
        std::pair<sf::Vector2i, std::vector<sf::Vector2i>> pair(itr->location, getNeighbor(itr->location));
        tilesGraph.emplace(pair);
        gridInMap.insert(itr->location);
    }
    //std::cout << "NUMERO DI GRIDPOSITION DENTRO LA MAPPA " << grid_in_map.size() << std::endl;

    //Creo tutte le gridposition
    for (int i = 0; i < 117; i++) {
        for (int j = 0; j < 63; j++) {
            allGrid.insert(sf::Vector2i(i, j));
        }
    }
    //std::cout << "NUMERO DI GRIDPOSITION " << allGrid.size() << std::endl;

    //Creo le griglie fuori dalla mappa che mi interessa, così la uso nella GridWithWeights
    for(const auto it : allGrid)
        if(gridInMap.find(it) == gridInMap.end())
            gridOutMap.insert(it);
    //std::cout << "NUMERO DI GRIDPOSITION OUT MAP" << gridOutMap.size() << std::endl;

}

std::vector<sf::Vector2i> nodeMap::getNeighbor(sf::Vector2i in)
{
    Tile* _tile = new Tile(in);
    Tile* N = new Tile(_tile->location.x, _tile->location.y - 1, gridSizeX);
    Tile* S = new Tile(_tile->location.x, _tile->location.y + 1, gridSizeX);
    Tile* E = new Tile(_tile->location.x + 1, _tile->location.y, gridSizeX);
    Tile* W = new Tile(_tile->location.x - 1, _tile->location.y, gridSizeX);

    std::vector<sf::Vector2i> temp_vector;

    for(auto itr : tiles)
        if(*itr == _tile)
        {
            if (checkIntersect(N))
                temp_vector.push_back(N->location);

            if (checkIntersect(S))
                temp_vector.push_back(S->location);

            if (checkIntersect(E))
                temp_vector.push_back(E->location);

            if (checkIntersect(W))
                temp_vector.push_back(W->location);
        }

    return temp_vector;
}

double nodeMap::heuristic(sf::Vector2i a, sf::Vector2i b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void nodeMap::aStarTile()
{
    PriorityQueue<sf::Vector2i, double> frontier;
    frontier.put(*start, 0);

    cameFrom.clear();
    costSoFar.clear();

    cameFrom[*start] = *start;
    costSoFar[*start] = 0;

    while (!frontier.empty())
    {
        sf::Vector2i current = frontier.get();

        if (current == *goal)
        {
            break;
        }

        for (sf::Vector2i next : tilesGraph[current])
        {
            double new_cost = costSoFar[current] + 1;
            if (costSoFar.find(next) == costSoFar.end() || new_cost < costSoFar[next])
            {
                costSoFar[next] = new_cost;
                double priority = new_cost + heuristic(next, *goal);
                frontier.put(next, priority);
                cameFrom[next] = current;
            }
        }
    }
}

void nodeMap::callAstar()
{
    aStarTile();

    for(auto& itr : reconstructPath())
    {
        Tile *tile_to_change = getTile(itr);
        tile_to_change->setColor(sf::Color::Red);
        tile_to_change->color = "red";
    }
}

void nodeMap::setStart()
{
    if(gridInMap.find(mousePosGrid) != gridInMap.end())
            start = new sf::Vector2i(static_cast<float>(mousePosGrid.x),
                                    static_cast<float>(mousePosGrid.y));
    else
        start = nullptr;
}

void nodeMap::setGoal()
{
    if (gridInMap.find(mousePosGrid) != gridInMap.end())
    {
        auto *temp1 = new sf::Vector2i(static_cast<float>(mousePosGrid.x),
                                    static_cast<float>(mousePosGrid.y));
        if (temp1 != start)
        {
            goal = temp1;

            std::cout << "GOAL " << goal->x << " |-| " << goal->y << std::endl;

            callAstar();
        }
    }
    else
        goal = nullptr;
}

Tile *nodeMap::getTile(sf::Vector2i in)
{
    Tile *temp2 = new Tile(in);

    for(const auto itr : tiles)
        if(*temp2 == itr)
            return itr;

    delete temp2;
    return nullptr;
}

void nodeMap::resetTile()
{
    for(auto itr : tiles)
    {
        if(itr->color == "red")
        {
            itr->setColor(sf::Color::Blue);
            itr->color = "blue";
        }
    }
}

std::vector<sf::Vector2i> nodeMap::reconstructPath()
{
    queue_player.clear();
    std::vector<sf::Vector2i> path;
    sf::Vector2i current = *goal;

    while (current != *start)
    {
        path.push_back(current);
        current = cameFrom[current];
    }

    path.push_back(*start); // optional
    std::reverse(path.begin(), path.end());

    resetTile();
    for(const auto& it : path)
        queue_player.push_back(it);

    notify();

    return path;
}

void nodeMap::notify()
{
    for(auto itr : observers)
        itr->update_observer();
}

void nodeMap::addObserver(Observer *o)
{
    observers.push_back(o);
}

void nodeMap::remObserver(Observer *o)
{
    observers.remove(o);
}

void nodeMap::setGoal_test(sf::Vector2i goal_position)
{
    start = new sf::Vector2i(69,6);
}

void nodeMap::setStart_test(sf::Vector2i start_position)
{
    goal = new sf::Vector2i(60,18);
}

std::list<Observer*> nodeMap::getObservers(){
    return observers;
}
