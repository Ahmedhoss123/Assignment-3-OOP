#include "MisereTTT_Classes.h"
#include <iostream>
using namespace std;

MisereTTT_Board::MisereTTT_Board() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '-';
}

void MisereTTT_Board::display_board() {
    cout << "\nMis¨¨re Tic Tac Toe (Avoid 3 in a row!)\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

bool MisereTTT_Board::update_board(int x, int y, char symbol) {
    if (x < 0 || x > 2 || y < 0 || y > 2) return false;
    if (board[x][y] != '-') return false;
    board[x][y] = symbol;
    return true;
}

bool MisereTTT_Board::is_full() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '-') return false;
    return true;
}

bool MisereTTT_Board::is_draw() {
    return is_full() && !is_winner();
}

// ===============================
// Mis¨¨re: Player LOSES if THEY get 3-in-row
// So if someone forms a line ¡ú they LOSE ¡ú return true
// ===============================
bool MisereTTT_Board::is_winner() {
    // Check rows
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '-')
            return true;

    // Check columns
    for (int j = 0; j < 3; j++)
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != '-')
            return true;

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-')
        return true;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-')
        return true;

    return false;  // No losing condition
}
