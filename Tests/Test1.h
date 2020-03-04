//
// Created by giuseppe on 03/03/20.
//

#ifndef LAB_PROGR_2_TEST1_H
#define LAB_PROGR_2_TEST1_H

#include "gtest/gtest.h"

class myFirstTest : ::testing::test
{
public:
    myFirstTest()
    {

    }
};

int main(int argv, char* argc)
{
    return RUN_ALL_TESTS();
}

#endif //LAB_PROGR_2_TEST1_H
