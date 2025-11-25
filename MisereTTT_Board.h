#ifndef MISERETTT_BOARD_H
#define MISERETTT_BOARD_H

#include "BoardGame_Classes.h"

// Mis¨¨re Tic-Tac-Toe board (3x3)
class MisereTTT_Board : public Board<char> {
public:
    MisereTTT_Board() : Board<char>(3, 3) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i][j] = ' ';
        n_moves = 0;
    }

    virtual ~MisereTTT_Board() {}

    // Update only if inside bounds and empty
    bool update_board(Move<char>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        char sym = move->get_symbol();

        if (x < 0 || x >= rows || y < 0 || y >= columns) {
            cout << "Invalid position. Try again.\n";
            return false;
        }
        if (board[x][y] != ' ') {
            cout << "Cell already occupied. Try again.\n";
            return false;
        }

        board[x][y] = sym;
        ++n_moves;
        return true;
    }

    // Under mis¨¨re rules, making 3-in-row is a LOSS; so is_win returns false for the mover
    bool is_win(Player<char>* /*p*/) override {
        return false;
    }

    // Check if given player has 3-in-row -> that player loses
    bool is_lose(Player<char>* p) override {
        char sym = p->get_symbol();
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

    // Draw when board full and no player has 3-in-row
    bool is_draw(Player<char>* /*p*/) override {
        if (n_moves < rows * columns) return false;
        bool x_three = player_has_three('X');
        bool o_three = player_has_three('O');
        return !(x_three || o_three);
    }

    bool game_is_over(Player<char>* p) override {
        return is_win(p) || is_lose(p) || is_draw(p);
    }

private:
    bool player_has_three(char sym) {
        for (int i = 0; i < rows; ++i)
            if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym) return true;
        for (int j = 0; j < columns; ++j)
            if (board[0][j] == sym && board[1][j] == sym && board[2][j] == sym) return true;
        if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) return true;
        if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) return true;
        return false;
    }
};

#endif // MISERETTT_BOARD_H
