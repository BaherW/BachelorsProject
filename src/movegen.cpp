#include "../headers/movegen.h"

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