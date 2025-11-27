#include "ObstaclesBoard.h"

ObstaclesBoard::ObstaclesBoard() : Board<char>(6,6) {
    srand(time(0));
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
            board[i][j] = '.';
}

bool ObstaclesBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if(board[x][y] != '.') return false;

    board[x][y] = s;
    n_moves++;

    // بعد كل دورين نضيف عوائق
    if(n_moves % 2 == 0)
        add_obstacles();

    return true;
}

void ObstaclesBoard::add_obstacles() {
    int added = 0;
    while(added < 2) {
        int r = rand() % 6;
        int c = rand() % 6;
        if(board[r][c] == '.') {
            board[r][c] = '#';
            added++;
        }
    }
}

bool ObstaclesBoard::is_win(Player<char>* p) {
    char s = p->get_symbol();

    // أفقي
    for(int r=0;r<6;r++)
        for(int c=0;c<=2;c++)
            if(board[r][c]==s && board[r][c+1]==s &&
               board[r][c+2]==s && board[r][c+3]==s) return true;

    // رأسي
    for(int c=0;c<6;c++)
        for(int r=0;r<=2;r++)
            if(board[r][c]==s && board[r+1][c]==s &&
               board[r+2][c]==s && board[r+3][c]==s) return true;

    
    for(int r=0;r<=2;r++)
        for(int c=0;c<=2;c++)
            if(board[r][c]==s && board[r+1][c+1]==s &&
               board[r+2][c+2]==s && board[r+3][c+3]==s) return true;
        for(int r=0;r<=2;r++)
        for(int c=3;c<6;c++)
            if(board[r][c]==s && board[r+1][c-1]==s &&
               board[r+2][c-2]==s && board[r+3][c-3]==s) return true;

    return false;
}

bool ObstaclesBoard::is_lose(Player<char>*) { return false; }

bool ObstaclesBoard::is_draw(Player<char>*) {
    return n_moves >= 36;
}

bool ObstaclesBoard::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}
