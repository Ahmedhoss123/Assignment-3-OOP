#pragma once
#include "BoardGame_Classes.h"
#include "FourByFourBoard.h"
#include "FourByFourMove.h"

class AIPlayer : public Player<char> {
public:
    AIPlayer(string name, char symbol);
    Move<char>* get_move(Board<char>* b);

private:
    int minimax(FourByFourBoard* board, int depth, bool isMax);
};
