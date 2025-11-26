#ifndef TTC5_BOARD_H
#define TTC5_BOARD_H

#include "BoardGame_Classes.h"

class TTC5_Board : public Board<char> {
public:
    TTC5_Board();
    bool update_board(int x, int y, char symbol);
    void display_board();
    void display_scores();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

private:
    int calculate_score(char symbol);
    bool check_three_in_row(char symbol);
};

#endif