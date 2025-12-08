#include "TTC5_Board.h"
#include <iostream>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

TTC5_Board::TTC5_Board() : Board(5, 5) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = ' ';
        }
    }
	srand(time(0));
}
bool TTC5_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 5 || y < 0 || y >= 5 || board[x][y] != ' ') {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool TTC5_Board::update_board(int x, int y, char symbol) {
    if (x < 0 || x >= 5 || y < 0 || y >= 5 || board[x][y] != ' ') {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;
    return true;
}

void TTC5_Board::display_board() {
    cout << "\n   0   1   2   3   4\n";
    cout << "  ---------------------\n";
    for (int i = 0; i < 5; i++) {
        cout << i << " | ";
        for (int j = 0; j < 5; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n  ---------------------\n";
    }
}

int TTC5_Board::calculate_score(char symbol) const {
    int score = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == symbol &&
                board[i][j + 1] == symbol &&
                board[i][j + 2] == symbol) {
                score++;
            }
        }
    }

    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 3; i++) {
            if (board[i][j] == symbol &&
                board[i + 1][j] == symbol &&
                board[i + 2][j] == symbol) {
                score++;
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == symbol &&
                board[i + 1][j + 1] == symbol &&
                board[i + 2][j + 2] == symbol) {
                score++;
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 2; j < 5; j++) {
            if (board[i][j] == symbol &&
                board[i + 1][j - 1] == symbol &&
                board[i + 2][j - 2] == symbol) {
                score++;
            }
        }
    }

    return score;
}

bool TTC5_Board::is_win(Player<char>* player) {
    if (n_moves < 24) return false;

    char current_symbol = player->get_symbol();
    char opponent_symbol = (current_symbol == 'X') ? 'O' : 'X';

    int my_score = calculate_score(current_symbol);
    int opponent_score = calculate_score(opponent_symbol);

    if (my_score > opponent_score) {
        cout << "\n=== FINAL SCORES ===" << endl;
        cout << player->get_name() << " (" << current_symbol << "): " << my_score << " points" << endl;
        cout << "Opponent: " << opponent_score << " points" << endl;
        cout << player->get_name() << " WINS!" << endl;
        cout << "===================" << endl;
        return true;
    }
    return false;
}


bool TTC5_Board::is_lose(Player<char>* player) {
    if (n_moves < 24) return false;

    char current_symbol = player->get_symbol();
    char opponent_symbol = (current_symbol == 'X') ? 'O' : 'X';

    int my_score = calculate_score(current_symbol);
    int opponent_score = calculate_score(opponent_symbol);

    if (my_score < opponent_score) {
        cout << "\n=== FINAL SCORES ===" << endl;
        cout << player->get_name() << " (" << current_symbol << "): " << my_score << " points" << endl;
        cout << "Opponent: " << opponent_score << " points" << endl;
        cout << "Opponent WINS!" << endl;
        cout << "===================" << endl;
        return true;
    }
    return false;
}

bool TTC5_Board::is_draw(Player<char>* player) {
    if (n_moves < 24) return false;

    char current_symbol = player->get_symbol();
    char opponent_symbol = (current_symbol == 'X') ? 'O' : 'X';

    int my_score = calculate_score(current_symbol);
    int opponent_score = calculate_score(opponent_symbol);

    if (my_score == opponent_score) {
        cout << "\n=== FINAL SCORES ===" << endl;
        cout << player->get_name() << " (" << current_symbol << "): " << my_score << " points" << endl;
        cout << "Opponent: " << opponent_score << " points" << endl;
        cout << "It's a DRAW!" << endl;
        cout << "===================" << endl;
        return true;
    }
    return false;
}

bool TTC5_Board::game_is_over(Player<char>* player) {
    return n_moves >= 24;
}

bool TTC5_Board::is_winner() {
    return false;
}

bool TTC5_Board::is_draw() {
    return n_moves >= 24;
}

bool TTC5_Board::game_is_over() {
    return n_moves >= 24;
}

bool TTC5_Board::check_three_in_row(char symbol) const {
    return calculate_score(symbol) > 0;
}
void TTC5_Board::display_scores() {
    int scoreX = calculate_score('X');
    int scoreO = calculate_score('O');

    cout << "\n=== FINAL SCORES ===" << endl;
    cout << "Player X: " << scoreX << " points" << endl;
    cout << "Player O: " << scoreO << " points" << endl;

    if (scoreX > scoreO) {
        cout << "Player X WINS!" << endl;
    }
    else if (scoreO > scoreX) {
        cout << "Player O WINS!" << endl;
    }
    else {
        cout << "It's a DRAW!" << endl;
    }
    cout << "===================" << endl;
}

void TTC5_Board::undo_move(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    if (x >= 0 && x < 5 && y >= 0 && y < 5) {
        board[x][y] = ' ';
        n_moves--;
    }
}

vector<Move<char>*> TTC5_Board::get_available_moves() {
    vector<Move<char>*> moves;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == ' ') {
                moves.push_back(new Move<char>(i, j, ' '));
            }
        }
    }
    return moves;
}
vector<pair<int, int>> TTC5_Board::get_empty_cells() const {
    vector<pair<int, int>> cells;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == ' ')
                cells.push_back({ i,j });
        }
    }
    return cells;
}
char TTC5_Board::get_cell(int x, int y) const {
    if (x >= 0 && x < 5 && y >= 0 && y < 5) {
        return board[x][y];
    }
    return ' ';
}
bool TTC5_Board::is_valid_move(int x, int y) const {
    return (x >= 0 && x < 5 && y >= 0 && y < 5 && board[x][y] == ' ');
}

bool TTC5_Board::is_full() const {
    return n_moves >= 24;
}
int TTC5_Board::evaluate_window(const vector<char>& window, char aiSymbol, char humanSymbol) const {
    int aiCount = 0, humanCount = 0, emptyCount = 0;

    for (char cell : window) {
        if (cell == aiSymbol) aiCount++;
        else if (cell == humanSymbol) humanCount++;
        else if (cell == ' ') emptyCount++;
    }

    if (aiCount == 3) return 100;
    if (aiCount == 2 && emptyCount == 1) return 10;
    if (aiCount == 1 && emptyCount == 2) return 1;
    if (humanCount == 3) return -100;
    if (humanCount == 2 && emptyCount == 1) return -10;
    if (humanCount == 1 && emptyCount == 2) return -1;

    return 0;
}


int TTC5_Board::minimax(int depth, bool isMaximizing, char aiSymbol, char humanSymbol,
    int alpha, int beta, int maxDepth) {
    if (depth >= maxDepth || is_full()) {
        return calculate_score(aiSymbol) - calculate_score(humanSymbol);
    }

    vector<pair<int, int>> emptyCells = get_empty_cells();

    if (isMaximizing) {
        int maxEval = INT_MIN;

        for (const auto& cell : emptyCells) {
            board[cell.first][cell.second] = aiSymbol;
            n_moves++;

            int eval = minimax(depth + 1, false, aiSymbol, humanSymbol,
                alpha, beta, maxDepth);

            board[cell.first][cell.second] = ' ';
            n_moves--;

            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);

            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        for (const auto& cell : emptyCells) {
            board[cell.first][cell.second] = humanSymbol;
            n_moves++;

            int eval = minimax(depth + 1, true, aiSymbol, humanSymbol,
                alpha, beta, maxDepth);

            board[cell.first][cell.second] = ' ';
            n_moves--;
            minEval = min(minEval, eval);
            beta = min(beta, eval);

            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}
pair<int, int> TTC5_Board::get_best_move(char aiSymbol, char humanSymbol, int difficulty) {
    vector<pair<int, int>> emptyCells = get_empty_cells();

    if (emptyCells.empty()) {
        return { -1, -1 };
    }
    if (emptyCells.size() == 25) {
        vector<pair<int, int>> centers = { {2, 2}, {1, 1}, {1, 3}, {3, 1}, {3, 3} };
        return centers[rand() % centers.size()];
    }
    int maxDepth;
    switch (difficulty) {
    case 1: maxDepth = 2; break;
    case 2: maxDepth = 3; break;
    case 3: maxDepth = 4; break;
    default: maxDepth = 3;
    }
    int bestScore = INT_MIN;
    pair<int, int> bestMove = emptyCells[0];

    for (const auto& cell : emptyCells) {
        board[cell.first][cell.second] = aiSymbol;
        n_moves++;

        int score = minimax(0, false, aiSymbol, humanSymbol,
            INT_MIN, INT_MAX, maxDepth);

        board[cell.first][cell.second] = ' ';
        n_moves--;
        if (score > bestScore) {
            bestScore = score;
            bestMove = cell;
        }
    }
    return bestMove;
}