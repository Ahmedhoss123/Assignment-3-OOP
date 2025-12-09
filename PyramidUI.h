#ifndef PYRAMID_UI_H
#define PYRAMID_UI_H

#include "BoardGame_Classes.h"
#include "PyramidBoard.h"

class PyramidUI : public UI<char> {
public:
    PyramidUI();

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

private:
    struct Cell { int r, c; };

    Move<char>* get_computer_move(Player<char>* player);
    std::vector<Cell> generate_moves(const PyramidBoard& board);
    int minimax(PyramidBoard boardState,
        char aiSym, char oppSym,
        bool isAiTurn,
        int depth,
        int maxDepth);
};

#endif
