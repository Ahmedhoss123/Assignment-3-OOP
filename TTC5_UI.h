#ifndef TTC5_UI_H
#define TTC5_UI_H

#include "BoardGame_Classes.h"

class TTC5_UI : public UI<char> {
public:
    TTC5_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

private:
    int get_coordinate(const string& prompt);
};

#endif