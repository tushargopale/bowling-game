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

TEST(BowlingGameTest, CatchBlockWhenFrameScoreInvalid) {
    // Invalid input: 1st frame has rolls 7 + 6 = 13 (>10), which should throw
    std::istringstream input("7 6 1 3 1 3 1 3 1 3 1 3 1 3 1 3 1 3 1 3 1 3"); // Invalid frame, should throw from addFrame()
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());   // redirect cin

    BowlingGame g;
    EXPECT_NO_THROW(g.play(1));  // play() handles the exception internally

    std::cin.rdbuf(orig); // restore cin
}

TEST(BowlingGameTest, getNumericInput) {
    std::istringstream input("A 1"); // mock input. First invalid and then valid
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());   // redirect cin

    EXPECT_EQ(getNumericInput(), 1);

    std::cin.rdbuf(orig); // restore cin
}

TEST(BowlingGameTest, isNumeric_Yes) {
    EXPECT_EQ(isNumeric("10"), true);
}

TEST(BowlingGameTest, isNumeric_No) {
    EXPECT_EQ(isNumeric("A"), false);
}
