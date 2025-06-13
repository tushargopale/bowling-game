#include "BowlingGame.h"
#define NO_OF_PLAYERS 1 // We can increase the players. Aim for this test is to calculate scores for one player only

int main() {
    BowlingGame game;
    game.play(NO_OF_PLAYERS);
    return 0;
}
