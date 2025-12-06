#ifndef PYRAMID_BOARD_H
#define PYRAMID_BOARD_H

#include "BoardGame_Classes.h"

class PyramidBoard : public Board<char> {
public:
    PyramidBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    //  AI
    void undo_move(Move<char>* move);
    char get_cell(int r, int c) const;
};

#endif
