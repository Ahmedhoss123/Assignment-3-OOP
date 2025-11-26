#include "TTC5_UI.h"
#include <iostream>
using namespace std;

TTC5_UI::TTC5_UI() : UI("Welcome to 5x5 Tic Tac Toe!", 3) {}

Move<char>* TTC5_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << "), enter your move:\n";

        int x = get_coordinate("Enter row (0-4): ");
        int y = get_coordinate("Enter column (0-4): ");

        return new Move<char>(x, y, player->get_symbol());
    }
    else {
        // Computer player - random move
        // You can enhance this with AI later
        int x, y;
        Board<char>* board = player->get_board_ptr();
        auto board_matrix = board->get_board_matrix();

        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (board_matrix[x][y] != ' ');

        cout << "Computer (" << player->get_symbol() << ") plays at ("
            << x << ", " << y << ")\n";

        return new Move<char>(x, y, player->get_symbol());
    }
}

Player<char>* TTC5_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

int TTC5_UI::get_coordinate(const string& prompt) {
    int coord;
    while (true) {
        cout << prompt;
        cin >> coord;
        if (coord >= 0 && coord <= 4) {
            return coord;
        }
        cout << "Invalid input! Please enter a number between 0 and 4.\n";
    }
}
