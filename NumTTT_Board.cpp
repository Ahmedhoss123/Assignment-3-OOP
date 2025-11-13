#include "NumTTT_Classes.h"
#include <iostream>
using namespace std;

NumTTT_Board::NumTTT_Board() : Board<int>(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool NumTTT_Board::update_board(Move<int>* move) {
    int r = move->get_x();
    int c = move->get_y();
    int val = move->get_symbol();

    if (r < 0 || r >= 3 || c < 0 || c >= 3)
        return false;
    if (board[r][c] != blank_symbol)
        return false;

    // Check that number isn't already used
    for (auto& row : board)
        for (auto cell : row)
            if (cell == val)
                return false;

    board[r][c] = val;
    n_moves++;
    return true;
}

bool NumTTT_Board::is_win(Player<int>* player) {
    // Check rows & cols
    for (int i = 0; i < 3; i++) {
        if (board[i][0] + board[i][1] + board[i][2] == 15 &&
            board[i][0] && board[i][1] && board[i][2])
            return true;
        if (board[0][i] + board[1][i] + board[2][i] == 15 &&
            board[0][i] && board[1][i] && board[2][i])
            return true;
    }
    // Diagonals
    if (board[0][0] + board[1][1] + board[2][2] == 15 &&
        board[0][0] && board[1][1] && board[2][2])
        return true;
    if (board[0][2] + board[1][1] + board[2][0] == 15 &&
        board[0][2] && board[1][1] && board[2][0])
        return true;

    return false;
}

bool NumTTT_Board::is_draw(Player<int>* player) {
    if (n_moves < 9)
        return false;
    return !is_win(player);
}

bool NumTTT_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}
