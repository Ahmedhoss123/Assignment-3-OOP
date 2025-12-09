#ifndef FOUR_BY_FOUR_UI_H
#define FOUR_BY_FOUR_UI_H

#include "BoardGame_Classes.h"
#include "FourByFourMove.h"
#include "FourByFourBoard.h"
#include <vector>

class FourByFourUI : public UI<char> {
public:
    FourByFourUI();

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

private:
  
    struct Move4 {
        int sx, sy;
        int dx, dy;
    };

    Move<char>* get_computer_move(Player<char>* player);

    std::vector<Move4> generate_moves(const FourByFourBoard& boardState, char sym);

    int minimax(FourByFourBoard boardState,
        char aiSym, char oppSym,
        bool isAiTurn,
        int depth,
        int maxDepth);
};

#endif
