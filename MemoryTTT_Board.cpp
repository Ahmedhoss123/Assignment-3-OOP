#include "MemoryTTT_Board.h"
#include <iostream>
#include <cctype>
using namespace std;

MemoryTTT_Board::MemoryTTT_Board() : Board(3, 3) {
	blank_symbol = '.';
	visible_board.assign(rows, vector<char>(columns, blank_symbol));
    secret_board.assign(rows, vector<char>(columns, blank_symbol));
	n_moves = 0;
}

bool MemoryTTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = toupper(move->get_symbol());

    // Validate move and apply if valid
    if (x < 0 || x >= rows || y < 0 || y >= columns || secret_board[x][y] != blank_symbol)
        return false;

	secret_board[x][y] = mark;
    n_moves++;
	return true;
}

vector<vector<char>> MemoryTTT_Board::get_board_matrix() const {
    return visible_board;
}

bool MemoryTTT_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((secret_board[i][0] == sym && secret_board[i][1] == sym && secret_board[i][2] == sym) || 
            (secret_board[0][i] == sym && secret_board[1][i] == sym && secret_board[2][i] == sym))
            return true;
    }

    // Check diagonals
    if ((secret_board[0][0] == sym && secret_board[1][1] == sym && secret_board[2][2] == sym) || 
        (secret_board[0][2] == sym && secret_board[1][1] == sym && secret_board[2][0] == sym))
        return true;

    return false;
}

bool MemoryTTT_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool MemoryTTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
