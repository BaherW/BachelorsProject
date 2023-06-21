#pragma once

#include "globals.h"

class Position
{
public:
    BitBoard pieces[12];
    BitBoard sides[3];

    Position();
    Position(string fen);

    void combine_boards();

    bool is_square_attacked(int square, int color);

    void print();
    void print_attacked_squares(int color);

private:
    void init_boards();
    void read_fen(string fen);
    void set_position(string fen);

    bool is_white_attacking(int square);
    bool is_black_attacking(int square);
};
