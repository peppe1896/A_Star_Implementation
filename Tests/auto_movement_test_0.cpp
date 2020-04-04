//
// Created by giuseppe on 31/03/20.
//

#include "gtest/gtest.h"

#include "../Game.h"

class auto_move_test : public ::testing::Test {
protected:
    virtual void SetUp()
    {
        test = new Game(0);
        mapp = test->getMap();
        create_array();
        player_test = test->getPlayer();
        mapp->setStart_test();
        mapp->setGoal_test();
        mapp->aStarTile();
        mapp->reconstructPath();
    }

    Game* test;
    nodeMap* mapp;
    player* player_test;
    std::array<sf::Vector2i, 22> expec;
    //Array for pre-defined path
    void create_array()
    {
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
    }
    std::vector<sf::Vector2f> _create_queue(std::vector<sf::Vector2i> in)
    {
        std::vector<sf::Vector2f> temp;
        for(auto& itr : in)
            temp.emplace_back(sf::Vector2f(static_cast<float>(itr.x), static_cast<float>(itr.y)));
        return temp;
    }

};

TEST_F(auto_move_test, move_player) {
    sf::Vector2f start_position = player_test->getPosition();
    for (float i = 0; i < 30.f; i++) {
        player_test->move_(sf::Vector2f(player_test->getPosition().x + i, player_test->getPosition().y + i));
        player_test->handleInput();
    }
    ASSERT_FALSE(start_position.x == player_test->getPosition().x)
                        << "X= " << start_position.x << " EXPECTED!= " << player_test->getPosition().x;
    ASSERT_FALSE(start_position.y == player_test->getPosition().y)
                        << "Y= " << start_position.y << " EXPECTED!= " << player_test->getPosition().y;
}