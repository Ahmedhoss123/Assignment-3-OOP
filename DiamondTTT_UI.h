#ifndef DIAMONDTTT_UI_H
#define DIAMONDTTT_UI_H

#include "BoardGame_Classes.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>

class DiamondTTT_UI : public UI<char> {
public:
    DiamondTTT_UI();
    virtual ~DiamondTTT_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

#endif
