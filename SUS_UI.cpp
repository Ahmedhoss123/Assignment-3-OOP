#include "SUS_Classes.h"
#include <iostream>
using namespace std;

SUS_UI::SUS_UI() : UI<char>("=== FCAI SUS Game ===", 3) {}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    cout << "Enter Player 1 name: ";
    string name1;
    getline(cin >> ws, name1);

    cout << "Choose Player 1 type:\n1. Human\n2. Computer\n";
    int choice1;
    cin >> choice1;
    PlayerType type1 = (choice1 == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;

    cout << "Enter Player 2 name: ";
    string name2;
    getline(cin >> ws, name2);

    cout << "Choose Player 2 type:\n1. Human\n2. Computer\n";
    int choice2;
    cin >> choice2;
    PlayerType type2 = (choice2 == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;

    // Use 'S' as dummy symbol - actual symbol chosen per move
    players[0] = create_player(name1, 'S', type1);
    players[1] = create_player(name2, 'S', type2);

    return players;
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    int x, y;
    char letter;

    cout << player->get_name() << " -> Enter row col letter (S or U): ";
    cin >> x >> y >> letter;

    // Handle input failure
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return new Move<char>(-1, -1, '?');  // Return invalid move
    }

    // Convert to uppercase
    letter = toupper(letter);

    return new Move<char>(x, y, letter);
}