#include "WordTTT_UI.h"
#include <iostream>
#include <cctype>
using namespace std;

WordTTT_UI::WordTTT_UI() : UI("Welcome to Word Tic-Tac-Toe!", 3) {}

Move<char>* WordTTT_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        char letter;
        cout << player->get_name() << ", enter your move:\n";
        cout << "Row (0-2): "; cin >> x;
        cout << "Column (0-2): "; cin >> y;
        cout << "Letter: "; cin >> letter;
        //letter[0] = toupper(letter[0]);
        return new Move<char>(x, y, letter);
    }
    else {
        //int x, y;
        //string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        //Board<char>* board = player->get_board_ptr();
        //auto mat = board->get_board_matrix();
        //do {
        //    x = rand() % 3;
        //    y = rand() % 3;
        //} while (mat[x][y] != ' ');
        //char letter(1, letters[rand() % 26]);
        //cout << "Computer (" << player->get_name() << ") plays '" << letter << "' at (" << x << "," << y << ")\n";
        //return new Move<char>(x, y, letter);
    }
}

Player<char>* WordTTT_UI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Player<char>** WordTTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];

    string name1, name2;
    cout << "Enter Player 1 name: "; getline(cin >> ws, name1);
    cout << "Enter Player 2 name: "; getline(cin >> ws, name2);

    players[0] = new Player<char>(name1, 'A', PlayerType::HUMAN);
    players[1] = new Player<char>(name2, 'B', PlayerType::HUMAN);

    return players;
}
