// MemoryTTT_UI.h
#ifndef MEMORYTTT_UI_H
#define MEMORYTTT_UI_H

#include "BoardGame_Classes.h"

class MemoryTTT_UI : public UI<char> {
public:
    MemoryTTT_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif