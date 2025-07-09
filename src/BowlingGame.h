#ifndef BOWLINGGAME_H
#define BOWLINGGAME_H

#include "Player.h"

class BowlingGame {
public:
    BowlingGame();
public:
    void play(int playersCount);
};
int getNumericInput();
bool isNumeric(const string& str);
#endif
