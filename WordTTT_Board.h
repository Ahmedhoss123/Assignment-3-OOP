#ifndef WORDTTT_BOARD_H
#define WORDTTT_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>

class WordTTT_Board : public Board<char> {
private:
    unordered_set<string> dictionary;

    void load_dictionary();
    bool is_valid_word(const std::string& word);

public:
    WordTTT_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

	vector<Move<char>*> get_available_moves();
	WordTTT_Board* clone() const;
    int evaluate_position();
	void undo_move(Move<char>* move);
};

#endif
