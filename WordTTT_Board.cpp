#include "WordTTT_Board.h"
#include <iostream>
#include <cctype>
#include <algorithm>
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
				word[0] = toupper(word[0]);
				word[1] = toupper(word[1]);
                word[2] = toupper(word[2]);
				dictionary.insert(word);
            }
        }
        file.close();
    }
    else {
        cout << "Warning: dic.txt not found. Using default words.\n";
		string defaultWords[] = { "CAT","DOG","SUN","CAR","BED","EGG","ICE","JOB","MAN","PEN" };
        for (int i = 0; i < 10; i++) {
            dictionary.insert(defaultWords[i]);
        }
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
    for (int i = 0; i < 3; i++) {
        seq = board[i][0] + board[i][1] + board[i][2];
        if (is_valid_word(seq)) { cout << "Word formed: " << seq << " - "; return true; }
    }
    for (int j = 0; j < 3; j++) {
        seq = board[0][j] + board[1][j] + board[2][j];
        if (is_valid_word(seq)) { cout << "Word formed: " << seq << " - "; return true; }
    }
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

vector<Move<char>*> WordTTT_Board::get_available_moves() {
    vector<Move<char>*> moves;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                for (char letter = 'A'; letter <= 'Z'; letter++) {
                    moves.push_back(new Move<char>(i, j, letter));
                }
            }
        }
    }
    return moves;
}
WordTTT_Board* WordTTT_Board::clone() const {
    WordTTT_Board* newBoard = new WordTTT_Board();
    newBoard->n_moves = this->n_moves;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            newBoard->board[i][j] = this->board[i][j];
    newBoard->dictionary = this->dictionary;
    return newBoard;
}
void WordTTT_Board::undo_move(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        board[x][y] = ' ';
        n_moves--;
    }
}
int WordTTT_Board::evaluate_position() {
    if (is_win(nullptr)) {
        return 1000;
    }
    if (is_lose(nullptr)) {
        return -1000;
    }
    int score = 0;
    if (board[1][1] != ' ') {
        score += 10;
    }
    if (board[0][0] != ' ') score += 5;
    if (board[0][2] != ' ') score += 5;
    if (board[2][0] != ' ') score += 5;
    if (board[2][2] != ' ') score += 5;
    for (int i = 0; i < 3; i++) {
        string row = "";
        row += board[i][0];
        row += board[i][1];
        row += board[i][2];
        if (row[0] != ' ' && row[1] != ' ' && row[2] == ' ') {
            for (char c = 'A'; c <= 'Z'; c++) {
                row[2] = c;
                if (is_valid_word(row)) score += 20;
            }
        }
    }
    return score;
}
