#include "WordTTT_SmartAI.h"
#include <fstream>
#include <algorithm>
#include <climits>
#include <iostream>
#include <ctime>
using namespace std;
WordTTT_SmartAI::WordTTT_SmartAI(string name, char symbol, int depth)
    : Player(name, symbol, PlayerType::AI), maxDepth(depth) {
    srand(time(0));
    ifstream file("dic.txt");
    string word;

    if (file.is_open()) {
        while (file >> word) {
            if (word.length() == 3) {
                for (char& c : word) {
                    c = toupper(c);
                }
                dictionary.insert(word);
            }
        }
        file.close();
        cout << "Dictionary loaded with " << dictionary.size() << " words.\n";
    }
    else {
        cout << "Warning: dic.txt not found. Using default dictionary.\n";
        string defaultWords[] = { "CAT", "DOG", "SUN", "CAR", "BED", "EGG",
                                "ICE", "JOB", "MAN", "PEN", "BAT", "FOX",
                                "HAT", "JAM", "KEY", "LOG", "MAP", "NET",
                                "OWL", "PIG", "RAT", "SEA", "TEA", "USE",
                                "VAN", "WAX", "YES", "ZOO" };
        for (const string& w : defaultWords) {
            dictionary.insert(w);
        }
    }
}
WordTTT_SmartAI::~WordTTT_SmartAI() {
}
int WordTTT_SmartAI::evaluate_board(WordTTT_Board& board) {
    if (board.is_win(nullptr)) {
        return 1000;
    }
    int score = 0;
    vector<vector<char>> matrix = board.get_board_matrix();
    if (matrix[1][1] != ' ') {
        if (matrix[1][1] == get_symbol()) {
            score += 50;
        }
        else {
            score -= 50;
        }
    }
    int corners[4][2] = { {0,0}, {0,2}, {2,0}, {2,2} };
    for (auto& corner : corners) {
        int i = corner[0];
        int j = corner[1];
        if (matrix[i][j] != ' ') {
            if (matrix[i][j] == get_symbol()) {
                score += 20;
            }
            else {
                score -= 20;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        string row = "";
        row += matrix[i][0];
        row += matrix[i][1];
        row += matrix[i][2];

        int emptyCount = 0;
        int aiCount = 0;
        int opponentCount = 0;

        for (char c : row) {
            if (c == ' ') emptyCount++;
            else if (c == get_symbol()) aiCount++;
            else opponentCount++;
        }

        if (emptyCount == 1) {
            for (char c = 'A'; c <= 'Z'; c++) {
                string testWord = row;
                if (testWord[0] == ' ') testWord[0] = c;
                else if (testWord[1] == ' ') testWord[1] = c;
                else if (testWord[2] == ' ') testWord[2] = c;

                if (dictionary.find(testWord) != dictionary.end()) {
                    if (aiCount == 2) {
                        score += 100;
                    }
                    else if (opponentCount == 2) {
                        score -= 200;
                    }
                }
            }
        }
    }
    for (int j = 0; j < 3; j++) {
        string col = "";
        col += matrix[0][j];
        col += matrix[1][j];
        col += matrix[2][j];

        int emptyCount = 0;
        int aiCount = 0;
        int opponentCount = 0;

        for (char c : col) {
            if (c == ' ') emptyCount++;
            else if (c == get_symbol()) aiCount++;
            else opponentCount++;
        }
        if (emptyCount == 1) {
            for (char c = 'A'; c <= 'Z'; c++) {
                string testWord = col;
                if (testWord[0] == ' ') testWord[0] = c;
                else if (testWord[1] == ' ') testWord[1] = c;
                else if (testWord[2] == ' ') testWord[2] = c;

                if (dictionary.find(testWord) != dictionary.end()) {
                    if (aiCount == 2) {
                        score += 100;
                    }
                    else if (opponentCount == 2) {
                        score -= 200;
                    }
                }
            }
        }
    }
    string diag1 = "";
    diag1 += matrix[0][0];
    diag1 += matrix[1][1];
    diag1 += matrix[2][2];

    string diag2 = "";
    diag2 += matrix[0][2];
    diag2 += matrix[1][1];
    diag2 += matrix[2][0];

    string diagonals[2] = { diag1, diag2 };

    for (string& diag : diagonals) {
        int emptyCount = 0;
        int aiCount = 0;
        int opponentCount = 0;

        for (char c : diag) {
            if (c == ' ') emptyCount++;
            else if (c == get_symbol()) aiCount++;
            else opponentCount++;
        }

        if (emptyCount == 1) {
            for (char c = 'A'; c <= 'Z'; c++) {
                string testWord = diag;
                if (testWord[0] == ' ') testWord[0] = c;
                else if (testWord[1] == ' ') testWord[1] = c;
                else if (testWord[2] == ' ') testWord[2] = c;

                if (dictionary.find(testWord) != dictionary.end()) {
                    if (aiCount == 2) {
                        score += 100;
                    }
                    else if (opponentCount == 2) {
                        score -= 200;
                    }
                }
            }
        }
    }
    return score;
}
int WordTTT_SmartAI::minimax(WordTTT_Board& board, int depth, bool isMaximizing,
    int alpha, int beta, char aiSymbol, char humanSymbol) {
    if (depth == 0 || board.game_is_over(nullptr)) {
        return evaluate_board(board);
    }

    if (isMaximizing) {
        int maxEval = INT_MIN;
        vector<Move<char>*> moves = board.get_available_moves();
        if (moves.size() > 10 && depth < maxDepth - 1) {
            random_shuffle(moves.begin(), moves.end());
            moves.resize(10);
        }

        for (Move<char>* move : moves) {
            board.update_board(move);

            int eval = minimax(board, depth - 1, false, alpha, beta, aiSymbol, humanSymbol);
            maxEval = max(maxEval, eval);
            board.undo_move(move);
            alpha = max(alpha, eval);
            if (beta <= alpha) {
                delete move;
                break;
            }
            delete move;
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        vector<Move<char>*> moves = board.get_available_moves();
        if (moves.size() > 10 && depth < maxDepth - 1) {
            random_shuffle(moves.begin(), moves.end());
            moves.resize(10);
        }
        for (Move<char>* move : moves) {
            board.update_board(move);

            int eval = minimax(board, depth - 1, true, alpha, beta, aiSymbol, humanSymbol);
            minEval = min(minEval, eval);
            board.undo_move(move);
            beta = min(beta, eval);
            if (beta <= alpha) {
                delete move;
                break;
            }
            delete move;
        }
        return minEval;
    }
}
Move<char>* WordTTT_SmartAI::get_best_move(Board<char>* gameBoard) {
    WordTTT_Board* board = dynamic_cast<WordTTT_Board*>(gameBoard);
    if (!board) {
        cout << "Error: Invalid board type!\n";
        return nullptr;
    }

    cout << "\nAI is thinking";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        clock_t start = clock();
        while (clock() - start < 200);
    }
    cout << "\n";
    vector<Move<char>*> moves = board->get_available_moves();
    if (moves.empty()) {
        cout << "No moves available!\n";
        return nullptr;
    }
    Move<char>* bestMove = nullptr;
    int bestValue = INT_MIN;
    if (moves.size() > 100) {
        random_shuffle(moves.begin(), moves.end());
        int sampleSize = min(20, (int)moves.size());

        for (int i = 0; i < sampleSize; i++) {
            Move<char>* move = moves[i];
            board->update_board(move);
            int moveValue = evaluate_board(*board);
            board->undo_move(move);

            if (moveValue > bestValue) {
                bestValue = moveValue;
                if (bestMove) delete bestMove;
                bestMove = new Move<char>(*move);
            }
        }
    }
    else {
        for (Move<char>* move : moves) {
            board->update_board(move);

            int moveValue = minimax(*board, maxDepth - 1, false,
                INT_MIN, INT_MAX, get_symbol(), 'H');
            board->undo_move(move);

            if (moveValue > bestValue) {
                bestValue = moveValue;
                if (bestMove) delete bestMove;
                bestMove = new Move<char>(*move);
            }
            delete move;
        }
    }
    if (bestMove) {
        cout << "AI chooses: '" << bestMove->get_symbol()
            << "' at (" << bestMove->get_x() << "," << bestMove->get_y() << ")\n";
    }
    return bestMove;
}