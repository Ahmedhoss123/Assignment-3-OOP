#include "ObstaclesUI.h"

ObstaclesUI::ObstaclesUI() : UI<char>("Obstacles Tic Tac Toe", 3) {}

Move<char>* ObstaclesUI::get_move(Player<char>* player) {
    int x,y;
    cout << player->get_name() << " enter position (row col): ";
    cin >> x >> y;
    return new Move<char>(x,y,player->get_symbol());
}

Player<char>* ObstaclesUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
