#include "AIPlayer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>
using namespace std;

AIPlayer::AIPlayer(string name, char symbol, PlayerType type)
    : Player<char>(name, symbol, type), difficulty(2) {
    opponentSymbol = (symbol == 'X') ? 'O' : 'X';
    srand(time(0));
}
AIPlayer::AIPlayer(char symbol, char opponent, int diff, string name)
    : Player<char>(name, symbol, PlayerType::AI),
    opponentSymbol(opponent), difficulty(diff) {
    srand(time(0));
}
int AIPlayer::evaluateMove(TTC5_Board& board, int x, int y) {
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
        board.update_board(x, y, ' '); 

        if (currentScore > 0) {
            score += currentScore * 100;
        }
    }
    if (board.update_board(x, y, opponentSymbol)) {
        int opponentScore = board.calculate_score(opponentSymbol);
        board.update_board(x, y, ' ');

        if (opponentScore > 0) {
            score += opponentScore * 80;
        }
    }
    return score;
}
bool AIPlayer::checkImmediateWin(TTC5_Board& board, char symbol) {
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
bool AIPlayer::checkImmediateBlock(TTC5_Board& board) {
    return checkImmediateWin(board, opponentSymbol);
}
void AIPlayer::get_move(TTC5_Board& board, int& x, int& y) {
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
        cout << "AI chooses strategic position: (" << x << ", " << y << ")\n";
        return;
    }
    if (difficulty == 1) {
        int idx = rand() % emptyCells.size();
        x = emptyCells[idx].first;
        y = emptyCells[idx].second;
        cout << "AI (Easy) chooses randomly: (" << x << ", " << y << ")\n";
        return;
    }
    if (difficulty >= 2) {
        for (const auto& cell : emptyCells) {
            board.update_board(cell.first, cell.second, symbol);
            if (board.calculate_score(symbol) > 0) {
                x = cell.first;
                y = cell.second;
                cout << "AI wins immediately: (" << x << ", " << y << ")\n";
                return;
            }
            board.update_board(cell.first, cell.second, ' ');
        }
    }
    if (difficulty >= 2) {
        for (const auto& cell : emptyCells) {
            board.update_board(cell.first, cell.second, opponentSymbol);
            if (board.calculate_score(opponentSymbol) > 0) {
                x = cell.first;
                y = cell.second;
                board.update_board(cell.first, cell.second, ' ');
                cout << "AI blocks opponent: (" << x << ", " << y << ")\n";
                return;
            }
            board.update_board(cell.first, cell.second, ' ');
        }
    }
    vector<pair<int, pair<int, int>>> scoredMoves;

    for (const auto& cell : emptyCells) {
        int moveScore = evaluateMove(board, cell.first, cell.second);
        scoredMoves.push_back({ moveScore, {cell.first, cell.second} });
    }
    sort(scoredMoves.rbegin(), scoredMoves.rend());
    x = scoredMoves[0].second.first;
    y = scoredMoves[0].second.second;

    if (difficulty == 2) {
        cout << "AI (Medium) chooses: (" << x << ", " << y << ")\n";
    }
    else {
        cout << "AI (Hard) chooses: (" << x << ", " << y << ") ";
        cout << "Score: " << scoredMoves[0].first << "\n";
    }
}
pair<int, int> AIPlayer::calculate_best_move(TTC5_Board& board) {
    int x, y;
    get_move(board, x, y);
    return { x, y };
}
void AIPlayer::set_difficulty(int level) {
    if (level >= 1 && level <= 3) {
        difficulty = level;
    }
}
string AIPlayer::get_difficulty_string() const {
    switch (difficulty) {
    case 1: return "Easy";
    case 2: return "Medium";
    case 3: return "Hard";
    default: return "Medium";
    }
}