#include "Game.h"

Game::Game()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Implementation A* search Alg.");
    this->window->setFramerateLimit((60));

    player.setFillColor(sf::Color::Red);
    player.setSize(sf::Vector2f(50.f,50.f));
    player.setOutlineThickness(1.f);
    player.setOutlineColor(sf::Color::Yellow);

    player.setPosition(posPlayer);
}

Game::~Game()
{

}

void Game::updatePos()
{
    if(!sf::Mouse::isButtonPressed((sf::Mouse::Right))) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            posPlayer.y -= 3.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            posPlayer.y += 3.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            posPlayer.x -= 3.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            posPlayer.x += 3.f;
    }
    else
        std::cout << "FORCED_PAUSE"<< std::endl;
    player.setPosition(posPlayer);
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

    window->draw(player);

    window->display();

}