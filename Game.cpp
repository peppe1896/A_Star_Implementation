#include <fstream>
#include "Game.h"

Game::Game(int config)
{
    std::string configure_;
    switch (config)
    {
        case 0:
            configure_ = "/home/giuseppe/Progetti/Lab_Progr_2/Assets/Config/Config0.txt";
            break;
        case 1:
            configure_ = "/home/giuseppe/Progetti/Lab_Progr_2/Assets/Config/Config1.txt";
            break;
        case 2:
            configure_ = "__";
            break;
        default:
            configure_ = "";
            break;
    }
    std::ifstream input;
    input.open(configure_);
    if(input.is_open())
    {
        std::cout << "LOADING CONFIGURATION from a Config file...\n";
        float off_x, off_y, scale_x, scale_y;
        std::string map;
        std::string background;

        input >> map >> background >> off_x >> off_y >> scale_x >> scale_y;

        offsetx = off_x;
        offsety = off_y;

        if(!background_texture.loadFromFile(background))
            std::cerr << "ERROR::COULD NOT FIND THE MAP";

        indirizzoMappa = map;

        scalex = scale_x;
        scaley = scale_y;
        input.close();
    }
    else
    {
        std::cout << "LOADING DEFAULT CONFIG\n";
        offsetx = 1.f;
        offsety = -1.f;

        if(!background_texture.loadFromFile("/home/giuseppe/Progetti/Lab_Progr_2/Assets/Background/back0.png"))
            std::cerr << "ERROR::COULD NOT FIND THE MAP";

        indirizzoMappa = "/home/giuseppe/Progetti/Lab_Progr_2/Assets/Config/Mappe/Mappa0.txt";

        scalex = 0.6757;
        scaley = 0.364967;
    }

    vMode.width = 1360;
    vMode.height = 800;
    this->window = new sf::RenderWindow(vMode, "A* search Alg.", sf::Style::Default);
    this->window->setFramerateLimit((60));

    //GridSize
    gridSize_x = 11.f;
    gridSize_y = 11.f;/*SCALARE PER IMPOSTARE LA DIMENSIONE DELLA TILE E DEL PLAYER*/

    hero = new player(window, 1.f, gridSize_x, gridSize_y);

    //set Background (map)
    background.setPosition(offsetx,offsety);
    background.setSize(sf::Vector2f(static_cast<float>(background_texture.getSize().x),static_cast<float>(background_texture.getSize().y)));// vMode.height));
    background.setTexture(&background_texture);
    background.setScale(scalex,scaley); //Non adattabili! per una risoluzione di |1360x800|
    //Graph
    mappa = new Node_map(window, gridSize_x, gridSize_y, indirizzoMappa);
}

Game::~Game() {}

void Game::update() {
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();
    }

    hero->handleInput();

    mappa->update();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        mappa->addTile();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) )
        {
            mappa->setStart();
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mappa->setGoal();
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F10))
    {
        mappa->saveTree();
        std::cout << "MAPPA SALVATA SU \n" << indirizzoMappa << std::endl;
    }
}

void Game::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->clear();

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        target->draw(background);

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        mappa->renderMap(target);

    hero->drawPlayer(target);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        mappa->renderMouse(target);

    window->display();
}

void Game::run()
{
    while (window->isOpen())
    {
        update();
        render(this->window);
    }
}