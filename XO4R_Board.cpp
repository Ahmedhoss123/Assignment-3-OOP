#include "XO4R_Classes.h"
#include <iostream>
#include "BoardGame_Classes.h"
#include <algorithm>
#include <vector>
using namespace std;

int col;

XO4R_Board::XO4R_Board() : Board(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool XO4R_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char mark = move->get_symbol();

	col = c;

    // Validate move and apply if valid
    if ((r >= 0 && r < rows && c >= 0 && c < columns) &&
        (board[r][c] == blank_symbol || mark == 0)) {

        if (mark == 0 && r != 5) { // Undo move
            n_moves--;
            board[r][c] = blank_symbol;
        }
        else if (r == 5 || (r + 1 < rows && board[r + 1][c] != blank_symbol)) {         // Apply move
            n_moves++;
            board[r][c] = toupper(mark);
        } 
        return true;
    }
    return false;
}

bool check_win_static(const vector<vector<char>>& b, char sym) {
    int rows = 6;
    int cols = 7;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols - 3; c++) {
            if (b[r][c] == sym && b[r][c + 1] == sym && b[r][c + 2] == sym && b[r][c + 3] == sym)
                return true;
        }
    }

    for (int r = 0; r < rows - 3; r++) {
        for (int c = 0; c < cols; c++) {
            if (b[r][c] == sym && b[r + 1][c] == sym && b[r + 2][c] == sym && b[r + 3][c] == sym)
                return true;
        }
    }

    for (int r = 0; r < rows - 3; r++) {
        for (int c = 0; c < cols - 3; c++) {
            if (b[r][c] == sym && b[r + 1][c + 1] == sym && b[r + 2][c + 2] == sym && b[r + 3][c + 3] == sym)
                return true;
        }
    }

    for (int r = 3; r < rows; r++) {
        for (int c = 0; c < cols - 3; c++) {
            if (b[r][c] == sym && b[r - 1][c + 1] == sym && b[r - 2][c + 2] == sym && b[r - 3][c + 3] == sym)
                return true;
        }
    }
    return false;
}

bool XO4R_Board::is_win(Player<char>* player) {
    return check_win_static(this->board, player->get_symbol());
}

bool XO4R_Board::is_draw(Player<char>* player) {
    return (n_moves == 42 && !is_win(player));
}

bool XO4R_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// ================================================
//       Perfect Minimax AI with Backtracking 
// ================================================

int evaluate_window(const vector<char>& window, char piece) {
    int score = 0;
	char opp_piece = (piece == 'X') ? 'O' : 'X';
    int count_piece = 0;
    int count_empty = 0;
    int count_opp = 0;

    for (char cell : window) {
        if (cell == piece) count_piece++;
        else if (cell == opp_piece) count_opp++;
        else if (cell == '.') count_empty++;
	}

	if (count_piece == 4) score += 100;
    else if (count_piece == 3 && count_empty == 1) score += 5;
    else if (count_piece == 2 && count_empty == 2) score += 2;
    if (count_opp == 3 && count_empty == 1) score -= 4;

    return score;
}

int score_position(const vector<vector<char>>& b, char piece) {
	int score = 0;
    int rows = 6;
    int cols = 7;

	vector<char> center_array;
	for (int r = 0; r < rows; r++)
        center_array.push_back(b[r][3]);

    int center_count = 0;
    for (char c : center_array)
		if (c == piece) center_count++;

	score += center_count * 3;

	for (int r = 0; r < rows; r++) {
		vector<char> row_array = b[r];
        for (int c = 0; c < cols - 3; c++) {
            vector<char> window;
			for (int i = 0; i < 4; i++)
                window.push_back(row_array[c + i]);
			score += evaluate_window(window, piece);
        }
    }

    for (int c = 0; c < cols; c++) {
        vector<char> col_array;
        for (int r = 0; r < rows; r++)
            col_array.push_back(b[r][c]);
        for (int r = 0; r < rows - 3; r++) {
            vector<char> window;
            for (int i = 0; i < 4; i++)
                window.push_back(col_array[r + i]);
            score += evaluate_window(window, piece);
		}
    }

    for (int r = 0; r < rows - 3; r++) {
        for (int c = 0; c < cols - 3; c++) {
            vector<char> window;
            for (int i = 0; i < 4; i++)
                window.push_back(b[r + i][c + i]);
            score += evaluate_window(window, piece);
        }
	}
	for (int r = 0; r < rows - 3; r++) {
        for (int c = 0; c < cols - 3; c++) {
            vector<char> window;
            for (int i = 0; i < 4; i++)
                window.push_back(b[r + 3 - i][c + i]);
            score += evaluate_window(window, piece);
        }
    }

    return score;
}

int get_next_open_row(const vector<vector<char>>& b, int col) {
    for (int r = 5; r >= 0; --r) {
        if (b[r][col] == '.') return r;
    }
    return -1;
}

bool is_terminal_node(const vector<vector<char>>& b) {
    return check_win_static(b, 'X') || check_win_static(b, 'O');
}

int minimax(vector<vector<char>>& b, int depth, int alpha, int beta, bool maximizingPlayer, char aiSym) {
	char oppSym = (aiSym == 'X') ? 'O' : 'X';

	if (check_win_static(b, aiSym))
        return 1000000;
    else if (check_win_static(b, oppSym))
        return -1000000;

	bool full = true;
    for (int c = 0; c < 7; ++c) {
        if (b[0][c] == '.') {
            full = false;
        };
    };

    if (full)
		return 0;

    if (depth == 0) {
        return score_position(b, aiSym);
    };

    if (maximizingPlayer) {
        int value = -2147483648;
		int colOrder[] = { 3, 2, 4, 1, 5, 0, 6 };

        for (int c : colOrder) {
            int r = get_next_open_row(b, c);
            if (r == -1) continue;

			b[r][c] = aiSym;
            int new_score = minimax(b, depth - 1, alpha, beta, false, aiSym);
            b[r][c] = '.';

            value = max(value, new_score);
            alpha = max(alpha, value);
            if (alpha >= beta)
				break;
        }
		return value;
    }
    else {
		int value = 2147483647;
        int colOrder[] = { 3, 2, 4, 1, 5, 0, 6 };

        for (int c : colOrder) {
            int r = get_next_open_row(b, c);
            if (r == -1) continue;

			b[r][c] = oppSym;
            int new_score = minimax(b, depth - 1, alpha, beta, true, aiSym);
            b[r][c] = '.';

            value = min(value, new_score);
            beta = min(beta, value);
            if (alpha >= beta) break;
        }
		return value;
    }
}

Move<char>* XO4R_AI_Player::make_perfect_move(XO4R_Board* real_board) {
    auto b = real_board->get_board_matrix();
    char aiSym = this->get_symbol();

    int bestScore = -2147483648;
    int bestCol = -1;
    int bestRow = -1;

    int depth = 6;

	int colOrder[] = { 3, 2, 4, 1, 5, 0, 6 };

    for (int c : colOrder) {
        int r = get_next_open_row(b, c);
		if (r == -1) continue;

		b[r][c] = aiSym;
        int score = minimax(b, depth - 1, -2147483648, 2147483647, false, aiSym);
		b[r][c] = '.';

		if (score > bestScore) {
            bestScore = score;
            bestCol = c;
            bestRow = r;
        }
    }

    if (bestCol == -1) {
        for (int c = 0; c < 7; c++) {
            if (b[0][c] == '.') {
                bestCol = c;
                bestRow = get_next_open_row(b, c);
                break;
            }
        }
    }

    cout << "\nAI drops in column: " << bestCol << endl;
	return new Move<char>(bestRow, bestCol, aiSym);
}
