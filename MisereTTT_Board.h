#ifndef MISERETTT_BOARD_H
#define MISERETTT_BOARD_H

#include "BoardGame_Classes.h"

// Misere Tic-Tac-Toe board (3x3)
class MisereTTT_Board : public Board<char> {
public:
    MisereTTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

private:
    bool player_has_three(char sym);
};

#endif // MISERETTT_BOARD_H
