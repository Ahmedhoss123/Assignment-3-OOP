#include "UltimateTTT_UI.h"
#include <iostream>

using namespace std;

Player<char>* UltimateTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* UltimateTTT_UI::get_move(Player<char>* player) {
    if (!player) return nullptr;

   
    if (player->get_type() == PlayerType::HUMAN) {
        int r, c;
        while (true) {
            cout << player->get_name() << " (" << player->get_symbol()
                << ") - Enter row and column in [0..8] [0..8]: ";

            if ((cin >> r >> c) && !cin.fail()) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return new Move<char>(r, c, player->get_symbol());
            }
            else {
                cout << "Invalid input. Enter two integers between 0 and 8.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    
    Board<char>* bptr = player->get_board_ptr();
    if (!bptr) {
        return new Move<char>(0, 0, player->get_symbol());
    }

    auto mat = bptr->get_board_matrix();
    vector<pair<int, int>> empties;

    for (int i = 0; i < (int)mat.size(); ++i) {
        for (int j = 0; j < (int)mat[i].size(); ++j) {
            if (mat[i][j] == ' ') {
                empties.push_back({ i, j });
            }
        }
    }

    if (empties.empty()) {
        return new Move<char>(-1, -1, player->get_symbol());
    }

    int idx = rand() % empties.size();
    auto pr = empties[idx];

    cout << player->get_name() << " (" << player->get_symbol()
        << ") chooses: " << pr.first << " " << pr.second << "\n";

    return new Move<char>(pr.first, pr.second, player->get_symbol());
}
