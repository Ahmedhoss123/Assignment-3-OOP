#include "AIPlayer.h"
#include <algorithm>

// Updated class name
FourByFour_AI_Player::FourByFour_AI_Player(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::AI) {}

Move<char>* FourByFour_AI_Player::get_move(Board<char>* b) {
    auto board = dynamic_cast<FourByFourBoard*>(b);

    int bestVal = -100000;
    Move<char>* bestMove = nullptr;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board->get_cell(i, j) == symbol) {

                int dx[4] = { 1,-1,0,0 };
                int dy[4] = { 0,0,1,-1 };

                for (int k = 0; k < 4; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];

                    if (ni >= 0 && ni < 4 && nj >= 0 && nj < 4 && board->get_cell(ni, nj) == '.') {
                        auto move = new FourByFourMove<char>(i, j, ni, nj, symbol);

                        if (board->update_board(move)) {
                            int val = minimax(board, 0, false);
                            board->undo_move(move);

                            if (val > bestVal) {
                                bestVal = val;
                                bestMove = move;
                            }
                            else {
                                delete move;
                            }
                        }
                        else {
                            delete move;
                        }
                    }
                }
            }
        }
    }
    return bestMove ? bestMove : new FourByFourMove<char>(0, 0, 0, 0, symbol); // Fallback
}

int FourByFour_AI_Player::minimax(FourByFourBoard* board, int depth, bool isMax) {
    if (board->is_win(this)) return 10 - depth;
    // Check opponent win
    Player<char> oppPlayer("Opp", (symbol == 'X' ? 'O' : 'X'), PlayerType::HUMAN);
    if (board->is_win(&oppPlayer)) return -10 + depth;

    if (depth >= 4) return 0; // Limit depth

    char opp = (symbol == 'X') ? 'O' : 'X';

    if (isMax) {
        int best = -100000;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board->get_cell(i, j) == symbol) {
                    for (int d = 0; d < 4; d++) {
                        int dx[4] = { 1,-1,0,0 };
                        int dy[4] = { 0,0,1,-1 };
                        int ni = i + dx[d], nj = j + dy[d];
                        if (ni >= 0 && ni < 4 && nj >= 0 && nj < 4 && board->get_cell(ni, nj) == '.') {
                            auto m = new FourByFourMove<char>(i, j, ni, nj, symbol);
                            if (board->update_board(m)) {
                                best = max(best, minimax(board, depth + 1, false));
                                board->undo_move(m);
                            }
                            delete m;
                        }
                    }
                }
            }
        }
        return best;
    }
    else {
        int best = 100000;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board->get_cell(i, j) == opp) {
                    for (int d = 0; d < 4; d++) {
                        int dx[4] = { 1,-1,0,0 };
                        int dy[4] = { 0,0,1,-1 };
                        int ni = i + dx[d], nj = j + dy[d];
                        if (ni >= 0 && ni < 4 && nj >= 0 && nj < 4 && board->get_cell(ni, nj) == '.') {
                            auto m = new FourByFourMove<char>(i, j, ni, nj, opp);
                            if (board->update_board(m)) {
                                best = min(best, minimax(board, depth + 1, true));
                                board->undo_move(m);
                            }
                            delete m;
                        }
                    }
                }
            }
        }
        return best;
    }
}
