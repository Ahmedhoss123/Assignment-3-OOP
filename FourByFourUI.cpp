#include "FourByFourUI.h"

FourByFourUI::FourByFourUI() : UI<char>("4x4 Moving Tic Tac Toe", 3) {}

Move<char>* FourByFourUI::get_move(Player<char>* player) {
    int sx, sy, dx, dy;
    cout << player->get_name() << " enter src(x y) then dst(x y): ";
    cin >> sx >> sy >> dx >> dy;
    return new FourByFourMove<char>(sx, sy, dx, dy, player->get_symbol());
}

Player<char>* FourByFourUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
