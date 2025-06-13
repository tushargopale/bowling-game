#include "BowlingGame.h"
#include <iostream>
using namespace std;

BowlingGame::BowlingGame(){
    cout << "Welcome!" << endl;
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
            cin >> roll_1;

            if (frameNo < 10 && roll_1 != 10) {
                cout << "  Enter roll 2: ";
                cin >> roll_2;
            } else if (frameNo == 10) {
                cout << "  Enter roll 2: ";
                cin >> roll_2;
                if (roll_1 == 10 || roll_1 + roll_2 == 10) {
                    cout << "  Enter roll 3 (bonus roll): ";
                    cin >> roll_3;
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
