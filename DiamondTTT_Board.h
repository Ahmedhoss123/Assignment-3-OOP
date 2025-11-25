#ifndef DIAMONDTTT_BOARD_H
#define DIAMONDTTT_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>

class DiamondTTT_Board : public Board<char> {
public:
    DiamondTTT_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
    bool is_valid_cell(int r, int c) const;

private:
    std::vector<std::pair<int, std::vector<std::pair<int, int>>>> collect_segments(int len, char sym) const;
    bool segments_form_valid_win(const std::vector<std::pair<int, std::vector<std::pair<int, int>>>>& seg3,
        const std::vector<std::pair<int, std::vector<std::pair<int, int>>>>& seg4) const;
};

#endif
