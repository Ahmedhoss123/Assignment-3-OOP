// MemoryTTT_Board.h
#ifndef MEMORYTTT_BOARD_H
#define MEMORYTTT_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

class MemoryTTT_Board : public Board<char> {
private:
    char blank_symbol;
    vector<vector<char>> visible_board;
    vector<vector<char>> secret_board;

public:
    MemoryTTT_Board();
    bool update_board(Move<char>* move) override;
    vector<vector<char>> get_board_matrix() const override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

#endif