#pragma once
#include "../globals.h"
#include "../movelist.cpp"
#include "../state.cpp"

void generate_queen_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wQUEEN];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            attacks = get_queen_attacks(source, state.position.sides[BOTH]) & !state.position.sides[WHITE];

            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[BLACK].get_bit(target))
                    move_list.add_move(Move(source, target, wQUEEN, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, wQUEEN, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
    else
    {
        board = state.position.pieces[bQUEEN];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            attacks = get_queen_attacks(source, state.position.sides[BOTH]) & !state.position.sides[BLACK];

            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[WHITE].get_bit(target))
                    move_list.add_move(Move(source, target, bQUEEN, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, bQUEEN, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
}