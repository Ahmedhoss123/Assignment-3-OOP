#include "XO4R_Classes.h"
#include <iostream>
#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

int col;

XO4R_Board::XO4R_Board() : Board(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool XO4R_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char mark = move->get_symbol();

    col = c;

    if ((r >= 0 && r < rows && c >= 0 && c < columns) &&
        (board[r][c] == blank_symbol || mark == 0)) {

        if (mark == 0 && r != 5) {
            n_moves--;
            board[r][c] = blank_symbol;
        }
        else if (r == 5 || (r + 1 < rows && board[r + 1][c] != blank_symbol)) {
            n_moves++;
            board[r][c] = toupper(mark);
        } 
        return true;
    }
    return false;
}

bool XO4R_Board::is_win(Player<char>* player) {
    return is_win_symbol(player->get_symbol());
}

/* ===================== NEW ===================== */

vector<int> XO4R_Board::get_valid_columns() {
    vector<int> valid_cols;
    for (int c = 0; c < columns; c++) {
        if (board[0][c] == blank_symbol)
            valid_cols.push_back(c);
    }
    return valid_cols;
}

int XO4R_Board::get_next_open_row(int col) {
    for (int r = rows - 1; r >= 0; r--) {
        if (board[r][col] == blank_symbol)
            return r;
    }
    return -1;
}

void XO4R_Board::apply_move(int col, char symbol) {
    int r = get_next_open_row(col);
    if (r != -1) {
        board[r][col] = symbol;
        n_moves++;
    }
}

void XO4R_Board::undo_move(int col) {
    for (int r = 0; r < rows; r++) {
        if (board[r][col] != blank_symbol) {
            board[r][col] = blank_symbol;
            n_moves--;
            break;
        }
    }
}

bool XO4R_Board::is_win_symbol(char sym) {

    auto all_equal = [&](char a, char b, char c, char d) {
        return a == b && b == c && c == d && a != blank_symbol;
    };

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {

            if (c + 3 < columns && all_equal(board[r][c], board[r][c + 1], board[r][c + 2], board[r][c + 3]) && board[r][c] == sym)
                return true;

            if (r + 3 < rows && all_equal(board[r][c], board[r + 1][c], board[r + 2][c], board[r + 3][c]) && board[r][c] == sym)
                return true;

            if (r + 3 < rows && c + 3 < columns && all_equal(board[r][c], board[r + 1][c + 1], board[r + 2][c + 2], board[r + 3][c + 3]) && board[r][c] == sym)
                return true;

            if (r + 3 < rows && c - 3 >= 0 && all_equal(board[r][c], board[r + 1][c - 1], board[r + 2][c - 2], board[r + 3][c - 3]) && board[r][c] == sym)
                return true;
        }
    }
    return false;
}

bool XO4R_Board::is_draw(Player<char>* player) {
    return (n_moves == 42 && !is_win(player));
}

bool XO4R_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
