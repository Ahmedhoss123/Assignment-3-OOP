#ifndef WORDTTT_SMARTAI_H
#define WORDTTT_SMARTAI_H

#include "BoardGame_Classes.h"
#include "WordTTT_Board.h"
#include <vector>
#include <unordered_set>

class WordTTT_SmartAI : public Player<char> {
private:
    unordered_set<string> dictionary;
    int maxDepth;

    int evaluate_board(WordTTT_Board& board);
    int minimax(WordTTT_Board& board, int depth, bool isMaximizing,
        int alpha, int beta, char aiSymbol, char humanSymbol);

public:
    WordTTT_SmartAI(string name, char symbol, int depth = 3);
    ~WordTTT_SmartAI();

    Move<char>* get_best_move(Board<char>* gameBoard);
};
#endif