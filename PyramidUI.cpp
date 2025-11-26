#include "PyramidUI.h"

PyramidUI::PyramidUI() : UI<char>("Pyramid Tic Tac Toe", 3) {}

Move<char>* PyramidUI::get_move(Player<char>* player) {
    int x,y;
    cout << player->get_name() << " enter cell (row col): ";
    cin >> x >> y;
    return new Move<char>(x,y,player->get_symbol());
}

Player<char>* PyramidUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
