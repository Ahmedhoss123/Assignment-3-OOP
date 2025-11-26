#ifndef WORDTTT_UI_H
#define WORDTTT_UI_H

#include "BoardGame_Classes.h"

class WordTTT_UI : public UI<char> {
public:
    WordTTT_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    Player<char>** setup_players() override;
};

#endif
