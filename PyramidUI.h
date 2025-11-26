#ifndef PYRAMID_UI_H
#define PYRAMID_UI_H

#include "BoardGame_Classes.h"

class PyramidUI : public UI<char> {
public:
    PyramidUI();

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif
