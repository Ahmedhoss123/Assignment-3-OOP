#ifndef FOUR_BY_FOUR_BOARD_H
#define FOUR_BY_FOUR_BOARD_H

#include "BoardGame_Classes.h"
#include "FourByFourMove.h"

class FourByFourBoard : public Board<char> {
public:
    FourByFourBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

    void undo_move(FourByFourMove<char>* m);
    char get_cell(int r, int c) const;   

#endif
