#include "DiamondTTT_UI.h"
#include "DiamondTTT_Board.h"
#include <iostream>
using namespace std;

DiamondTTT_UI::DiamondTTT_UI()
    : UI<char>("Diamond Tic-Tac-Toe: make a 3-line and a 4-line simultaneously (different directions).", 1) {
    srand((unsigned)time(nullptr));
}

DiamondTTT_UI::~DiamondTTT_UI() {}

Player<char>* DiamondTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* DiamondTTT_UI::get_move(Player<char>* player) {
    if (!player) return nullptr;
    if (player->get_type() == PlayerType::HUMAN) {
        int r, c;
        while (true) {
            cout << player->get_name() << " (" << player->get_symbol() << ") - enter row and column: ";
            if ((cin >> r >> c) && !cin.fail()) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return new Move<char>(r, c, player->get_symbol());
            }
            else {
                cout << "Invalid input. Enter two integers.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    else {
        Board<char>* bptr = player->get_board_ptr();
        if (!bptr) return new Move<char>(0, 0, player->get_symbol());
        auto mat = bptr->get_board_matrix();
        vector<pair<int, int>> empties;
        for (int i = 0; i < (int)mat.size(); ++i)
            for (int j = 0; j < (int)mat[0].size(); ++j)
                if (mat[i][j] == ' ') empties.push_back({ i,j });
        if (empties.empty()) return new Move<char>(-1, -1, player->get_symbol());
        int idx = rand() % empties.size();
        auto pr = empties[idx];
        cout << player->get_name() << " (" << player->get_symbol() << ") chooses: " << pr.first << " " << pr.second << "\n";
        return new Move<char>(pr.first, pr.second, player->get_symbol());
    }
}
