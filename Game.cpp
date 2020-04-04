#include <fstream>
#include "Game.h"

Game::Game(int config)
{
    std::string configure_;
    switch (config)
    {
        case 0:
            configure_ = "./Assets/Config/Config0.txt";
            break;
        case 1:
            configure_ = "./Assets/Config/Config1.txt";
            break;
        case 2:
            configure_ = "./Assets/Config/Config2.txt";
            break;
        default:
            configure_ = "";
            break;
    }
    std::ifstream input;
    input.open(configure_);

    if(input.is_open())
    {
        //std::cout << "GAME::LOADING CONFIGURATION from a Config file...\n";
        float off_x, off_y, scale_x, scale_y;
        std::string map;
        std::string background;

        input >> map >> background >> off_x >> off_y >> scale_x >> scale_y;

        offsetX = off_x;
        offsetY = off_y;

        if(!background_texture.loadFromFile(background))
            std::cerr << "ERROR::COULD NOT FIND THE MAP";

        indirizzoMappa = map;

        scaleX = scale_x;
        scaleY = scale_y;
        input.close();
    }
    else
    {
        std::cout << "~~GAME::LOADING DEFAULT CONFIG~~\n";
        offsetX = 1.f;
        offsetY = -1.f;

        if(!background_texture.loadFromFile("./Assets/Background/back0.png"))
            std::cerr << "ERROR::COULD NOT FIND THE MAP";

        indirizzoMappa = "./Assets/Config/Mappe/Mappa0.txt";

        scaleX = 0.6757;
        scaleY = 0.364967;
    }

    vMode.width = 1360;
    vMode.height = 800;
    this->window = new sf::RenderWindow(vMode, "A* search Alg.", sf::Style::Default);
    this->window->setFramerateLimit((60));

    //GridSize
    gridSizeX = 11.f;
    gridSizeY = 11.f;/*SCALARE PER IMPOSTARE LA DIMENSIONE DELLA TILE E DEL PLAYER*/

    //Graph & player
    mappa = new nodeMap(window, gridSizeX, gridSizeY, indirizzoMappa);
    hero = new player(window, 1.f, gridSizeX, gridSizeY, mappa);

    //set Background (map)
    background.setPosition(offsetX, offsetY);
    background.setSize(sf::Vector2f(static_cast<float>(background_texture.getSize().x),static_cast<float>(background_texture.getSize().y)));// vMode.height));
    background.setTexture(&background_texture);
    background.setScale(scaleX, scaleY); //Non adattabili! per una risoluzione di |1360x800|
}

Game::~Game()
{
}

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
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
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
    {
        mappa->renderMouse(target);
    }

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

nodeMap *Game::getMap() const {
    return mappa;
}

player *Game::getPlayer() const {
    return hero;
}

