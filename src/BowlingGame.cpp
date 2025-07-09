#include "BowlingGame.h"
#include <iostream>
using namespace std;

BowlingGame::BowlingGame(){
    cout << "Welcome!" << endl;
}

bool isNumeric(const string& str) {
    if (str.empty()) return false;

    for (int i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) return false;
    }

    return true;
}

// Get validated numeric input from user
int getNumericInput() {
    string input;
    while (true) {
        cin >> input;
        if (isNumeric(input)) {
            return stoi(input); // convert valid string to int
        }
        cout << "  Invalid input! Please enter a valid integer: ";
    }
}

void BowlingGame::play(int playersCount) {
    Player player[playersCount];
    cout << "Enter bowling scores for 10 frames:\n";
    for (int frameNo = 1; frameNo <= 10; ++frameNo) {
        // for multiplayer game added this for loop. For this test only one player is considered
        for(int playerNumber = 0; playerNumber < playersCount; playerNumber++) {
            cout << "Player " << playerNumber + 1 << " is playing" << endl;
        
            int roll_1, roll_2 = 0, roll_3 = 0;
            cout << "Frame " << frameNo << ":\n";
            cout << "  Enter roll 1: ";
            roll_1 = getNumericInput();
            if (frameNo < 10 && roll_1 != 10) {
                cout << "  Enter roll 2: ";
                roll_2 = getNumericInput();
            } else if (frameNo == 10) {
                // Suggested Change 1:
                if (roll_1 != 10) {
                    cout << "  Enter roll 2: ";
                    roll_2 = getNumericInput();
                } else {
                    // skip roll 2
                    roll_2 = 0;
                }
                
                if (roll_1 == 10 || roll_1 + roll_2 == 10) {
                    cout << "  Enter roll 3 (bonus roll): ";
                    roll_3 = getNumericInput();
                }
            }

            try {
                player[playerNumber].addFrame(roll_1, roll_2, roll_3);
                player[playerNumber].printScorecard();
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << "\n";
                --frameNo;
            }
        }
    }

    // Total score for one player
    cout << "Final Score: " << player[0].getTotalScore() << "\n";
}
