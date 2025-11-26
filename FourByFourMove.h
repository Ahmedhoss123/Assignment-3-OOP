#ifndef FOUR_BY_FOUR_MOVE_H
#define FOUR_BY_FOUR_MOVE_H

#include "BoardGame_Classes.h"

template <typename T>
class FourByFourMove : public Move<T> {
    int dst_x, dst_y;

public:
    FourByFourMove(int src_x, int src_y, int dx, int dy, T sym)
        : Move<T>(src_x, src_y, sym), dst_x(dx), dst_y(dy) {}

    int get_dst_x() const { return dst_x; }
    int get_dst_y() const { return dst_y; }
};

#endif
