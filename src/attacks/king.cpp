#pragma once
#include "../globals.h"

BitBoard KING_ATTACKS[BOARD_SIZE];

BitBoard king_attacks_mask(int square)
{
    BitBoard attacks = BitBoard();
    BitBoard board = BitBoard();

    board.set_bit(square);

    if (((board >> 8)) != empty_board)
        attacks |= board >> 8;

    if (((board << 8)) != empty_board)
        attacks |= board << 8;

    if (((board >> 1) & NOT_H_FILE) != empty_board)
        attacks |= board >> 1;

    if (((board << 1) & NOT_A_FILE) != empty_board)
        attacks |= board << 1;

    if (((board >> 7) & NOT_A_FILE) != empty_board)
        attacks |= board >> 7;

    if (((board << 7) & NOT_H_FILE) != empty_board)
        attacks |= board << 7;

    if (((board >> 9) & NOT_H_FILE) != empty_board)
        attacks |= board >> 9;

    if (((board << 9) & NOT_A_FILE) != empty_board)
        attacks |= board << 9;

    return attacks;
}

void init_king_attacks()
{
    for (int square = 0; square < BOARD_SIZE; square++)
    {
        KING_ATTACKS[square] = king_attacks_mask(square);
    }
}