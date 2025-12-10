#ifndef XO4R_CLASSES_H
#define XO4R_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class XO4R_Board
 * @brief Specialized board for Numerical Tic-Tac-Toe game (sum = 15).
 */

class XO4R_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    XO4R_Board();
    bool update_board(Move<char>* move) ;
    bool is_win(Player<char>* player) ;
    bool is_lose(Player<char>* player) { return false; }
    bool is_draw(Player<char>* player) ;
    bool game_is_over(Player<char>* player) ;
    int& get_n_moves_ref() { return n_moves; }
    pair<int, int> drop_in_column(int col, char sym);
};

/**
 * @class XO4R_UI
 * @brief User interface for the Numerical Tic-Tac-Toe.
 */

class XO4R_UI : public UI<char> {
public:
    XO4R_UI();
    ~XO4R_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

class XO4R_AI_Player : public Player<char> {
public:
    XO4R_AI_Player(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::AI) {}

    // This is the ONLY function the AI uses
    Move<char>* make_perfect_move(XO4R_Board* board);
};

#endif // XO4R_CLASSES_H
