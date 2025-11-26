#include "TTC5_Board.h"
#include <iostream>
using namespace std;

TTC5_Board::TTC5_Board() : Board(5, 5) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = ' ';
        }
    }
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

int TTC5_Board::calculate_score(char symbol) {
    int score = 0;

    // Check horizontal sequences
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == symbol &&
                board[i][j + 1] == symbol &&
                board[i][j + 2] == symbol) {
                score++;
            }
        }
    }

    // Check vertical sequences
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 3; i++) {
            if (board[i][j] == symbol &&
                board[i + 1][j] == symbol &&
                board[i + 2][j] == symbol) {
                score++;
            }
        }
    }

    // Check main diagonals
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == symbol &&
                board[i + 1][j + 1] == symbol &&
                board[i + 2][j + 2] == symbol) {
                score++;
            }
        }
    }

    // Check anti-diagonals
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
    return false; // Not used in this implementation
}

bool TTC5_Board::is_draw() {
    return n_moves >= 24;
}

bool TTC5_Board::game_is_over() {
    return n_moves >= 24;
}

bool TTC5_Board::check_three_in_row(char symbol) {
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