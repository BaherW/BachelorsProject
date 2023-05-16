#pragma once
#include "globals.h"
#include "move.cpp"

class MoveList
{
public:
    Move moves[MAX_MOVES];
    int num_moves;

    MoveList()
    {
        num_moves = 0;
    }

    void add_move(Move new_move)
    {
        moves[num_moves] = new_move;
        num_moves += 1;
    }

    void print()
    {
        for (int i = 0; i < num_moves; i++)
        {
            moves[i].print();
        }
    }
};