#pragma once
#include "Player.h"
#include "FourByFourBoard.h"
#include "FourByFourMove.h"

class AIPlayer : public Player<char> {
public:
    AIPlayer(char symbol);
    Move<char>* get_move(Board<char>* b) override;

private:
    int minimax(FourByFourBoard* board, int depth, bool isMax);
};
