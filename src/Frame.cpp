#include "Frame.h"

Frame::Frame(int r1, int r2, int r3) {
    roll1 = r1;
    roll2 = r2;
    roll3 = r3;
    isStrike = (r1 == 10);
    isSpare = (!isStrike && (r1 + r2 == 10));
}

int Frame::getFrameScore() {
    return roll1 + roll2 + roll3;
}
