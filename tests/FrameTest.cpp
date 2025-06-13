#include <gtest/gtest.h>
#include "../src/Frame.h"

TEST(FrameTest, FrameScoreCalculation) {
    Frame f(4, 5, 0);
    EXPECT_EQ(f.getFrameScore(), 9);
}

TEST(FrameTest, FrameScoreCalculationForFrame10) {
    Frame f(4, 5, 10);
    EXPECT_EQ(f.getFrameScore(), 19);
}
