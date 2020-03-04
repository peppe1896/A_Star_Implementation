#include "Game.h"

Game::Game()
{
    hero = new player();

    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Implementation A* search Alg.");
    this->window->setFramerateLimit((60));
}

Game::~Game()
{

}

void Game::updatePos()
{
    hero->handleInput();
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

void Game::update() {
    while (window->pollEvent(event))
        if (event.type == sf::Event::Closed)
            window->close();

    updatePos();
}

void Game::render()
{
    window->clear();

    hero->drawPlayer(this->window);

    window->display();

}