#include "SUS_Classes.h"
#include <iostream>
#include <cctype>
using namespace std;

SUS_UI::SUS_UI() : UI<char>("=== FCAI SUS Game ===", 3) {}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::AI) {
        cout << "Perfect Unbeatable AI activated!\n";
        return new SUS_AI_Player(name, symbol);
    }
    return new Player<char>(name, symbol, type);
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    // Special case: Perfect AI player
    if (player->get_type() == PlayerType::AI) {
        SUS_AI_Player* ai = static_cast<SUS_AI_Player*>(player);
        SUS_Board* board = static_cast<SUS_Board*>(player->get_board_ptr());
        return ai->make_perfect_move(board);
    }

    // Human or Random
    int x, y;
    char choice;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol()
            << ") enter move (S/U x y): ";
        cin >> choice >> x >> y;
        choice = toupper(choice);
    }
    else {
        auto b = player->get_board_ptr()->get_board_matrix();
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (b[x][y] != '.');
        choice = (rand() % 2 == 0) ? 'S' : 'U';
		cout << "\nRandom computer plays: " << choice << " " << x << " " << y << endl;
    }

	return new Move<char>(x, y, choice);
}
