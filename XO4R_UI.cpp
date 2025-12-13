#include "XO4R_Classes.h"
#include <iostream>
#include "BoardGame_Classes.h"
using namespace std;

XO4R_UI::XO4R_UI() : UI<char>("Welcome to Connect Four (6x7) by Dr El-Ramly", 3) {}

Player<char>* XO4R_UI::create_player(string& name, char symbol, PlayerType type) {
    // Fix: Check for both AI and COMPUTER types
    if (type == PlayerType::AI || type == PlayerType::COMPUTER) {
        cout << "Perfect Unbeatable AI activated!\n";
        // This constructor sets the internal type to PlayerType::AI
        return new XO4R_AI_Player(name, symbol);
    }
    return new Player<char>(name, symbol, type);
}

Move<char>* XO4R_UI::get_move(Player<char>* player) {
    // Special case: Perfect AI player
    if (player->get_type() == PlayerType::AI) {
        XO4R_AI_Player* ai = static_cast<XO4R_AI_Player*>(player);
        XO4R_Board* board = static_cast<XO4R_Board*>(player->get_board_ptr());
        return ai->make_perfect_move(board);
    }

    // Human or Random
    int x = -1, y = -1;
    auto b = player->get_board_ptr()->get_board_matrix();

    if (player->get_type() == PlayerType::HUMAN) {
        while (true) {
            cout << "\n" << player->get_name() << " (" << player->get_symbol() << "). Enter column (0-6): ";
            if (!(cin >> y)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter an integer between 0 and 6.\n";
                continue;
            }

            if (y >= 0 && y < 7) {
                bool full = true;
                for (int r = 5; r >= 0; --r) {
                    if (b[r][y] == '.') {
                        x = r;
                        full = false;
                        break;
                    }
                }
                if (!full) break;
                else cout << "Column is full! Try another.\n";
            }
            else {
                cout << "Invalid column. Please enter a number between 0 and 6.\n";
            }
        }
    }
    else {
        do {
            y = rand() % 7;
            x = -1;
            for (int r = 5; r >= 0; --r) {
                if (b[r][y] == '.') {
                    x = r;
                    break;
                }
            }
        } while (x == -1);
        cout << "\nRandom computer plays column: " << y << endl;
    }
    return new Move<char>(x, y, player->get_symbol());
}
