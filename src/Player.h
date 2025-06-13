#ifndef PLAYER_H
#define PLAYER_H

#include "Frame.h"
#include <string>
using namespace std;

class Player {
private:
    Frame frames[10];
    int frameCount;
public:
    Player();
    void addFrame(int r1, int r2 = 0, int r3 = 0);
    int getTotalScore();
    void printScorecard();

private:
    int getNextRoll(int i) ;
    int getNextTwoRolls(int i);
    int getFrameScoreAt(int i);
};

#endif
