#include "PyramidBoard.h"

PyramidBoard::PyramidBoard() : Board<char>(3,5) {
    for(int i=0;i<3;i++)
        for(int j=0;j<5;j++)
            board[i][j] = ' ';

    board[0][0] = '.';
    board[1][0] = board[1][1] = board[1][2] = '.';
    for(int j=0;j<5;j++) board[2][j] = '.';
}

bool PyramidBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 5) return false;
    if(board[x][y] != '.') return false;

    board[x][y] = s;
    n_moves++;
    return true;
}

bool PyramidBoard::is_win(Player<char>* p) {
    char s = p->get_symbol();

    // أفقي (الصف الأخير فقط)
    for(int j=0;j<=2;j++)
        if(board[2][j]==s && board[2][j+1]==s && board[2][j+2]==s)
            return true;

    // عمودي
    if(board[0][0]==s && board[1][0]==s && board[2][0]==s) return true;

    // قطري
    if(board[2][0]==s && board[1][1]==s && board[0][0]==s) return true;
    if(board[2][4]==s && board[1][2]==s && board[0][0]==s) return true;

    return false;
}

bool PyramidBoard::is_lose(Player<char>*) {
    return false;
}

bool PyramidBoard::is_draw(Player<char>*) {
    return n_moves == 9;
}

bool PyramidBoard::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

   // AI (Minimax + Backtracking)
   

void PyramidBoard::undo_move(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    board[x][y] = '.';
    n_moves--;
}

char PyramidBoard::get_cell(int r, int c) const {
    return board[r][c];
}
