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
        return get_best_computer_move(player);
    }
}
Move<char>* DiamondTTT_UI::get_best_computer_move(Player<char>* player) {
    Board<char>* bptr = player->get_board_ptr();
    if (!bptr) {
        return new Move<char>(0, 0, player->get_symbol());
    }

    DiamondTTT_Board* realBoard = dynamic_cast<DiamondTTT_Board*>(bptr);
    char aiSym = player->get_symbol();
    char oppSym = (aiSym == 'X' ? 'O' : 'X');

    auto mat = bptr->get_board_matrix();

    int bestScore = numeric_limits<int>::min();
    int bestR = -1, bestC = -1;
    int maxDepth = 5;

    if (realBoard) {
        for (int i = 0; i < (int)mat.size(); ++i) {
            for (int j = 0; j < (int)mat[i].size(); ++j) {
                if (mat[i][j] == ' ') {
                    DiamondTTT_Board simBoard = *realBoard;

                    Move<char> mv(i, j, aiSym);
                    if (!simBoard.update_board(&mv))
                        continue;

                    int score = minimax(simBoard, aiSym, oppSym, false, 1, maxDepth);

                    if (score > bestScore) {
                        bestScore = score;
                        bestR = i;
                        bestC = j;
                    }
                }
            }
        }
    }
    if (bestR == -1 || bestC == -1) {
        vector<pair<int, int>> empties;
        for (int i = 0; i < (int)mat.size(); ++i)
            for (int j = 0; j < (int)mat[i].size(); ++j)
                if (mat[i][j] == ' ')
                    empties.push_back({ i, j });

        if (empties.empty())
            return new Move<char>(-1, -1, aiSym);

        int idx = rand() % empties.size();
        auto pr = empties[idx];
        bestR = pr.first;
        bestC = pr.second;
    }

    cout << player->get_name() << " (" << player->get_symbol()
        << ") chooses: " << bestR << " " << bestC << "\n";

    return new Move<char>(bestR, bestC, aiSym);
}

int DiamondTTT_UI::minimax(DiamondTTT_Board boardState,
    char aiSym, char oppSym,
    bool isAiTurn,
    int depth,
    int maxDepth) {

    Player<char> ai("AI", aiSym, PlayerType::HUMAN);
    Player<char> opp("OPP", oppSym, PlayerType::HUMAN);

  
    if (boardState.is_win(&ai))
        return 10 - depth;
    if (boardState.is_win(&opp))
        return -10 + depth;
    if (boardState.is_draw(&ai))
        return 0;

    if (depth >= maxDepth)
        return 0;  
    auto mat = boardState.get_board_matrix();

    if (isAiTurn) {
        int best = numeric_limits<int>::min();

        for (int i = 0; i < (int)mat.size(); ++i) {
            for (int j = 0; j < (int)mat[i].size(); ++j) {
                if (mat[i][j] == ' ') {
                    DiamondTTT_Board nextBoard = boardState;
                    Move<char> mv(i, j, aiSym);
                    if (!nextBoard.update_board(&mv))
                        continue;

                    int score = minimax(nextBoard, aiSym, oppSym, false, depth + 1, maxDepth);
                    if (score > best) best = score;
                }
            }
        }

        if (best == numeric_limits<int>::min())
            return 0;

        return best;
    }
    else {
        int best = numeric_limits<int>::max();

        for (int i = 0; i < (int)mat.size(); ++i) {
            for (int j = 0; j < (int)mat[i].size(); ++j) {
                if (mat[i][j] == ' ') {
                    DiamondTTT_Board nextBoard = boardState;
                    Move<char> mv(i, j, oppSym);
                    if (!nextBoard.update_board(&mv))
                        continue;

                    int score = minimax(nextBoard, aiSym, oppSym, true, depth + 1, maxDepth);
                    if (score < best) best = score;
                }
            }
        }

        if (best == numeric_limits<int>::max())
            return 0;

        return best;
    }
}
