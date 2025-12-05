#ifndef MISERETTT_UI_H
#define MISERETTT_UI_H

#include "BoardGame_Classes.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>

class MisereTTT_UI : public UI<char> {
public:
    MisereTTT_UI()
        : UI<char>("Welcome to Mis¨¨re Tic-Tac-Toe (avoid making 3-in-a-row)!", 1) {
        srand((unsigned)time(nullptr));
    }

    virtual ~MisereTTT_UI() {}
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }
    Move<char>* get_move(Player<char>* player) override {

        if (player->get_type() == PlayerType::HUMAN) {
            int x, y;
            while (true) {
                cout << player->get_name() << " (" << player->get_symbol()
                    << ") - Enter row and column (e.g., 0 2): ";

                if ((cin >> x >> y) && !cin.fail()) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                else {
                    cout << "Invalid input. Enter two integers.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            return new Move<char>(x, y, player->get_symbol());
        }

        Board<char>* bptr = player->get_board_ptr();
        if (!bptr) {
            return new Move<char>(0, 0, player->get_symbol());
        }

        vector<vector<char>> mat = bptr->get_board_matrix();

        char aiSym = player->get_symbol();
        char oppSym = (aiSym == 'X' ? 'O' : 'X');

        int bestScore = -1000;
        int bestR = -1, bestC = -1;
        for (int i = 0; i < (int)mat.size(); ++i) {
            for (int j = 0; j < (int)mat[i].size(); ++j) {

                if (mat[i][j] == ' ' || mat[i][j] == '-') {
                    char backup = mat[i][j];
                    mat[i][j] = aiSym;

                    int score = minimax_rec(mat, aiSym, oppSym, false);

                    mat[i][j] = backup;

                    if (score > bestScore) {
                        bestScore = score;
                        bestR = i;
                        bestC = j;
                    }
                }
            }
        }

        if (bestR == -1 || bestC == -1) {
            for (int i = 0; i < (int)mat.size(); ++i) {
                for (int j = 0; j < (int)mat[i].size(); ++j) {
                    if (mat[i][j] == ' ' || mat[i][j] == '-') {
                        bestR = i;
                        bestC = j;
                        break;
                    }
                }
                if (bestR != -1) break;
            }

            if (bestR == -1) {

                return new Move<char>(-1, -1, aiSym);
            }
        }

        cout << player->get_name() << " (" << player->get_symbol()
            << ") chooses: " << bestR << " " << bestC << "\n";

        return new Move<char>(bestR, bestC, aiSym);
    }


    Player<char>** setup_players() override {

        Player<char>** players = new Player<char>*[2];

        string nameX;
        cout << "Enter Player X name: ";
        cin >> nameX;

        int choiceX;
        cout << "1. Human\n2. Computer\nChoose type for Player X: ";
        cin >> choiceX;

        PlayerType typeX = (choiceX == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN);
        players[0] = new Player<char>(nameX, 'X', typeX);

        string nameO;
        cout << "Enter Player O name: ";
        cin >> nameO;

        int choiceO;
        cout << "1. Human\n2. Computer\nChoose type for Player O: ";
        cin >> choiceO;

        PlayerType typeO = (choiceO == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN);
        players[1] = new Player<char>(nameO, 'O', typeO);

        return players;
    }

private:
    bool has_three(const vector<vector<char>>& mat, char sym) {
        // rows
        for (int i = 0; i < 3; ++i)
            if (mat[i][0] == sym && mat[i][1] == sym && mat[i][2] == sym)
                return true;
        // cols
        for (int j = 0; j < 3; ++j)
            if (mat[0][j] == sym && mat[1][j] == sym && mat[2][j] == sym)
                return true;
        // diags
        if (mat[0][0] == sym && mat[1][1] == sym && mat[2][2] == sym)
            return true;
        if (mat[0][2] == sym && mat[1][1] == sym && mat[2][0] == sym)
            return true;
        return false;
    }
int evaluate_position(const vector<vector<char>>& mat, char aiSym, char oppSym) {
        if (has_three(mat, aiSym))  return -1;  
        if (has_three(mat, oppSym)) return 1;   

        bool full = true;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (mat[i][j] == ' ' || mat[i][j] == '-') {
                    full = false;
                    break;
                }
            }
            if (!full) break;
        }

        if (full) return 0;  
        return 2;            
    }

    int minimax_rec(vector<vector<char>>& mat,
        char aiSym, char oppSym,
        bool isAiTurn) {

        int eval = evaluate_position(mat, aiSym, oppSym);
        if (eval != 2)  
            return eval;

        if (isAiTurn) {
            int best = -1000;

            for (int i = 0; i < (int)mat.size(); ++i) {
                for (int j = 0; j < (int)mat[i].size(); ++j) {
                    if (mat[i][j] == ' ' || mat[i][j] == '-') {
                        char backup = mat[i][j];
                        mat[i][j] = aiSym;

                        int score = minimax_rec(mat, aiSym, oppSym, false);

                        mat[i][j] = backup;
                        if (score > best) best = score;
                    }
                }
            }
            return best;
        }
        else {
            int best = 1000;

            for (int i = 0; i < (int)mat.size(); ++i) {
                for (int j = 0; j < (int)mat[i].size(); ++j) {
                    if (mat[i][j] == ' ' || mat[i][j] == '-') {
                        char backup = mat[i][j];
                        mat[i][j] = oppSym;

                        int score = minimax_rec(mat, aiSym, oppSym, true);

                        mat[i][j] = backup;
                        if (score < best) best = score;
                    }
                }
            }
            return best;
        }
    }
};

#endif 
