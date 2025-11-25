#include "DiamondTTT_Board.h"

DiamondTTT_Board::DiamondTTT_Board()
    : Board<char>(5, 5)
{
    board = std::vector<std::vector<char>>(5, std::vector<char>(5, '#'));
    n_moves = 0;

    board[0][2] = ' ';
    board[1][1] = board[1][2] = board[1][3] = ' ';
    board[2][0] = board[2][1] = board[2][2] = board[2][3] = board[2][4] = ' ';
    board[3][1] = board[3][2] = board[3][3] = ' ';
    board[4][2] = ' ';
}

bool DiamondTTT_Board::is_valid_cell(int r, int c) const {
    return (r >= 0 && r < rows && c >= 0 && c < columns && board[r][c] != '#');
}

bool DiamondTTT_Board::update_board(Move<char>* move) {
    if (!move) return false;
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (!is_valid_cell(x, y) || board[x][y] != ' ') return false;

    board[x][y] = sym;
    ++n_moves;
    return true;
}

std::vector<std::pair<int, std::vector<std::pair<int, int>>>> DiamondTTT_Board::collect_segments(int len, char sym) const {
    std::vector<std::pair<int, std::vector<std::pair<int, int>>>> segments;
    const std::vector<std::pair<int, int>> dirs = { {1,0}, {0,1}, {1,1}, {-1,1} };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (!is_valid_cell(r, c) || board[r][c] != sym) continue;
            for (int d = 0; d < (int)dirs.size(); ++d) {
                int dr = dirs[d].first, dc = dirs[d].second;
                std::vector<std::pair<int, int>> coords;
                coords.push_back({ r,c });
                bool ok = true;
                for (int k = 1; k < len; ++k) {
                    int nr = r + dr * k, nc = c + dc * k;
                    if (!is_valid_cell(nr, nc) || board[nr][nc] != sym) { ok = false; break; }
                    coords.push_back({ nr,nc });
                }
                if (ok && (int)coords.size() == len) {
                    int pr = r - dr, pc = c - dc;
                    if (pr >= 0 && pr < rows && pc >= 0 && pc < columns && is_valid_cell(pr, pc) && board[pr][pc] == sym)
                        continue;
                    segments.push_back({ d, coords });
                }
            }
        }
    }
    return segments;
}

bool DiamondTTT_Board::segments_form_valid_win(
    const std::vector<std::pair<int, std::vector<std::pair<int, int>>>>& seg3,
    const std::vector<std::pair<int, std::vector<std::pair<int, int>>>>& seg4) const
{
    for (auto& s3 : seg3) {
        for (auto& s4 : seg4) {
            if (s3.first == s4.first) continue;
            int inter = 0;
            for (auto& a : s3.second)
                for (auto& b : s4.second)
                    if (a.first == b.first && a.second == b.second) ++inter;
            if (inter <= 1) return true;
        }
    }
    return false;
}

bool DiamondTTT_Board::is_win(Player<char>* p) {
    if (!p) return false;
    char sym = p->get_symbol();
    auto seg3 = collect_segments(3, sym);
    auto seg4 = collect_segments(4, sym);
    if (seg3.empty() || seg4.empty()) return false;
    return segments_form_valid_win(seg3, seg4);
}

bool DiamondTTT_Board::is_lose(Player<char>* /*p*/) { return false; }

bool DiamondTTT_Board::is_draw(Player<char>* /*p*/) {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            if (is_valid_cell(r, c) && board[r][c] == ' ') return false;
    return true;
}

bool DiamondTTT_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}
