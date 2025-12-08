#ifndef TTC5_BOARD_H
#define TTC5_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>

class TTC5_Board : public Board<char> {
public:
    TTC5_Board();
    bool update_board(int x, int y, char symbol);
    void display_board();
    void display_scores();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    void undo_move(Move<char>* move);
    int get_score(char symbol) const;
    vector<pair<int, int>> get_empty_cells() const;
    char get_cell(int x, int y) const;
    void set_cell(int x, int y, char symbol);
    bool is_full() const;
    int calculate_score(char symbol) const;
    bool is_valid_move(int x, int y) const;
    pair<int, int> get_best_move(char aiSymbol, char humanSymbol, int difficulty = 2);

private:
    bool check_three_in_row(char symbol) const;
    int evaluate_window(const vector<char>& window, char aiSymbol, char humanSymbol) const;
    int minimax(int depth, bool isMaximizing, char aiSymbol, char humanSymbol,int alpha, int beta, int maxDepth);
    vector<Move<char>*> get_available_moves();
};

#endif