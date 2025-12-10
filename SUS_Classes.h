#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

class SUS_Board : public Board<char> {
private:
    int player1_score = 0;
    int player2_score = 0;  // Fixed: removed extra '='
    int current_player = 1;

    int count_new_sus_created(int x, int y, char symbol);

public:
    static constexpr char blank_symbol = '.';

    SUS_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    int get_player1_score() const { return player1_score; }
    int get_player2_score() const { return player2_score; }

    // Add getter for board access in UI
    char get_cell(int x, int y) const { return board[x][y]; }

    int& get_n_moves_ref() { return n_moves; }

	int get_current_player() const { return current_player; }
};

class SUS_UI : public UI<char> {
public:
    SUS_UI();
    ~SUS_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;

    // Display board using getter instead of direct access
    void display_board(Board<char>* b) {
        SUS_Board* board = dynamic_cast<SUS_Board*>(b);
        if (!board) return;

        cout << "\n   0   1   2\n";
        for (int i = 0; i < 3; ++i) {
            cout << i << "  ";
            for (int j = 0; j < 3; ++j) {
                char cell = board->get_cell(i, j);  // Use getter method
                cout << (cell == '.' ? '.' : cell);
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "   --------- \n";
        }
        cout << "\nScore -> Player 1: " << board->get_player1_score()
            << " | Player 2: " << board->get_player2_score() << "\n\n";
    }
};

class SUS_AI_Player : public Player<char> {
public:
    SUS_AI_Player(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::AI) {}

    // This is the ONLY function the AI uses
    Move<char>* make_perfect_move(SUS_Board* board);
};

#endif
