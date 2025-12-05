#include "UltimateTTT_Board.h"

UltimateTTT_Board::UltimateTTT_Board()
    : Board<char>(9, 9) {

  
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = ' ';

   
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            mainBoard[i][j] = ' ';

    n_moves = 0;
}


bool UltimateTTT_Board::small_board_win(int br, int bc, char sym) const {
    int rs = br * 3;
    int cs = bc * 3;

    for (int i = 0; i < 3; ++i) {
        if (board[rs + i][cs + 0] == sym &&
            board[rs + i][cs + 1] == sym &&
            board[rs + i][cs + 2] == sym)
            return true;
    }

    
    for (int j = 0; j < 3; ++j) {
        if (board[rs + 0][cs + j] == sym &&
            board[rs + 1][cs + j] == sym &&
            board[rs + 2][cs + j] == sym)
            return true;
    }

    
    if (board[rs + 0][cs + 0] == sym &&
        board[rs + 1][cs + 1] == sym &&
        board[rs + 2][cs + 2] == sym)
        return true;

    if (board[rs + 0][cs + 2] == sym &&
        board[rs + 1][cs + 1] == sym &&
        board[rs + 2][cs + 0] == sym)
        return true;

    return false;
}

bool UltimateTTT_Board::small_board_full(int br, int bc) const {
    int rs = br * 3;
    int cs = bc * 3;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[rs + i][cs + j] == ' ')
                return false;
    return true;
}


bool UltimateTTT_Board::main_board_win(char sym) const {
   
    for (int i = 0; i < 3; ++i)
        if (mainBoard[i][0] == sym &&
            mainBoard[i][1] == sym &&
            mainBoard[i][2] == sym)
            return true;

    for (int j = 0; j < 3; ++j)
        if (mainBoard[0][j] == sym &&
            mainBoard[1][j] == sym &&
            mainBoard[2][j] == sym)
            return true;

    if (mainBoard[0][0] == sym &&
        mainBoard[1][1] == sym &&
        mainBoard[2][2] == sym)
        return true;

    if (mainBoard[0][2] == sym &&
        mainBoard[1][1] == sym &&
        mainBoard[2][0] == sym)
        return true;

    return false;
}

bool UltimateTTT_Board::all_small_boards_finished() const {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (mainBoard[i][j] == ' ')
                return false;
    return true;
}



bool UltimateTTT_Board::update_board(Move<char>* move) {
    if (!move) return false;

    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    
    if (board[x][y] != ' ')
        return false;

    
    int br = x / 3;
    int bc = y / 3;
    if (mainBoard[br][bc] != ' ')
        return false;

  
    board[x][y] = sym;
    ++n_moves;

    if (small_board_win(br, bc, sym)) {
        mainBoard[br][bc] = sym;   
    }
    else if (small_board_full(br, bc) && mainBoard[br][bc] == ' ') {
        mainBoard[br][bc] = '-';       }

    return true;
}

bool UltimateTTT_Board::is_win(Player<char>* p) {
    if (!p) return false;
    char sym = p->get_symbol();
    return main_board_win(sym);
}

bool UltimateTTT_Board::is_lose(Player<char>* /*p*/) {
    
    return false;
}

bool UltimateTTT_Board::is_draw(Player<char>* /*p*/) {
    
    if (main_board_win('X') || main_board_win('O'))
        return false;

    if (all_small_boards_finished())
        return true;

    if (n_moves >= rows * columns)
        return true;

    return false;
}

bool UltimateTTT_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_lose(p) || is_draw(p);
}
