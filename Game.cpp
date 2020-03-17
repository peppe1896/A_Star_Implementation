#include "Game.h"

Game::Game()
{
    offsetx = 1.f;
    offsety = -1.f;
    vMode.width = 1360;
    vMode.height = 800;
    this->window = new sf::RenderWindow(vMode, "Implementation A* search Alg.", sf::Style::Default);
    this->window->setFramerateLimit((60));

    //GridSize
    gridSize_x = 11.f;
    gridSize_y = 11.f;/*SCALARE PER IMPOSTARE LA DIMENSIONE DELLA TILE E DEL PLAYER*/

    hero = new player(window, .5f, gridSize_x, gridSize_y);

    //set Background (map)
    if(!background_texture.loadFromFile("/home/giuseppe/Progetti/Lab_Progr_2/Assets/Background/canvas.png"))
        std::cerr << "ERROR::COULD NOT FIND THE MAP";
    background.setPosition(offsetx,offsety);
    background.setSize(sf::Vector2f(static_cast<float>(background_texture.getSize().x),static_cast<float>(background_texture.getSize().y)));// vMode.height));
    background.setTexture(&background_texture);
    background.setScale(0.6757,0.3647); //Non adattabili! per una risoluzione di |1360x800|

    //Graph
    mappa = new Node_map(window, gridSize_x, gridSize_y);
    mappa->loadTree("/home/giuseppe/Progetti/Lab_Progr_2/Assets/Config/Mappa.txt");
}

Game::~Game() {}

void Game::update() {
    while (window->pollEvent(event))
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();

    hero->handleInput();

    mappa->update();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        mappa->addTile();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F10))
    {
        mappa->saveTree("/home/giuseppe/Progetti/Lab_Progr_2/Assets/Config/Mappa.txt");
        std::cout << "MAPPA SALVATA SU 'Mappa.txt'" << std::endl;
    }
}

void Game::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->clear();

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        target->draw(background);

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        mappa->renderMap(target);

    hero->drawPlayer(target);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        mappa->render(target);

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

