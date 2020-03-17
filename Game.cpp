#include "Game.h"

Game::Game()
{
    offsetx = 3.f;
    offsety = 2.f;
    vMode.width = 1360;
    vMode.height = 800;
    this->window = new sf::RenderWindow(vMode, "Implementation A* search Alg.", sf::Style::Default);
    this->window->setFramerateLimit((60));

    hero = new player(window, 4.f);

    //set Background (map)
    if(!background_texture.loadFromFile("/home/giuseppe/Progetti/Lab_Progr_2/Assets/Background/canvas.png"))
        std::cerr << "ERROR::COULD NOT FIND THE MAP";
    background.setPosition(offsetx,offsety);
    background.setSize(sf::Vector2f(static_cast<float>(background_texture.getSize().x),static_cast<float>(background_texture.getSize().y)));// vMode.height));
    background.setTexture(&background_texture);
    background.setScale(0.6757,0.364); //Non adattabili! per una risoluzione di |1360x800|
    show_bck = false;

    //Graph
    //creo un oggetto Node_map che in teoria
    //ha il grafo

    //Devo creare un handle input per Node_map
    mappa = new Node_map(window);
}

Game::~Game()
{

}

void Game::update() {
    while (window->pollEvent(event))
        if (event.type == sf::Event::Closed)
            window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
            show_bck= true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
            show_bck = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))// && sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            window->close();
    hero->handleInput();

    mappa->update();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        mappa->addTile();
}

void Game::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->clear();

    hero->drawPlayer(target);
    if(show_bck)
        target->draw(background);
    else
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

sf::VideoMode Game::getVideoMode()
{
    return vMode;
}
