#include "NumTTT_Classes.h"
#include <iostream>
using namespace std;

NumTTT_UI::NumTTT_UI() : UI<int>("=== FCAI Numerical Tic-Tac-Toe ===", 3) {}

Player<int>* NumTTT_UI::create_player(string& name, int symbol, PlayerType type) {
    return new Player<int>(name, symbol, type);
}

Move<int>* NumTTT_UI::get_move(Player<int>* player) {
    int r, c, num;
    cout << player->get_name() << " ("
        << (player->get_symbol() % 2 ? "odd" : "even")
        << " numbers) enter your move (row col number): ";
    cin >> r >> c >> num;
    return new Move<int>(r, c, num);
}
