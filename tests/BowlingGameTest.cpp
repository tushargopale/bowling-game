#include <gtest/gtest.h>
#include "../src/BowlingGame.h"

TEST(BowlingGameTest, GameInit) {
    std::istringstream input("1 3 1 3 1 3 1 3 1 3 1 3 1 3 1 3 1 3 1 3"); // mock input
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());   // redirect cin

    BowlingGame g;
    EXPECT_NO_THROW(g.play(1));

    std::cin.rdbuf(orig); // restore cin
}

TEST(BowlingGameTest, GameWith10thFrameStrike) {
    std::istringstream input("1 3 1 3 1 3 1 3 1 3 1 3 1 3 1 3 1 3 10 10 2"); // mock input
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());   // redirect cin

    BowlingGame g;
    EXPECT_NO_THROW(g.play(1));

    std::cin.rdbuf(orig); // restore cin
}