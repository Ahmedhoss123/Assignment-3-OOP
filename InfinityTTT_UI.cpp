#include "InfinityTTT_Classes.h"
#include <iostream>
#include "BoardGame_Classes.h"
using namespace std;

InfinityTTT_UI::InfinityTTT_UI() : UI<char>("Weclome to FCAI Infinity Tic-Tac-Toe Game by Dr El-Ramly", 3) {}

Player<char>* InfinityTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* InfinityTTT_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
