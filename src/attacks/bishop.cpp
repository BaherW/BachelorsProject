#pragma once
#include "../globals.h"
#include "../movelist.cpp"
#include "../state.cpp"

BitBoard bishop_attacks_mask(int square, BitBoard blockers = empty_board, int edges = 0)
{
    BitBoard attacks = BitBoard();
    BitBoard mask;
    int row, file;
    int max, min;

    if (edges == 0)
        max = 6, min = 1;
    else
        max = 7, min = 0;

    int original_square = square / 8;
    int original_file = square % 8;

    row = original_square + 1;
    file = original_file + 1;
    while (row <= max && file <= max)
    {
        mask = BitBoard(1) << (row * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
        row++, file++;
    }

    row = original_square - 1;
    file = original_file + 1;
    while (row >= min && file <= max)
    {
        mask = BitBoard(1) << (row * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
        row--, file++;
    }

    row = original_square + 1;
    file = original_file - 1;
    while (row <= max && file >= min)
    {
        mask = BitBoard(1) << (row * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
        row++, file--;
    }

    row = original_square - 1;
    file = original_file - 1;
    while (row >= min && file >= min)
    {
        mask = BitBoard(1) << (row * 8 + file);
        attacks |= mask;
        if (mask & blockers)
            break;
        row--, file--;
    }

    return attacks;
}

void generate_bishop_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wBISHOP];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            attacks = get_bishop_attacks(source, state.position.sides[BOTH]) & !state.position.sides[WHITE];

            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[BLACK].get_bit(target))
                    move_list.add_move(Move(source, target, wBISHOP, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, wBISHOP, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
    else
    {
        board = state.position.pieces[bBISHOP];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            attacks = get_bishop_attacks(source, state.position.sides[BOTH]) & !state.position.sides[BLACK];

            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[WHITE].get_bit(target))
                    move_list.add_move(Move(source, target, bBISHOP, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, bBISHOP, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
}