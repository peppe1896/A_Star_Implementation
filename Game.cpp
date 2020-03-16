#include "Game.h"

Game::Game()
{
    vMode.width = 1024;
    vMode.height = 1024;
    this->window = new sf::RenderWindow(vMode, "Implementation A* search Alg.", sf::Style::Default);
    this->window->setFramerateLimit((60));

    hero = new player(window, 4.f);

    //set Background (map)
    if(!background_texture.loadFromFile("/home/giuseppe/Progetti/Lab_Progr_2/Assets/Background/canvas.png"))
        std::cerr << "ERROR::COULD NOT FIND THE MAP";

    background.setSize(sf::Vector2f(vMode.width, vMode.height));
    background.setTexture(&background_texture);
    show_bck = true;

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
                show_bck= false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::B))
                show_bck = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))// && sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            window->close();
    hero->handleInput();
    mappa->update();
}

void Game::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->clear();

    if(show_bck)
        target->draw(background);

    hero->drawPlayer(target);
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
