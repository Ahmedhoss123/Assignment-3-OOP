#ifndef MISERETTT_UI_H
#define MISERETTT_UI_H

#include "BoardGame_Classes.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>

class MisereTTT_UI : public UI<char> {
public:
    MisereTTT_UI()
        : UI<char>("Welcome to Mis¨¨re Tic-Tac-Toe (avoid making 3-in-a-row)!", 1) {
        srand((unsigned)time(nullptr));
    }

    virtual ~MisereTTT_UI() {}

    // create_player used by UI::setup_players()
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    // get_move: human input or random computer move
    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::HUMAN) {
            int x, y;
            while (true) {
                cout << player->get_name() << " (" << player->get_symbol() << ") - enter row and column (e.g. 0 2): ";
                if ((cin >> x >> y) && !cin.fail()) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                else {
                    cout << "Invalid input. Enter two integers separated by space.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            return new Move<char>(x, y, player->get_symbol());
        }
        else {
            // Computer: random empty cell
            Board<char>* bptr = player->get_board_ptr();
            if (!bptr) return new Move<char>(0, 0, player->get_symbol());

            vector<pair<int, int>> empties;
            auto mat = bptr->get_board_matrix();
            int r = (int)mat.size();
            int c = (int)mat[0].size();
            for (int i = 0; i < r; ++i)
                for (int j = 0; j < c; ++j)
                    if (mat[i][j] == ' ')
                        empties.push_back({ i,j });

            if (empties.empty()) return new Move<char>(-1, -1, player->get_symbol());
            int idx = rand() % empties.size();
            auto pr = empties[idx];
            cout << player->get_name() << " (" << player->get_symbol() << ") chooses: " << pr.first << " " << pr.second << "\n";
            return new Move<char>(pr.first, pr.second, player->get_symbol());
        }
    }
};

#endif // MISERETTT_UI_H
