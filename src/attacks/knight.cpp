#pragma once
#include "../globals.h"
#include "../movelist.cpp"
#include "../state.cpp"

BitBoard knight_attacks_mask(int square)
{
    BitBoard attacks = BitBoard();
    BitBoard board = BitBoard();

    board.set_bit(square);

    if (((board >> 17) & NOT_H_FILE) != empty_board)
        attacks |= board >> 17;

    if (((board >> 15) & NOT_A_FILE) != empty_board)
        attacks |= board >> 15;

    if (((board >> 10) & NOT_GH_FILE) != empty_board)
        attacks |= board >> 10;

    if (((board >> 6) & NOT_AB_FILE) != empty_board)
        attacks |= board >> 6;

    if (((board << 17) & NOT_A_FILE) != empty_board)
        attacks |= board << 17;

    if (((board << 15) & NOT_H_FILE) != empty_board)
        attacks |= board << 15;

    if (((board << 10) & NOT_AB_FILE) != empty_board)
        attacks |= board << 10;

    if (((board << 6) & NOT_GH_FILE) != empty_board)
        attacks |= board << 6;

    return attacks;
}

void init_knight_attacks()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        KNIGHT_ATTACKS[square] = knight_attacks_mask(square);
    }
}

void generate_knight_moves(int color, MoveList &move_list, State &state)
{
    BitBoard board, attacks;
    int source, target;

    if (color == WHITE)
    {
        board = state.position.pieces[wKNIGHT];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            attacks = KNIGHT_ATTACKS[source] & !state.position.sides[WHITE];

            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[BLACK].get_bit(target))
                    move_list.add_move(Move(source, target, wKNIGHT, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, wKNIGHT, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
    else
    {
        board = state.position.pieces[bKNIGHT];

        while (board != empty_board)
        {
            source = board.get_ls1b_index();
            attacks = KNIGHT_ATTACKS[source] & !state.position.sides[BLACK];

            while (attacks != empty_board)
            {
                target = attacks.get_ls1b_index();

                if (!state.position.sides[WHITE].get_bit(target))
                    move_list.add_move(Move(source, target, bKNIGHT, 0, 0, 0, 0, 0));
                else
                    move_list.add_move(Move(source, target, bKNIGHT, 0, 1, 0, 0, 0));
                attacks.unset_bit(target);
            }
            board.unset_bit(source);
        }
    }
}