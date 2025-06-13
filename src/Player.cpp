#include "Player.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

Player::Player() {
    frameCount = 0;
}

void Player::addFrame(int r1, int r2, int r3) {
    if (frameCount >= 10)
        throw logic_error("Cannot add more than 10 frames.");

    if (r1 < 0 || r2 < 0 || r3 < 0 || r1 > 10 || r2 > 10 || r3 > 10)
        throw invalid_argument("Pins must be in range 0-10.");

    if (frameCount < 9 && r1 + r2 > 10)
        throw invalid_argument("Invalid frame: pins exceed 10.");

    if (frameCount == 9 && r1 != 10 && r1 + r2 > 10)
        throw invalid_argument("10th frame invalid: pins exceed 10.");

    frames[frameCount++] = Frame(r1, r2, r3);
}

int Player::getNextRoll(int i) {
    return (i + 1 < frameCount) ? frames[i + 1].roll1 : 0;
}

int Player::getNextTwoRolls(int i) {
    if (i + 1 >= frameCount) return 0;
    if (frames[i + 1].isStrike && i + 2 < frameCount)
        return frames[i + 1].roll1 + frames[i + 2].roll1;
    else
        return frames[i + 1].roll1 + frames[i + 1].roll2;
}

int Player::getFrameScoreAt(int i) {
    Frame& f = frames[i];
    int score = f.getFrameScore();

    if (i < 9) {
        if (f.isStrike) {
            if (i + 1 >= frameCount) throw runtime_error("Strike waiting for future rolls");
            score += getNextTwoRolls(i);
        } else if (f.isSpare) {
            if (i + 1 >= frameCount) throw runtime_error("Spare waiting for next roll");
            score += getNextRoll(i);
        }
    }

    return score;
}

int Player::getTotalScore() {
    int total = 0;
    for (int i = 0; i < frameCount; ++i)
        total += getFrameScoreAt(i);
    return total;
}

void Player::printScorecard() {
    cout << "\nScorecard after " << frameCount << " frame(s):\n";
    cout << "Frame\tRolls\t\tScore\n";

    int total = 0;
    for (int i = 0; i < frameCount; ++i) {
        Frame& f = frames[i];

        string r1 = (f.roll1 == 10) ? "X" : to_string(f.roll1);
        string r2 = "-";
        string r3 = (f.roll3 > 0) ? to_string(f.roll3) : "";

        if (i < 9) {
            r2 = (f.isStrike) ? " " : (f.isSpare ? "/" : to_string(f.roll2));
        } else {
            r2 = (f.roll1 == 10) ? ((f.roll2 == 10) ? "X" : to_string(f.roll2))
                : ((f.roll1 + f.roll2 == 10) ? "/" : to_string(f.roll2));
            if (f.roll3 == 10) r3 = "X";
            else if ((f.roll2 + f.roll3 == 10) && f.roll2 != 10) r3 = "/";
        }

        try {
            int frameScore = getFrameScoreAt(i);
            total += frameScore;

            cout << i + 1 << "\t" << r1 << " " << r2;
            if (!r3.empty()) cout << " " << r3;
            else cout << "\t";
            cout << "\t" << total << endl;
        } catch (...) {
            cout << i + 1 << "\t" << r1 << " " << r2;
            if (!r3.empty()) cout << " " << r3;
            else cout << "\t";
            cout << "\t--\n";
        }
    }
    cout << endl;
}
