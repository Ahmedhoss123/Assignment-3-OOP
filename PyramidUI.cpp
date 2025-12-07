#include "PyramidUI.h"
#include "PyramidMove.h"
#include "PyramidAI.h"
#include <iostream>
using namespace std;

PyramidUI::PyramidUI() : UI<char>("Pyramid Tic Tac Toe", 3) {}

Move<char>* PyramidUI::get_move(Player<char>* player) {

    
    if (player->get_type() == PlayerType::COMPUTER) {
        return player->get_move();
    }

   
    int x, y;
    cout << player->get_name() << " enter cell (row col): ";
    cin >> x >> y;

    return new PyramidMove<char>(x, y, player->get_symbol());
}

Player<char>* PyramidUI::create_player(string& name, char symbol, PlayerType type) {

   
    if (type == PlayerType::COMPUTER) {
        return new PyramidAI(name, symbol);
    }

    
    return new Player<char>(name, symbol, type);
}
