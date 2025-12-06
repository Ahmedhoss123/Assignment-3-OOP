
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

    // Validate move and apply if valid
    if ((r >= 0 && r < rows && c >= 0 && c < columns) &&
        (board[r][c] == blank_symbol || mark == 0)) {

        if (mark == 0 && r != 5) { // Undo move
            n_moves--;
            board[r][c] = blank_symbol;
        }
        else if (r == 5 || (r + 1 < rows && board[r + 1][c] != blank_symbol)) {         // Apply move
            n_moves++;
            board[r][c] = toupper(mark);
        } 
        return true;
    }
    return false;
}

bool XO4R_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c, char d) {
        return a == b && b == c && c == d && a != blank_symbol;
    };

    // Check rows and columns
    for (int r = 0; r < rows; ++r) {

        if (col + 3 < columns) {
            if (all_equal(board[r][col], board[r][col + 1], board[r][col + 2], board[r][col + 3]) && board[r][col] == sym)
                return true;
		}

		if (col - 3 >= 0) {
            if (all_equal(board[r][col], board[r][col - 1], board[r][col - 2], board[r][col - 3]) && board[r][col] == sym)
                return true;
        }

		if (r + 3 < rows) {
            if (all_equal(board[r][col], board[r + 1][col], board[r + 2][col], board[r + 3][col]) && board[r][col] == sym)
                return true;
        }

		if (r - 3 >= 0) {
            if (all_equal(board[r][col], board[r - 1][col], board[r - 2][col], board[r - 3][col]) && board[r][col] == sym)
                return true;
        }

		if (r + 3 < rows && col + 3 < columns) {
            if (all_equal(board[r][col], board[r + 1][col + 1], board[r + 2][col + 2], board[r + 3][col + 3]) && board[r][col] == sym)
                return true;
        }

        if (r - 3 >= 0 && col - 3 >= 0) {
            if (all_equal(board[r][col], board[r - 1][col - 1], board[r - 2][col - 2], board[r - 3][col - 3]) && board[r][col] == sym)
                return true;
		}

        if (r + 3 < rows && col - 3 >= 0) {
            if (all_equal(board[r][col], board[r + 1][col - 1], board[r + 2][col - 2], board[r + 3][col - 3]) && board[r][col] == sym)
                return true;
        }
        if (r - 3 >= 0 && col + 3 < columns) {
            if (all_equal(board[r][col], board[r - 1][col + 1], board[r - 2][col + 2], board[r - 3][col + 3]) && board[r][col] == sym)
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
