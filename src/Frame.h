#ifndef FRAME_H
#define FRAME_H

class Frame {
public:
    int roll1, roll2, roll3;
    bool isStrike, isSpare;

    Frame(int r1 = 0, int r2 = 0, int r3 = 0);
    int getFrameScore();
};

#endif
