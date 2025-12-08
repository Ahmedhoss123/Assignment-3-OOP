#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "BoardGame_Classes.h"
#include "TTC5_Board.h"
#include <string>
#include <vector>

using namespace std;

class AIPlayer : public Player<char> {
private:
    char opponentSymbol;
    int difficulty;
    int evaluateMove(TTC5_Board& board, int x, int y);
    bool checkImmediateWin(TTC5_Board& board, char symbol);
    bool checkImmediateBlock(TTC5_Board& board);

public:
    AIPlayer(string name, char symbol, PlayerType type = PlayerType::AI);
    AIPlayer(char symbol, char opponent, int difficulty = 2, string name = "Smart AI");
    void get_move(TTC5_Board& board, int& x, int& y);
    void set_difficulty(int level);
    int get_difficulty() const { return difficulty; }
    string get_difficulty_string() const;
    pair<int, int> calculate_best_move(TTC5_Board& board);
};

#endif