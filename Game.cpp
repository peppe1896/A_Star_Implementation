#include "Game.h"

Game::Game()
{
    sf::VideoMode vMode(1360,800);
    this->window = new sf::RenderWindow(vMode, "Implementation A* search Alg.", sf::Style::Default);
    this->window->setFramerateLimit((60));

    hero = new player(window);

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

void Game::render()
{
    window->clear();

    hero->drawPlayer(this->window);

    window->display();

}

sf::VideoMode Game::getVideoMode() {
    return vMode;
}

void Game::run()
{
    while (window->isOpen()){
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        update();
        render();
    }
}
