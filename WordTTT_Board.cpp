#include "WordTTT_Board.h"
#include <iostream>
#include <cctype>
using namespace std;

WordTTT_Board::WordTTT_Board() : Board(3, 3) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';

    load_dictionary();
}

void WordTTT_Board::load_dictionary() {
    ifstream file("dic.txt");
    string word;

    if (file.is_open()) {
        while (file >> word) {
            if (word.length() == 3) {
                for (char& c : word) c = toupper(c);
                dictionary.push_back(word);
            }
        }
        file.close();
    }
    else {
        cout << "Warning: dic.txt not found. Using default words.\n";
        dictionary = { "CAT","DOG","SUN","CAR","BED","EGG","ICE","JOB","MAN","PEN" };
    }
}

bool WordTTT_Board::is_valid_word(const string& word) {
    for (const auto& w : dictionary)
        if (w == word) return true;
    return false;
}

bool WordTTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') return false;
    if (symbol == ' ') return false;

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool WordTTT_Board::is_win(Player<char>* player) {
    string seq;
    // صفوف
    for (int i = 0; i < 3; i++) {
        seq = board[i][0] + board[i][1] + board[i][2];
        if (is_valid_word(seq)) { cout << "Word formed: " << seq << " - "; return true; }
    }
    // أعمدة
    for (int j = 0; j < 3; j++) {
        seq = board[0][j] + board[1][j] + board[2][j];
        if (is_valid_word(seq)) { cout << "Word formed: " << seq << " - "; return true; }
    }
    // قطرين
    seq = board[0][0] + board[1][1] + board[2][2];
    if (is_valid_word(seq)) { cout << "Word formed: " << seq << " - "; return true; }

    seq = board[0][2] + board[1][1] + board[2][0];
    if (is_valid_word(seq)) { cout << "Word formed: " << seq << " - "; return true; }

    return false;
}

bool WordTTT_Board::is_lose(Player<char>* player) {
    return game_is_over(player) && !is_win(player);
}

bool WordTTT_Board::is_draw(Player<char>* player) {
    return n_moves >= 9 && !is_win(player);
}

bool WordTTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || n_moves >= 9;
}
