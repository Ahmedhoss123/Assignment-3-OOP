#ifndef OBSTACLES_BOARD_H
#define OBSTACLES_BOARD_H

#include "BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>

class ObstaclesBoard : public Board<char> {
public:
    ObstaclesBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

private:
    void add_obstacles();
};

#endif
