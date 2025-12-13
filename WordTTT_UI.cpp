#include "WordTTT_UI.h"
#include "WordTTT_SmartAI.h" // Include AI header
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

WordTTT_UI::WordTTT_UI() : UI("Welcome to Word Tic-Tac-Toe!", 3) {
    // FIXED: Static cast to avoid C4244 warning
    srand(static_cast<unsigned int>(time(0)));
}

Player<char>* WordTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER || type == PlayerType::AI) {
        return new WordTTT_SmartAI(name, symbol, 3);
    }
    return new Player<char>(name, symbol, type);
}

Move<char>* WordTTT_UI::get_move(Player<char>* player) {
    // Check for Smart AI
    WordTTT_SmartAI* aiPtr = dynamic_cast<WordTTT_SmartAI*>(player);
    if (aiPtr) {
        return aiPtr->get_best_move(player->get_board_ptr());
    }

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
        // Fallback Random
        Board<char>* gameBoard = player->get_board_ptr();
        vector<vector<char>> boardMatrix = gameBoard->get_board_matrix();
        // ... (Random logic as before)
        return nullptr;
    }
}

Player<char>** WordTTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];

    string name1, name2;
    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);

    players[0] = create_player(name1, 'A', PlayerType::HUMAN);
    char choice;
    cout << "Is Player 2 a computer? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        // Use create_player to ensure correct AI class instantiation
        string aiName = "Computer";
        players[1] = create_player(aiName, 'B', PlayerType::AI);
    }
    else {
        players[1] = create_player(name2, 'B', PlayerType::HUMAN);
    }
    return players;
}
