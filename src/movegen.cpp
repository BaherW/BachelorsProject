#pragma once
#include "globals.h"
#include "movelist.cpp"
#include "state.cpp"
#include "attacks/pawn.cpp"
#include "attacks/knight.cpp"
#include "attacks/bishop.cpp"
#include "attacks/rook.cpp"
#include "attacks/queen.cpp"
#include "attacks/king.cpp"

void generate_moves(MoveList &move_list, State &state)
{
    int current_color = state.current_color;

    generate_pawn_moves(current_color, move_list, state);
    generate_knight_moves(current_color, move_list, state);
    generate_bishop_moves(current_color, move_list, state);
    generate_rook_moves(current_color, move_list, state);
    generate_queen_moves(current_color, move_list, state);
    generate_king_moves(current_color, move_list, state);
}