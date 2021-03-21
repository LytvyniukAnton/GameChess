#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
    Game game;
    game.Show();
    while(true){
        game.OneMove();
        if (game.isСheckForWhite()) {
            if (game.getLastColor() == "White") {
                game.CancelLastMove();
            }
            else {
                cout << "It's check for white..." << endl;
            }
        }
        if (game.isСheckForBlack()) {
            if (game.getLastColor() == "Black") {
                game.CancelLastMove();
            }
            else {
                cout << "It's check for black..." << endl;
            }
        }
        //------------------------------------
        if (game.isMateForWhite()) {
            if (game.getLastColor() == "White") {
                game.CancelLastMove();
            }
            else {
                cout << "-> It's mate for white !!! <-" << endl;
            }
        }
        if (game.isMateForBlack()) {
            if (game.getLastColor() == "Black") {
                game.CancelLastMove();
            }
            else {
                cout << "-> It's mate for black !!! <-" << endl;
            }
        }
        game.Show();
    }
    system("pause");
}
