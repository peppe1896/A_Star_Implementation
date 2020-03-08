#include "Game.h"

Game::Game()
{
    sf::VideoMode vMode(1360,800);
    this->window = new sf::RenderWindow(vMode, "Implementation A* search Alg.", sf::Style::Default);
    this->window->setFramerateLimit((60));

    hero = new player(window);

    //set Background (map)
    if(!background_texture.loadFromFile("/home/giuseppe/Progetti/Lab_Progr_2/Assets/Background/canvas.png"))
        std::cerr << "ERROR::COULD NOT FIND THE MAP";

    background.setSize(sf::Vector2f(vMode.width, vMode.height));
    background.setTexture(&background_texture);

}

Game::~Game()
{

}

void Game::update() {
    while (window->pollEvent(event))
        if (event.type == sf::Event::Closed)
            window->close();


    hero->handleInput();
}

void Game::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->clear();

    target->draw(background);

    hero->drawPlayer(target);

    window->display();

}

sf::VideoMode Game::getVideoMode()
{
    return vMode;
}

void Game::run()
{
    while (window->isOpen()){
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                    window->close();
        }
        update();
        render(this->window);
    }
}
