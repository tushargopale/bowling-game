#include <gtest/gtest.h>
#include "../src/Player.h"

// Helper to create a player and add frames
Player createPlayerWithFrames(std::vector<std::tuple<int, int, int>> rolls) {
    Player p;
    for (auto& [r1, r2, r3] : rolls) {
        p.addFrame(r1, r2, r3);
    }
    return p;
}

Player createPlayerWithFrames(int rolls[10][3]) {
    Player p;
    for (int i = 0; i < 10; ++i) {
        p.addFrame(rolls[i][0], rolls[i][1], rolls[i][2]);
    }
    return p;
}

TEST(PlayerTest, AddValidFrames) {
    Player p;
    EXPECT_NO_THROW(p.addFrame(3, 6, 0));
    EXPECT_NO_THROW(p.addFrame(10, 0, 0));  // strike
    EXPECT_NO_THROW(p.addFrame(7, 3, 0));   // spare
}

TEST(PlayerTest, RejectInvalidFrameMoreThanTenFrames) {
    Player p;
    for (int i = 0; i < 10; ++i) {
        p.addFrame(4, 5, 0);
    }
    EXPECT_THROW(p.addFrame(3, 3, 0), std::logic_error);
}

TEST(PlayerTest, RejectInvalidPinsOverTen) {
    Player p;
    EXPECT_THROW(p.addFrame(11, 0, 0), std::invalid_argument);
    EXPECT_THROW(p.addFrame(6, 5, 0), std::invalid_argument);  // sum > 10
}

TEST(PlayerTest, InvalidTenthFrameMoreThanTenPinsWithoutStrike) {
    Player p;
    
    // Add 9 valid frames first
    for (int i = 0; i < 9; ++i)
        p.addFrame(1, 1, 0);
    
    // 10th frame: r1 != 10 and r1 + r2 > 10 → should throw
    EXPECT_THROW(p.addFrame(6, 5, 0), std::invalid_argument);
}

TEST(PlayerTest, TotalScoreWithNoStrikesOrSpares) {
    int input[10][3] = {
        {3, 6, 0}, {4, 5, 0}, {2, 3, 0}, {1, 2, 0}, {0, 0, 0},
        {7, 1, 0}, {6, 2, 0}, {3, 4, 0}, {2, 5, 0}, {4, 3, 0}
    };


    Player p = createPlayerWithFrames({
        {3, 6, 0}, {4, 5, 0}, {2, 3, 0}, {1, 2, 0}, {0, 0, 0},
        {7, 1, 0}, {6, 2, 0}, {3, 4, 0}, {2, 5, 0}, {4, 3, 0}
    });
    EXPECT_EQ(p.getTotalScore(), 63);
}

TEST(PlayerTest, TotalScoreWithStrikes) {
    Player p = createPlayerWithFrames({
        {10, 0, 0}, {4, 5, 0}, {3, 3, 0}, {2, 2, 0},
        {10, 0, 0}, {10, 0, 0}, {5, 4, 0}, {6, 2, 0}, {3, 4, 0}, {2, 3, 0}
    });
    EXPECT_EQ(p.getTotalScore(), 111);
}

TEST(PlayerTest, TotalScoreWithSpares) {
    Player p = createPlayerWithFrames({
        {7, 3, 0}, {4, 5, 0}, {6, 4, 0}, {2, 3, 0},
        {5, 5, 0}, {5, 3, 0}, {6, 2, 0}, {3, 4, 0}, {2, 5, 0}, {4, 3, 0}
    });
    EXPECT_EQ(p.getTotalScore(), 92);
}

TEST(PlayerTest, TenthFrameSpecialHandlingStrike) {
    Player p = createPlayerWithFrames({
        {1, 1, 0}, {1, 1, 0}, {1, 1, 0}, {1, 1, 0}, {1, 1, 0},
        {1, 1, 0}, {1, 1, 0}, {1, 1, 0}, {1, 1, 0}, {10, 10, 10}
    });
    EXPECT_EQ(p.getTotalScore(), 48); // first 9 frames = 18, last = 30
}

TEST(PlayerTest, TenthFrameSpareExtraRoll) {
    Player p = createPlayerWithFrames({
        {1, 1, 0}, {1, 1, 0}, {1, 1, 0}, {1, 1, 0}, {1, 1, 0},
        {1, 1, 0}, {1, 1, 0}, {1, 1, 0}, {1, 1, 0}, {7, 3, 10}
    });
    EXPECT_EQ(p.getTotalScore(), 38); // first 9 frames = 18
}
