#include "SUS_Classes.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

SUS_Board::SUS_Board() : Board<char>(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    player1_score = player2_score = 0;
    current_player = 1;
    n_moves = 0;
}

int SUS_Board::count_new_sus_created(int x, int y, char symbol) {
    int created = 0;

    auto is_char = [&](int r, int c, char target) {
        if (r < 0 || r > 2 || c < 0 || c > 2) return false;
		return board[r][c] == target;
    };

    if (symbol == 'S') {
		if (is_char(x, y - 1, 'U') && is_char(x, y - 2, 'S')) created++;
        if (is_char(x, y + 1, 'U') && is_char(x, y + 2, 'S')) created++;

        if (is_char(x - 1, y, 'U') && is_char(x - 2, y, 'S')) created++;
        if (is_char(x + 1, y, 'U') && is_char(x + 2, y, 'S')) created++;

        if (is_char(x - 1, y - 1, 'U') && is_char(x - 2, y - 2, 'S')) created++;
        if (is_char(x + 1, y + 1, 'U') && is_char(x + 2, y + 2, 'S')) created++;
        if (is_char(x - 1, y + 1, 'U') && is_char(x - 2, y + 2, 'S')) created++;
        if (is_char(x + 1, y - 1, 'U') && is_char(x + 2, y - 2, 'S')) created++;
    }
	else if (symbol == 'U') {
        if (is_char(x, y - 1, 'S') && is_char(x, y + 1, 'S')) created++;
        if (is_char(x - 1, y, 'S') && is_char(x + 1, y, 'S')) created++;
        if (is_char(x - 1, y - 1, 'S') && is_char(x + 1, y + 1, 'S')) created++;
        if (is_char(x - 1, y + 1, 'S') && is_char(x + 1, y - 1, 'S')) created++;
    }

    return created;
}

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != '.' || (sym != 'S' && sym != 'U')) {
        cout << "Invalid move!\n";
        return false;
    }

    board[x][y] = sym;
    n_moves++;

    int pts = count_new_sus_created(x, y, sym);
    if (current_player == 1) player1_score += pts;
    else                   player2_score += pts;

    current_player = 3 - current_player;
    return true;
}

bool SUS_Board::is_win(Player<char>* p) {
    if (n_moves != 9) return false;
    
	int my_score = (current_player == 1) ? player1_score : player2_score;

    return (p->get_symbol() == 'X')
        ? (player1_score > player2_score)
		: (player2_score > player1_score);
}

bool SUS_Board::is_draw(Player<char>*) {
    return n_moves == 9 && player1_score == player2_score;
}

bool SUS_Board::game_is_over(Player<char>*) {
    return n_moves == 9;
}

// ================================================
//       Perfect Minimax AI with Backtracking 
// ================================================

struct MiniState {
    char grid[3][3];
    int player1_score;
    int player2_score;
	int n_moves;
};

int calculate_utility(const MiniState& s, int ai_player_num) {
    if (ai_player_num == 1) return s.player1_score - s.player2_score;
	return s.player2_score - s.player1_score;
}

int count_points_on_grid(char grid[3][3], int r, int c, char sym) {
    int pts = 0;
    auto val = [&](int i, int j) {
		if (i < 0 || i > 2 || j < 0 || j > 2) return ' ';
		return grid[i][j];
    };

    if (sym == 'S') {
        if (val(r, c - 1) == 'U' && val(r, c - 2) == 'S') pts++;
        if (val(r, c + 1) == 'U' && val(r, c + 2) == 'S') pts++;
        if (val(r - 1, c) == 'U' && val(r - 2, c) == 'S') pts++;
        if (val(r + 1, c) == 'U' && val(r + 2, c) == 'S') pts++;
        if (val(r - 1, c - 1) == 'U' && val(r - 2, c - 2) == 'S') pts++;
        if (val(r + 1, c + 1) == 'U' && val(r + 2, c + 2) == 'S') pts++;
        if (val(r - 1, c + 1) == 'U' && val(r - 2, c + 2) == 'S') pts++;
        if (val(r + 1, c - 1) == 'U' && val(r + 2, c - 2) == 'S') pts++;
	}
    else if (sym == 'U') {
        if (val(r, c - 1) == 'S' && val(r, c + 1) == 'S') pts++;
        if (val(r - 1, c) == 'S' && val(r + 1, c) == 'S') pts++;
        if (val(r - 1, c - 1) == 'S' && val(r + 1, c + 1) == 'S') pts++;
        if (val(r - 1, c + 1) == 'S' && val(r + 1, c - 1) == 'S') pts++;
    }
	return pts;
}

int minimax_ab(MiniState& state, int depth, bool isMax, int alpha, int beta, int ai_player_num) {
	if (state.n_moves == 9) {
        return calculate_utility(state, ai_player_num);
    }

	int bestVal = isMax ? -9999 : 9999;
	char symbols[2] = { 'S', 'U' };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state.grid[i][j] == '.') {
                for (char sym : symbols) {
					state.grid[i][j] = sym;
					state.n_moves++;

					int pts = count_points_on_grid(state.grid, i, j, sym);

					int mover = (state.n_moves % 2 != 0) ? 1 : 2;

					if (mover == 1) state.player1_score += pts;
					else state.player2_score += pts;

					int val = minimax_ab(state, depth + 1, !isMax, alpha, beta, ai_player_num);
                    
					if (mover == 1) state.player1_score -= pts;
					else state.player2_score -= pts;
					state.n_moves--;
					state.grid[i][j] = '.';

                    if (isMax) {
                        bestVal = max(bestVal, val);
                        alpha = max(alpha, bestVal);
                    } else {
                        bestVal = min(bestVal, val);
                        beta = min(beta, bestVal);
					}
                    if (beta <= alpha) break;
                }
                if (beta <= alpha) break;
            }
        }
    }
    return bestVal;
}

Move<char>* SUS_AI_Player::make_perfect_move(SUS_Board* real_board) {
    MiniState state;
	vector<vector<char>> b = real_board->get_board_matrix();
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
			state.grid[i][j] = b[i][j];

    state.player1_score = real_board->get_player1_score();
	state.player2_score = real_board->get_player2_score();

    state.n_moves = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
			if (state.grid[i][j] != '.') state.n_moves++;

	int ai_p_num = (state.n_moves % 2 == 0) ? 1 : 2;

	int bestVal = -9999;
	int bestX = -1, bestY = -1;
    char bestSym = 'S';

	char symbols[2] = { 'S', 'U' };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state.grid[i][j] == '.') {
                for (char sym : symbols) {
					state.grid[i][j] = sym;
					state.n_moves++;

					int pts = count_points_on_grid(state.grid, i, j, sym);
					if (ai_p_num == 1) state.player1_score += pts;
					else state.player2_score += pts;

					int moveVal = minimax_ab(state, 0, false, -10000, 10000, ai_p_num);

					if (ai_p_num == 1) state.player1_score -= pts;
					else state.player2_score -= pts;
					state.n_moves--;
					state.grid[i][j] = '.';

					if (moveVal > bestVal) {
                        bestVal = moveVal;
                        bestX = i;
                        bestY = j;
                        bestSym = sym;
                    }
                }
            }
        }
    }

	return new Move<char>(bestX, bestY, bestSym);
}
