#ifndef FOUR_BY_FOUR_UI_H
#define FOUR_BY_FOUR_UI_H

#include "BoardGame_Classes.h"
#include "FourByFourMove.h"

class FourByFourUI : public UI<char> {
public:
    FourByFourUI();

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif
