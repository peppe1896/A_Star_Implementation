//
// Created by giuseppe on 01/04/20.
//

#include "gtest/gtest.h"

#include "../Game.h"
#include "../Subject.h"

TEST(Observer, observer_attach) {
    Game *game = new Game(1);
    nodeMap *map = game->getMap();
    map->setStart_test();
    map->setGoal_test();
    map->aStarTile();
    map->reconstructPath();
    std::list<Observer *> obs_test = map->getObservers();
    int num_observer_previsti = 1;

    ASSERT_EQ(obs_test.size(), num_observer_previsti);
    ASSERT_EQ(obs_test.front(), game->getPlayer());
}

