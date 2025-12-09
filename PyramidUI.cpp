#include "PyramidUI.h"
#include <iostream>
#include <limits>
using namespace std;

PyramidUI::PyramidUI() : UI<char>("Pyramid Tic Tac Toe", 2) {}

Player<char>* PyramidUI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* PyramidUI::get_move(Player<char>* player) {

    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << player->get_name() << " enter cell (row col): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    return get_computer_move(player);
}

vector<PyramidUI::Cell> PyramidUI::generate_moves(const PyramidBoard& board) {
    vector<Cell> moves;

    auto mat = board.get_board_matrix();

    for (int r = 0; r < board.get_rows(); r++) {
        for (int c = 0; c < board.get_columns(); c++) {
            if (mat[r][c] == '.')
                moves.push_back({ r, c });
        }
    }
    return moves;
}

int PyramidUI::minimax(PyramidBoard boardState,
    char aiSym, char oppSym,
    bool isAiTurn,
    int depth,
    int maxDepth)
{
    Player<char> ai("AI", aiSym, PlayerType::HUMAN);
    Player<char> op("OPP", oppSym, PlayerType::HUMAN);

    if (boardState.is_win(&ai)) return 10 - depth;
    if (boardState.is_win(&op)) return -10 + depth;

    if (depth >= maxDepth) return 0;

    char current = isAiTurn ? aiSym : oppSym;

    vector<Cell> moves = generate_moves(boardState);
    if (moves.empty())
        return 0;

    if (isAiTurn) {
        int best = -1000;
        for (auto& mv : moves) {
            PyramidBoard next = boardState;
            Move<char> m(mv.r, mv.c, current);
            next.update_board(&m);

            int score = minimax(next, aiSym, oppSym, false, depth + 1, maxDepth);
            best = max(best, score);
        }
        return best;
    }
    else {
        int best = 1000;
        for (auto& mv : moves) {
            PyramidBoard next = boardState;
            Move<char> m(mv.r, mv.c, current);
            next.update_board(&m);

            int score = minimax(next, aiSym, oppSym, true, depth + 1, maxDepth);
            best = min(best, score);
        }
        return best;
    }
}


Move<char>* PyramidUI::get_computer_move(Player<char>* player) {
    Board<char>* bp = player->get_board_ptr();
    PyramidBoard* board = dynamic_cast<PyramidBoard*>(bp);

    char aiSym = player->get_symbol();
    char oppSym = (aiSym == 'X' ? 'O' : 'X');

    vector<Cell> moves = generate_moves(*board);

    int bestScore = -1000;
    Cell bestMove = moves[0];

    int maxDepth = 4;   // ذكاء ممتاز + سرعة كويسة

    for (auto& mv : moves) {
        PyramidBoard next = *board;
        Move<char> m(mv.r, mv.c, aiSym);
        next.update_board(&m);

        int score = minimax(next, aiSym, oppSym, false, 1, maxDepth);

        if (score > bestScore) {
            bestScore = score;
            bestMove = mv;
        }
    }

    cout << player->get_name() << " (" << aiSym << ") chooses: "
        << bestMove.r << " " << bestMove.c << "\n";

    return new Move<char>(bestMove.r, bestMove.c, aiSym);
}
