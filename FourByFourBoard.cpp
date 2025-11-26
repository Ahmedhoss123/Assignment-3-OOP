#include "FourByFourBoard.h"

FourByFourBoard::FourByFourBoard() : Board<char>(4,4) {
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            board[i][j] = '.';

    for(int j=0;j<4;j++) board[0][j] = 'X';
    for(int j=0;j<4;j++) board[3][j] = 'O';
}

bool FourByFourBoard::update_board(Move<char>* move) {
    auto m = dynamic_cast<FourByFourMove<char>*>(move);
    if(!m) return false;

    int sx = m->get_x(), sy = m->get_y();
    int dx = m->get_dst_x(), dy = m->get_dst_y();
    char sym = m->get_symbol();

    if(board[sx][sy] != sym) return false;
    if(board[dx][dy] != '.') return false;

    int dr = abs(sx-dx), dc = abs(sy-dy);
    if(!((dr==1 && dc==0) || (dr==0 && dc==1))) return false;

    board[sx][sy] = '.';
    board[dx][dy] = sym;
    n_moves++;
    return true;
}

bool FourByFourBoard::is_win(Player<char>* p) {
    char s = p->get_symbol();

    for(int r=0;r<4;r++)
        for(int c=0;c<=1;c++)
            if(board[r][c]==s && board[r][c+1]==s && board[r][c+2]==s) return true;

    for(int c=0;c<4;c++)
        for(int r=0;r<=1;r++)
            if(board[r][c]==s && board[r+1][c]==s && board[r+2][c]==s) return true;

    for(int r=0;r<=1;r++)
        for(int c=0;c<=1;c++)
            if(board[r][c]==s && board[r+1][c+1]==s && board[r+2][c+2]==s) return true;

    for(int r=0;r<=1;r++)
        for(int c=2;c<4;c++)
            if(board[r][c]==s && board[r+1][c-1]==s && board[r+2][c-2]==s) return true;

    return false;
}

bool FourByFourBoard::is_lose(Player<char>*) { return false; }
bool FourByFourBoard::is_draw(Player<char>*) { return n_moves > 60; }
bool FourByFourBoard::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}
