#include "FourByFourUI.h"
#include "AIPlayer.h"    

FourByFourUI::FourByFourUI() : UI<char>("4x4 Moving Tic Tac Toe", 3) {}

Move<char>* FourByFourUI::get_move(Player<char>* player) {

    // لو اللاعب ذكاء اصطناع هو اللي يحسب الحركة بنفسه
    if(player->get_type() == PlayerType::AI){
        return static_cast<AIPlayer*>(player)->get_move(player->get_board_ptr());
    }

    // لو لاعب عادي)
    int sx, sy, dx, dy;
    cout << player->get_name() << " enter src(x y) then dst(x y): ";
    cin >> sx >> sy >> dx >> dy;
    return new FourByFourMove<char>(sx, sy, dx, dy, player->get_symbol());
}


//  هنا بنحدد نوع اللاعب الحقيقي نسان أو AI
Player<char>* FourByFourUI::create_player(string& name, char symbol, PlayerType type) {

    if(type == PlayerType::AI){
        return new AIPlayer(name, symbol);
    }

    // افتراضي لاعب إنسان
    return new Player<char>(name, symbol, PlayerType::HUMAN);
}
