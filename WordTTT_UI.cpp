#include "WordTTT_UI.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

WordTTT_UI::WordTTT_UI() : UI("Welcome to Word Tic-Tac-Toe!", 3) {
    srand(time(0));
}
Move<char>* WordTTT_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        char letter;
        cout << player->get_name() << ", enter your move:\n";
        cout << "Row (0-2): "; cin >> x;
        cout << "Column (0-2): "; cin >> y;
        cout << "Letter: "; cin >> letter;
        letter = toupper(letter);
        return new Move<char>(x, y, letter);
    }
    else {
        Board<char>* gameBoard = player->get_board_ptr();
        vector<vector<char>> boardMatrix = gameBoard->get_board_matrix();

        int emptyCount = 0;
        int emptyCells[9][2];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (boardMatrix[i][j] == ' ') {
                    emptyCells[emptyCount][0] = i;
                    emptyCells[emptyCount][1] = j;
                    emptyCount++;
                }
            }
        }
        if (emptyCount == 0) {
            return nullptr;
        }
        int idx = rand() % emptyCount;
        int x = emptyCells[idx][0];
        int y = emptyCells[idx][1];
        char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char letter = letters[rand() % 26];
        cout << "Computer (" << player->get_name() << ") plays '"
            << letter << "' at (" << x << "," << y << ")\n";
        return new Move<char>(x, y, letter);
    }
}
Player<char>* WordTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Player<char>** WordTTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];

    string name1, name2;
    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);

    players[0] = new Player<char>(name1, 'A', PlayerType::HUMAN);
    char choice;
    cout << "Is Player 2 a computer? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        players[1] = new Player<char>("Computer", 'B', PlayerType::COMPUTER);
    }
    else {
        players[1] = new Player<char>(name2, 'B', PlayerType::HUMAN);
    }
    return players;
}
