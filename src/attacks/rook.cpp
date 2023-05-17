#pragma once
#include "../globals.h"
#include "../movelist.cpp"
#include "../state.cpp"

BitBoard rook_attacks_mask(int square, BitBoard blockers = empty_board, int edges = 0)
{
    BitBoard attacks = BitBoard();
    BitBoard mask;
    int row, file;
    int max, min;

    if (edges == 0)
        max = 6, min = 1;
    else
        max = 7, min = 0;

    for (row = (square / 8) + 1; row <= max; ++row)
    {
        mask = BitBoard(1) << (row * 8 + (square % 8));
        attacks |= mask;
        if (mask & blockers)
            break;
    }

    for (row = (square / 8) - 1; row >= min; --row)
    {
        mask = BitBoard(1) << (row * 8 + (square % 8));
        attacks |= mask;
        if (mask & blockers)
            break;
    }

    for (file = (square % 8) + 1; file <= max; ++file)
    {
        mask = BitBoard(1) << ((square / 8) * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
    }

    for (file = (square % 8) - 1; file >= min; --file)
    {
        mask = BitBoard(1) << ((square / 8) * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
    }

    return attacks;
}

void generate_rook_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wROOK];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            attacks = get_rook_attacks(source, state.position.sides[BOTH]) & !state.position.sides[WHITE];

            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[BLACK].get_bit(target))
                    move_list.add_move(Move(source, target, wROOK, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, wROOK, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
    else
    {
        board = state.position.pieces[bROOK];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            attacks = get_rook_attacks(source, state.position.sides[BOTH]) & !state.position.sides[BLACK];

            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[WHITE].get_bit(target))
                    move_list.add_move(Move(source, target, bROOK, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, bROOK, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
}