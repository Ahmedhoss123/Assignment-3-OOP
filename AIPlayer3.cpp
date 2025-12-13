#include "AIPlayer3.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>
using namespace std;

// Updated Class Names
TTC5_AI_Player::TTC5_AI_Player(string name, char symbol, PlayerType type)
    : Player<char>(name, symbol, type), difficulty(2) {
    opponentSymbol = (symbol == 'X') ? 'O' : 'X';
    // FIXED: Static cast to avoid C4244 warning
    srand(static_cast<unsigned int>(time(0)));
}
TTC5_AI_Player::TTC5_AI_Player(char symbol, char opponent, int diff, string name)
    : Player<char>(name, symbol, PlayerType::AI),
    opponentSymbol(opponent), difficulty(diff) {
    // FIXED: Static cast to avoid C4244 warning
    srand(static_cast<unsigned int>(time(0)));
}

int TTC5_AI_Player::evaluateMove(TTC5_Board& board, int x, int y) {
    int score = 0;
    if (x == 2 && y == 2) score += 100;

    else if ((x == 1 && y == 1) || (x == 1 && y == 3) ||
        (x == 3 && y == 1) || (x == 3 && y == 3)) {
        score += 50;
    }
    else if ((x == 0 || x == 4) && (y == 0 || y == 4)) {
        score += 30;
    }
    else if ((x == 0 && y == 2) || (x == 2 && y == 0) ||
        (x == 2 && y == 4) || (x == 4 && y == 2)) {
        score += 20;
    }
    if (board.update_board(x, y, symbol)) {
        int currentScore = board.calculate_score(symbol);
        board.update_board(x, y, ' '); // Undo

        if (currentScore > 0) {
            score += currentScore * 100;
        }
    }
    if (board.update_board(x, y, opponentSymbol)) {
        int opponentScore = board.calculate_score(opponentSymbol);
        board.update_board(x, y, ' '); // Undo

        if (opponentScore > 0) {
            score += opponentScore * 80;
        }
    }
    return score;
}

bool TTC5_AI_Player::checkImmediateWin(TTC5_Board& board, char symbol) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board.get_cell(i, j) == ' ') {
                board.update_board(i, j, symbol);
                bool hasWin = (board.calculate_score(symbol) > 0);
                board.update_board(i, j, ' ');
                if (hasWin) return true;
            }
        }
    }
    return false;
}

bool TTC5_AI_Player::checkImmediateBlock(TTC5_Board& board) {
    return checkImmediateWin(board, opponentSymbol);
}

void TTC5_AI_Player::get_move(TTC5_Board& board, int& x, int& y) {
    cout << "\n " << name << " (" << get_difficulty_string() << ") is thinking...\n";

    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board.get_cell(i, j) == ' ') {
                emptyCells.push_back({ i, j });
            }
        }
    }

    if (emptyCells.empty()) {
        x = y = -1;
        return;
    }
    if (emptyCells.size() == 25) {
        vector<pair<int, int>> strategicMoves = {
            {2, 2},
            {1, 1}, {1, 3}, {3, 1}, {3, 3},
            {0, 0}, {0, 4}, {4, 0}, {4, 4}
        };

        int idx = rand() % strategicMoves.size();
        x = strategicMoves[idx].first;
        y = strategicMoves[idx].second;
        return;
    }

    vector<pair<int, pair<int, int>>> scoredMoves;

    for (const auto& cell : emptyCells) {
        int moveScore = evaluateMove(board, cell.first, cell.second);
        scoredMoves.push_back({ moveScore, {cell.first, cell.second} });
    }
    sort(scoredMoves.rbegin(), scoredMoves.rend());
    x = scoredMoves[0].second.first;
    y = scoredMoves[0].second.second;
}

pair<int, int> TTC5_AI_Player::calculate_best_move(TTC5_Board& board) {
    int x, y;
    get_move(board, x, y);
    return { x, y };
}

void TTC5_AI_Player::set_difficulty(int level) {
    if (level >= 1 && level <= 3) {
        difficulty = level;
    }
}

string TTC5_AI_Player::get_difficulty_string() const {
    switch (difficulty) {
    case 1: return "Easy";
    case 2: return "Medium";
    case 3: return "Hard";
    default: return "Medium";
    }
}
