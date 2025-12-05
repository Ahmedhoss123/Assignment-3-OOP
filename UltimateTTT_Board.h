#ifndef ULTIMATETTT_BOARD_H
#define ULTIMATETTT_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>

class UltimateTTT_Board : public Board<char> {
public:
    UltimateTTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

private:
    char mainBoard[3][3]; 
    bool small_board_win(int br, int bc, char sym) const;
    bool small_board_full(int br, int bc) const;
    bool main_board_win(char sym) const;
    bool all_small_boards_finished() const;
};

#endif