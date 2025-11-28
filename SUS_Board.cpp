#include "SUS_Classes.h"
#include <iostream>
using namespace std;

SUS_Board::SUS_Board() : Board<char>(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    player1_score = player2_score = 0;
    current_player = 1;
    n_moves = 0;
}

int SUS_Board::count_new_sus_created(int x, int y, char symbol) {
    if (symbol != 'S') return 0;

    int created = 0;
    auto check = [&](int r1, int c1, int r2, int c2, int r3, int c3) {
        return board[r1][c1] == 'S' && board[r2][c2] == 'U' && board[r3][c3] == 'S';
        };

    if (check(x, 0, x, 1, x, 2)) created++;        // row
    if (check(0, y, 1, y, 2, y)) created++;        // column
    if (x == y && check(0, 0, 1, 1, 2, 2)) created++; // main diag
    if (x + y == 2 && check(0, 2, 1, 1, 2, 0)) created++; // anti diag

    return created;
}

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != '.' || (sym != 'S' && sym != 'U')) {
        cout << "Invalid move!\n";
        return false;
    }

    board[x][y] = sym;
    n_moves++;

    int pts = count_new_sus_created(x, y, sym);
    if (current_player == 1) player1_score += pts;
    else                   player2_score += pts;

    current_player = 3 - current_player;
    return true;
}

bool SUS_Board::is_win(Player<char>* p) {
    if (n_moves != 9) return false;
    return (p->get_symbol() == 'S' &&
        ((current_player == 1 ? player2_score : player1_score) >
            (current_player == 1 ? player1_score : player2_score)));
}

bool SUS_Board::is_draw(Player<char>*) {
    return n_moves == 9 && player1_score == player2_score;
}

bool SUS_Board::game_is_over(Player<char>*) {
    return n_moves == 9;
}