#ifndef NUMTTT_CLASSES_H
#define NUMTTT_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class NumTTT_Board
 * @brief Specialized board for Numerical Tic-Tac-Toe game (sum = 15).
 */
class NumTTT_Board : public Board<int> {
private:
    int blank_symbol = 0;

public:
    NumTTT_Board();
    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* player) override { return false; }
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
};

/**
 * @class NumTTT_UI
 * @brief User interface for the Numerical Tic-Tac-Toe.
 */
class NumTTT_UI : public UI<int> {
public:
    NumTTT_UI();
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;
    Move<int>* get_move(Player<int>* player) override;
};

#endif // NUMTTT_CLASSES_H
