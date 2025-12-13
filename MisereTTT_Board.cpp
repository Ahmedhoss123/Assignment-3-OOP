#include "MisereTTT_Board.h"
#include <iostream>

using namespace std;

MisereTTT_Board::MisereTTT_Board() : Board<char>(3, 3) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = ' ';
    n_moves = 0;
}

bool MisereTTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }
    if (board[x][y] != ' ') {
        return false;
    }

    board[x][y] = sym;
    n_moves++;
    return true;
}

// In Misere, if you get 3 in a row, you LOSE. 
// So is_win returns false (unless we defined a winning condition for the opponent, 
// but the GameManager checks is_lose).
bool MisereTTT_Board::is_win(Player<char>* p) {
    return false;
}

// Check if given player has 3-in-row -> that player loses
bool MisereTTT_Board::is_lose(Player<char>* p) {
    return player_has_three(p->get_symbol());
}

bool MisereTTT_Board::is_draw(Player<char>* p) {
    // Draw if board is full and nobody has lost (which implies nobody has won)
    return (n_moves >= rows * columns && !is_lose(p));
}

bool MisereTTT_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}

bool MisereTTT_Board::player_has_three(char sym) {
    // rows
    for (int i = 0; i < rows; ++i)
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym) return true;
    // cols
    for (int j = 0; j < columns; ++j)
        if (board[0][j] == sym && board[1][j] == sym && board[2][j] == sym) return true;
    // diags
    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) return true;
    return false;
}
