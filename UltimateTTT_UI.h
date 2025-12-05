#ifndef ULTIMATETTT_UI_H
#define ULTIMATETTT_UI_H

#include "BoardGame_Classes.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>


class UltimateTTT_UI : public UI<char> {
public:
    UltimateTTT_UI()
        : UI<char>("Ultimate Tic-Tac-Toe: 3x3 grid of 3x3 boards.", 3)
    {
        srand((unsigned)time(nullptr));
    }

    virtual ~UltimateTTT_UI() {}

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

#endif // ULTIMATETTT_UI_H
