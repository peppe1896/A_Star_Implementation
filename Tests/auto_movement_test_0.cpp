//
// Created by giuseppe on 31/03/20.
//

#include "gtest/gtest.h"

#include "../Game.h"

TEST(player, move_player)
{
    Game* test_game = new Game(0);
    player* hero_test = test_game->getPlayer();
    sf::Vector2f start_position = hero_test->getPosition();
    for(float i = 0; i< 30.f; i++)
        hero_test->move(sf::Vector2f(hero_test->getPosition().x + i , hero_test->getPosition().y + i));
    ASSERT_FALSE(start_position.x != hero_test->getPosition().x && start_position.y != hero_test->getPosition().y);

    delete hero_test;
    delete test_game;

}

TEST(player, auto_mover)
{
    Game* test_game = new Game(0);
    player* hero_test = test_game->getPlayer();

    sf::Vector2f initial = hero_test->getPosition();

    std::array<sf::Vector2i, 22> expec;

    expec[0] = sf::Vector2i(69,6);
    expec[1] = sf::Vector2i(68,6);
    expec[2] = sf::Vector2i(67,6);
    expec[3] = sf::Vector2i(66,6);
    expec[4] = sf::Vector2i(65,6);
    expec[5] = sf::Vector2i(64,6);
    expec[6] = sf::Vector2i(63,6);
    expec[7] = sf::Vector2i(62,6);
    expec[8] = sf::Vector2i(62,7);
    expec[9] = sf::Vector2i(62,8);
    expec[10] = sf::Vector2i(62,9);
    expec[11] = sf::Vector2i(62,10);
    expec[12] = sf::Vector2i(62,11);
    expec[13] = sf::Vector2i(62,12);
    expec[14] = sf::Vector2i(62,13);
    expec[15] = sf::Vector2i(62,14);
    expec[16] = sf::Vector2i(62,15);
    expec[17] = sf::Vector2i(62,16);
    expec[18] = sf::Vector2i(62,17);
    expec[19] = sf::Vector2i(62,18);
    expec[20] = sf::Vector2i(61,18);
    expec[21] = sf::Vector2i(60,18);

    std::vector<sf::Vector2i> auto_percorso;

    for(auto itr : expec)
        auto_percorso.push_back(itr);

    hero_test->create_queue_test(auto_percorso);
    std::vector<sf::Vector2f> queue = hero_test->getQueue();
    EXPECT_EQ(hero_test->getPosition().x, queue.back().x);
    EXPECT_EQ(hero_test->getPosition().y, queue.back().y);
    ASSERT_TRUE(initial != hero_test->getPosition());
}