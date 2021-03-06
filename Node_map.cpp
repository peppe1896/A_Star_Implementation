//
// Created by giuseppe on 14/03/20.
//

#include <sstream>
#include <fstream>
#include "Node_map.h"

Node_map::Node_map(sf::RenderWindow* window, float gridX, float gridY, std::string& location_mappa)
{
    //mouse text & font
    if (!mouse_font.loadFromFile("./Assets/Fonts/mouse_font.ttf"))
        std::cerr << "ERROR::NODE_MAP::COULD NOT LOAD FONT FOR MOUSE";
    mouse_text.setFont(mouse_font);
    mouse_text.setString("MOUSE POS");
    mouse_text.setFillColor(sf::Color::White);
    this->window = window;
    mousePosGrid = sf::Mouse::getPosition();
    mouse_text.setCharacterSize(16);

    gridSizeX = gridX;
    gridSizeY = gridY;

    locationMappa = location_mappa;

    if(!loadTree())
        std::cerr << "Mappa Non caricata!\nControlla i nomi dei file!\n";

    start = nullptr;
    goal = nullptr;

    start_goal_box.setSize(sf::Vector2f(150.f, 60.f));
    start_goal_box.setPosition(window->getSize().x - start_goal_box.getSize().x - 6.f, 6.f);
    start_goal_box.setFillColor(sf::Color(0,0,0,180));
    start_goal_box.setOutlineColor(sf::Color::Green);
    start_goal_box.setOutlineThickness(2.f);

    mouse_pos_box.setSize(sf::Vector2f(300.f, 55.f));
    mouse_pos_box.setPosition(window->getSize().x / 2.f - mouse_pos_box.getSize().x/2, 6.f);
    mouse_pos_box.setFillColor(sf::Color(0,0,0,180));
    mouse_pos_box.setOutlineColor(sf::Color::Green);
    mouse_pos_box.setOutlineThickness(2.f);
    mouse_text.setPosition(window->getSize().x / 2.f - mouse_pos_box.getSize().x / 2.f + 12.f, 20.f);

    start_.setFont(mouse_font);
    goal_.setFont(mouse_font);

    start_.setPosition(sf::Vector2f(start_goal_box.getPosition().x + start_goal_box.getSize().x/2.f - 60.f
            ,start_goal_box.getPosition().y + start_goal_box.getSize().y / 2.f - 20.f));

    goal_.setPosition(sf::Vector2f(start_goal_box.getPosition().x + start_goal_box.getSize().x/2.f - 60.f
            ,start_goal_box.getPosition().y + start_goal_box.getSize().y / 2.f));

    start_.setCharacterSize(13);
    goal_.setCharacterSize(13);
    start_.setFillColor(sf::Color::Red);
    goal_.setFillColor(sf::Color::Red);
    queue_player.clear();

}

void Node_map::update()
{
    mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    mousePosGrid =
            sf::Vector2i(
                    static_cast<int>(mousePosView.x) / static_cast<int>(this->gridSizeX),
                    static_cast<int>(mousePosView.y) / static_cast<int>(this->gridSizeY)
            );

}

void Node_map::renderMouse(sf::RenderTarget* target)
{
    //mouse_text.setPosition(mousePosView.x + 40, mousePosView.y - 10);
    std::stringstream ss;
    ss << "POSITION (Pixel): " <<mousePosView.x << " <-> " << mousePosView.y << "\n"
            << "POSITION (Grill): "<< mousePosGrid.x << " <-> " << mousePosGrid.y;
    mouse_text.setString(ss.str());
    mouse_text.setFillColor(sf::Color::Red);
    target->draw(mouse_pos_box);
    target->draw(mouse_text);

}

bool Node_map::checkIntersect(Tile* _tile)
{
    for(auto itr : tiles)
            if(*itr == _tile)
                return true;
    return false;

}

void Node_map::addTile()
{
    Tile* _tile = new Tile(static_cast<float>(mousePosGrid.x) * gridSizeX, static_cast<float>(mousePosGrid.y) * gridSizeY, gridSizeX, gridSizeY);

    if (!checkIntersect(_tile))
    {
        tiles.push_back(_tile);
        std::cout << "TILE ADDED!\n";
    } else
        std::cout << "Gia presente\n";
}

Node_map::~Node_map()
{
    for(auto itr : tiles)
        delete itr;

    tiles_graph.clear();
    grid_in_map.clear();
    grid_out_map.clear();
    all_grid.clear();

    delete window;
    observers.clear();
    delete start;
    delete goal;

}

void Node_map::renderMap(sf::RenderTarget *target) {
    std::stringstream ss1;
    std::stringstream ss2;

    if (start != nullptr) {
        target->draw(start_goal_box);
        ss1 << "START: " << start->x << "<->" << start->y;
        start_.setString(ss1.str());
        target->draw(start_);
        if (goal != nullptr) {
            ss2 << "GOAL: " << goal->x << "<->" << goal->y;
            goal_.setString(ss2.str());
            target->draw(goal_);
        }
    }
/*
    for (auto itr : tiles)
        if (itr->color != "blue")
            target->draw(itr->shape);
*/
}

void Node_map::saveTree()
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

bool Node_map::loadTree()
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
        create_static_data();
        //std::cout << "Size Graph (Num Elements): " << tiles_graph.size() << std::endl;
        return true;
    }
    return false;
}

void Node_map::create_static_data() {
    //CREATING I SETS PER LE TILE DENTRO E FUORI DALLA MAPPA

    for (auto itr : tiles) {
        std::pair<sf::Vector2i, std::vector<sf::Vector2i>> pair(itr->location, get_neighbor(itr->location));
        tiles_graph.emplace(pair);
        grid_in_map.insert(itr->location);
    }
    //std::cout << "NUMERO DI GRIDPOSITION DENTRO LA MAPPA " << grid_in_map.size() << std::endl;

    //Creo tutte le gridposition
    for (int i = 0; i < 117; i++) {
        for (int j = 0; j < 63; j++) {
            all_grid.insert(sf::Vector2i(i, j));
        }
    }
    //std::cout << "NUMERO DI GRIDPOSITION " << all_grid.size() << std::endl;

    //Creo le griglie fuori dalla mappa che mi interessa, così la uso nella GridWithWeights
    for(const auto it : all_grid)
        if(grid_in_map.find(it) == grid_in_map.end())
            grid_out_map.insert(it);
    //std::cout << "NUMERO DI GRIDPOSITION OUT MAP" << grid_out_map.size() << std::endl;

}

std::vector<sf::Vector2i> Node_map::get_neighbor(sf::Vector2i in)
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

double Node_map::heuristic(sf::Vector2i a, sf::Vector2i b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void Node_map::aStar_tile()
{
    PriorityQueue<sf::Vector2i, double> frontier;
    frontier.put(*start, 0);

    came_from.clear();
    cost_so_far.clear();

    came_from[*start] = *start;
    cost_so_far[*start] = 0;

    while (!frontier.empty())
    {
        sf::Vector2i current = frontier.get();

        if (current == *goal)
        {
            break;
        }

        for (sf::Vector2i next : tiles_graph[current])
        {
            double new_cost = cost_so_far[current] + 1;
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, *goal);
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }
}

void Node_map::call_astar()
{
    aStar_tile();

    for(auto& itr : reconstruct_path())
    {
        Tile *tile_to_change = get_tile(itr);
        tile_to_change->setColor(sf::Color::Red);
        tile_to_change->color = "red";
    }
}

void Node_map::setStart()
{
    if(grid_in_map.find(mousePosGrid) != grid_in_map.end())
            start = new sf::Vector2i(static_cast<float>(mousePosGrid.x),
                                    static_cast<float>(mousePosGrid.y));
    else
        start = nullptr;
}

void Node_map::setGoal()
{
    if (grid_in_map.find(mousePosGrid) != grid_in_map.end())
    {
        auto *temp1 = new sf::Vector2i(static_cast<float>(mousePosGrid.x),
                                    static_cast<float>(mousePosGrid.y));
        if (temp1 != start)
        {
            goal = temp1;

            std::cout << "GOAL " << goal->x << " |-| " << goal->y << std::endl;

            call_astar();
        }
    }
    else
        goal = nullptr;
}

Tile *Node_map::get_tile(sf::Vector2i in)
{
    Tile *temp2 = new Tile(in);

    for(const auto itr : tiles)
        if(*temp2 == itr)
            return itr;

    delete temp2;
    return nullptr;
}

void Node_map::reset_tile()
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

std::vector<sf::Vector2i> Node_map::reconstruct_path()
{
    queue_player.clear();
    std::vector<sf::Vector2i> path;
    sf::Vector2i current = *goal;

    while (current != *start)
    {
        path.push_back(current);
        current = came_from[current];
    }

    path.push_back(*start); // optional
    std::reverse(path.begin(), path.end());

    reset_tile();
    for(const auto& it : path)
        queue_player.push_back(it);

    notify();

    return path;
}

void Node_map::notify()
{
    for(auto itr : observers)
        itr->update_observer();
}

void Node_map::addObserver(Observer *o)
{
    observers.push_back(o);
}

void Node_map::remObserver(Observer *o)
{
    observers.remove(o);
}

void Node_map::setGoal_test(sf::Vector2i goal_position)
{
    start = new sf::Vector2i(69,6);
}

void Node_map::setStart_test(sf::Vector2i start_position)
{
    goal = new sf::Vector2i(60,18);
}

std::list<Observer*> Node_map::getObservers(){
    return observers;
}
