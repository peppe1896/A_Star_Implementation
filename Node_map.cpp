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

    gridSizeX = gridX;
    gridSizeY = gridY;

    loadTree("/home/giuseppe/Progetti/Lab_Progr_2/Assets/Config/Mappa.txt");

    //creo il grafo da passare a a_star_search
    //grid.width = 117;
    //grid.height = 63;

    //grid = new SquareGrid{117,63};

    //func();
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
    mouse_text.setFillColor(sf::Color::Red);
    target->draw(mouse_text);

    //Render mappa
    renderMap(target);
}

bool Node_map::checkIntersect(Tile* _tile)
{
    for(auto itr : tiles)
            if(itr->getPosition() == _tile->getPosition())
                return true;
    return false;

}

void Node_map::addTile()
{
    Tile* _tile = new Tile(static_cast<float>(mousePosGrid.x) * gridSizeX, static_cast<float>(mousePosGrid.y) * gridSizeY, gridSizeX, gridSizeY);

    if (!checkIntersect(_tile))
        tiles.push_back(_tile);
}

Node_map::~Node_map()
{
    for(auto itr : tiles)
        delete itr;

    //delete grid;
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
            out_file << itr->location.x << " " << itr->location.y  << " " << itr->weight << std::endl;
            //out_file << itr->shape.getPosition().x/gridSizeX << " " << itr->shape.getPosition().y/gridSizeY  << " " << itr->weight << std::endl;
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
            int weig = 0;
            in_file >> tempx >> tempy >> weig;
            tiles.push_back(new Tile(tempx*gridSizeX,tempy*gridSizeY, gridSizeX,gridSizeY, weig));
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
        //grid_in_map.insert(itr->location);
    }

    std::cout << "UNORDERED MAP CREATED" << std::endl;

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
        {
            if (checkIntersect(N))
                temp_vector.push_back(N);

            if (checkIntersect(S))
                temp_vector.push_back(S);

            if (checkIntersect(E))
                temp_vector.push_back(E);

            if (checkIntersect(W))
                temp_vector.push_back(W);
        }

    return temp_vector;
}
/*
template<typename Location, typename Graph>
void Node_map::aStar(Graph graph,
                     Location start,
                     Location goal)
{
        PriorityQueue<Location, double> frontier;
        frontier.put(start, 0);

        this->came_from[start] = start;
        this->cost_so_far[start] = 0;

        while (!frontier.empty()) {
            Location current = frontier.get();

            if (current == goal){
                break;
            }

            for (Location next : graph.neighbors(current)) {
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
//======================================================================================================================

void Node_map::func() {

    Tile* a = new Tile(GridLocation{13,17});
    Tile* b = new Tile(GridLocation{17,29});
    //GridLocation goal{17,29};
    aStar_tile(a, b);


    //dijkstra_search(grid, start, goal, came_from, cost_so_far);
}

double Node_map::heuristic(GridLocation a, GridLocation b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void Node_map::aStar_tile(Tile *start, Tile *goal)
{
    PriorityQueue<Tile*, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while(!frontier.empty()) {
        Tile *current = frontier.get();

        if(current == goal)
            break;

        for(Tile* next : get_neighbor(current))
        {
            double new_cost = cost_so_far[current] +
                              1; //1 perché costa sempre 1 attraversare una tile. Di fatto questo è più dijstrka

            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
                cost_so_far[next] = new_cost;

            double priority = new_cost + 1;
            frontier.put(next, priority);

            came_from[next] = current;
        }
    }

}

template<typename Location, typename Graph>
void Node_map::aStar(Graph graph, Location start, Location goal) {

}

/*
bool checkTile(Tile * check) {
    for(const auto itr : tiles_graph) {
        if (itr.first->id == check->id)
            return true;
    }
    return false;
}*/
